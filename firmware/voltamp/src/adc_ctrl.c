
#include "adc_ctrl.h"
#include "ch.h"
#include "hal.h"

#include "hdw_config.h"
#include "dac.h"
#include "cpu_io.h"
#include "led_ctrl.h"

#define OSC_QUEUE_SZ 	384

#define EAUX_IND 0
#define EREF_IND 1
#define IAUX_IND 2

int fbEn = 0;
int fbEnPrev = 0;
int fbGainNum = 1;
int fbGainDen = 1;
int fbInIndex = 2;
int fbSetpoint = 2047;
int dacHigh = 2047;
int dacLow  = 2047;

// Oscilloscope queues.
InputQueue eaux_queue, eref_queue, iaux_queue;
uint8_t     eaux_queue_buffer[OSC_QUEUE_SZ],
			eref_queue_buffer[OSC_QUEUE_SZ],
			iaux_queue_buffer[OSC_QUEUE_SZ];

// Command queue.
OutputQueue command_queue;
uint8_t     command_queue_buffer[4];

int oscPeriod = 10000;
int oscTime   = 0;



void modeProcess( int mode );
void modeInit( int mode );

static void initDac( void );
static void processDac( void );

static void initOnePulse( void );
static void processOnePulse( void );

static void initMeandr( void );
static void processMeandr( void );

static void initSweep( void );
static void processSweep( void );

static void initFb( void );
static void processFb( void );

static void processOsc( adcsample_t * buffer );

uint8_t mode = TDAC;

static void convAdcReadyCb( ADCDriver * adcp, adcsample_t * buffer, size_t n )
{
	(void)adcp;
	(void)n;
	// For debugging purposes toggling LED3.
	//toggleLedsI( 4 );

	// Process mode.
	modeProcess( mode );

	// Process oscilloscope regardless of all other conditions.
	processOsc( buffer );

	// Query for command.
	chSysLockFromIsr();
		msg_t msg;
		msg = chOQGetI( &command_queue );
		uint8_t newMode = ( msg != Q_EMPTY ) ? 1 : 0;
		if ( newMode )
			// New mode if mode has arrived.
			mode = (uint8_t)msg;
	chSysUnlockFromIsr();

	// Init new mode.
	if ( newMode )
		modeInit( mode );
}

#define ADC_NUM_CHANNELS 3
#define ADC_BUF_DEPTH    2
static adcsample_t adcSamples[ ADC_NUM_CHANNELS * ADC_BUF_DEPTH ];

// ADC_SAMPLE_1P5
// ADC_SAMPLE_7P5
// ADC_SAMPLE_13P5
// ADC_SAMPLE_28P5
// ADC_SAMPLE_41P5
// ADC_SAMPLE_55P5
// ADC_SAMPLE_71P5
// ADC_SAMPLE_239P5

// At 16MHz 3 signals would be measured with frequency 16000 / ( 28.5 * 3 ) = 187kHz.
// But ADC definitely shouldn't be faster then PWM.
#define ADC_SAMPLING  ADC_SAMPLE_239P5 //ADC_SAMPLE_28P5

static const ADCConversionGroup adcGroup =
{
    TRUE,
    ADC_NUM_CHANNELS,
    convAdcReadyCb,
    NULL,
    0, 0,           						/* CR1, CR2 */
    ADC_SMPR1_SMP_AN10( ADC_SAMPLING ) |
    ADC_SMPR1_SMP_AN11( ADC_SAMPLING ) |
    ADC_SMPR1_SMP_AN12( ADC_SAMPLING ),		// SMPR1
    0, 										// SMPR2
    ADC_SQR1_NUM_CH( ADC_NUM_CHANNELS ),	// SQR1
    0,										// SQR2
    ADC_SQR3_SQ1_N( ADC_CHANNEL_IN10 ) |
    ADC_SQR3_SQ2_N( ADC_CHANNEL_IN11 ) |
    ADC_SQR3_SQ3_N( ADC_CHANNEL_IN12 ) 		// SQR3
};




void initAdc( void )
{
	// Command queue initialization.
	chOQInit( &command_queue, command_queue_buffer, sizeof( command_queue_buffer ), 0 );
	// Oscilloscope queues initialization.
	chIQInit( &eaux_queue, eaux_queue_buffer, OSC_QUEUE_SZ, 0 );
	chIQInit( &eref_queue, eref_queue_buffer, OSC_QUEUE_SZ, 0 );
	chIQInit( &iaux_queue, iaux_queue_buffer, OSC_QUEUE_SZ, 0 );
    // Init ADC pins.
    palSetGroupMode( PORT_ADC, PAL_PORT_BIT( PIN_EAUX ) |
    	                       PAL_PORT_BIT( PIN_EREF ) |
    	                       PAL_PORT_BIT( PIN_IAUX ),
                               0, PAL_MODE_INPUT_ANALOG );

    // Init ADC.
    adcStart( &ADCD1, NULL );
    adcStartConversion( &ADCD1, &adcGroup, adcSamples, ADC_BUF_DEPTH );
}


void setOscPeriod( uint32_t t )
{
	oscPeriod = t;
}

void setFbSetpoint( int sp )
{
	(void)sp;
}

void setFbInput( int ind )
{
	(void)ind;
}

void setFbGain( int num, int den )
{
	(void)num;
	(void)den;
}

void setFbEn( int en )
{
	(void)en;
}

OutputQueue * commandQueue( void )
{
    return &command_queue;
}

InputQueue * eauxQueue( void )
{
	return &eaux_queue;
}

InputQueue * erefQueue( void )
{
	return &eref_queue;
}

InputQueue * iauxQueue( void )
{
	return &iaux_queue;
}

void modeProcess( int mode )
{
	switch ( mode )
	{
	case 0:
		processDac();
		break;
	case 1:
		processOnePulse();
		break;
	case 2:
		processMeandr();
		break;
	case 3:
		processSweep();
		break;
	case 4:
		processFb();
		break;
	}
}

void modeInit( int mode )
{
	switch ( mode )
	{
	case 0:
		initDac();
		break;
	case 1:
		initOnePulse();
		break;
	case 2:
		initMeandr();
		break;
	case 3:
		initSweep();
		break;
	case 4:
		initFb();
		break;
	}
}

static void initDac( void )
{
	uint8_t * args = funcArgs();
	dacLow  = (uint16_t)args[0] + ((uint16_t)(args[1]) << 8);
	dacHigh = (uint16_t)args[2] + ((uint16_t)(args[3]) << 8);
}

static void processDac( void )
{
	DacCfg dacs;
	dacs.dac1 = dacLow;
	dacs.dac2 = dacHigh;
	dacSet( &dacs );
}

uint32_t pulsePeriod = 1000;
uint32_t pulseTime   = 0;
DacCfg   pulseDac, pulseDacSave;

static void initOnePulse( void )
{
	uint8_t * args = funcArgs();
	pulseDac.dac1 = (uint16_t)args[0] + ((uint16_t)(args[1]) << 8);
	pulseDac.dac2 = (uint16_t)args[2] + ((uint16_t)(args[3]) << 8);
	dacSet( &pulseDac );

	pulseDacSave.dac1 = dacLow;
	pulseDacSave.dac2 = dacHigh;

	dacLow  = pulseDac.dac1;
	dacHigh = pulseDac.dac2;

	pulsePeriod = (uint32_t)args[4] +
			      ((uint32_t)(args[5]) << 8) +
			      ((uint32_t)(args[6]) << 16) +
			      ((uint32_t)(args[7]) << 24);
	pulseTime = 0;
}

static void processOnePulse( void )
{
	pulseTime += 1;
	if ( pulseTime >= pulsePeriod )
	{
		dacSet( &pulseDacSave );
		dacLow  = pulseDacSave.dac1;
		dacHigh = pulseDacSave.dac2;
		mode = TDAC;
	}
}

uint32_t meanderPeriod1 = 1000;
uint32_t meanderPeriod2 = 2000;
uint32_t meanderTime   = 0;
DacCfg   meanderDac1,
		 meanderDac2;

static void initMeandr( void )
{
	uint8_t * args = funcArgs();

	meanderDac1.dac1 = (uint16_t)args[0] + ((uint16_t)(args[1]) << 8);
	meanderDac1.dac2 = (uint16_t)args[2] + ((uint16_t)(args[3]) << 8);
	meanderPeriod1 = (uint32_t)args[4] +
			         ((uint32_t)(args[5]) << 8) +
			         ((uint32_t)(args[6]) << 16) +
			         ((uint32_t)(args[7]) << 24);

	meanderDac2.dac1 = (uint16_t)args[8]  + ((uint16_t)(args[9]) << 8);
	meanderDac2.dac2 = (uint16_t)args[10] + ((uint16_t)(args[11]) << 8);
	meanderPeriod2   = (uint32_t)args[12] +
			           ((uint32_t)(args[13]) << 8) +
			           ((uint32_t)(args[14]) << 16) +
			           ((uint32_t)(args[15]) << 24);
	meanderPeriod2 += meanderPeriod1;
	meanderTime = meanderPeriod2;
}

static void processMeandr( void )
{
	meanderTime += 1;
	if ( meanderTime == meanderPeriod1 )
	{
		// Shift to dac2.
		dacSet( &meanderDac2 );
	}
	else if ( meanderTime >= meanderPeriod2 )
	{
		dacSet( &meanderDac1 );
		meanderTime -= meanderPeriod2;
	}
}

int32_t sweepPeriod = 1000;
float   sweepPeriodInvf = 0.001f;
int32_t sweepTime   = 0;
DacCfg   sweepDac1,
         sweepDac2;
int8_t   sweepSpeed = 1;
float dDacf1, dDacf2;

static void initSweep( void )
{
    uint8_t * args = funcArgs();

    sweepDac1.dac1 = (uint16_t)args[0] + ((uint16_t)(args[1]) << 8);
    sweepDac1.dac2 = (uint16_t)args[2] + ((uint16_t)(args[3]) << 8);
    sweepDac2.dac1 = (uint16_t)args[4] + ((uint16_t)(args[5]) << 8);
    sweepDac2.dac2 = (uint16_t)args[6] + ((uint16_t)(args[7]) << 8);
    sweepPeriod    = (uint32_t)args[8] +
                     ((uint32_t)(args[9]) << 8) +
                     ((uint32_t)(args[10]) << 16) +
                     ((uint32_t)(args[11]) << 24);
    sweepPeriodInvf = 1.0f/(float)sweepPeriod;
    dDacf1       = (float)( sweepDac2.dac1 - sweepDac1.dac1 );
    dDacf2       = (float)( sweepDac2.dac2 - sweepDac1.dac2 );
    sweepTime      = 0;
    sweepSpeed     = 1;
}

static void processSweep( void )
{
    sweepTime += sweepSpeed;
    uint8_t overflow, underflow;
    overflow  = ( sweepTime >= sweepPeriod );
    underflow = ( sweepTime <= 0 );

    int32_t time;
    if ( overflow )
        time = sweepPeriod;
    else if ( underflow )
        time = 0;
    else
        time = sweepTime;
    if ( overflow || underflow )
        sweepSpeed = -sweepSpeed;

    int from, dac;
    DacCfg writeDac;
    float timef = (float)time * sweepPeriodInvf;

    from = (int32_t)sweepDac1.dac1;
    dac  = from + (int)( dDacf1 * timef );
    writeDac.dac1 = (uint16_t)dac;

    from = (int32_t)sweepDac1.dac2;
    dac  = from + (int)( dDacf2 * timef );
    writeDac.dac2 = (uint16_t)dac;

    dacSet( &writeDac );
}

static void initFb( void )
{

}

static void processFb( void )
{

}

static uint32_t filtered[3] = { 2047, 2047, 2047 };

static void processOsc( adcsample_t * buffer )
{
	oscTime += 1;

	int timeConst = oscPeriod >> 2;
	int alpha = (timeConst < 32768) ? timeConst : 32767;
	alpha = ( alpha > 0 ) ? alpha : 1;
	filtered[0] = ( ( (filtered[0]<<1) + 1 )*( alpha-1 ) + ( buffer[0] << 5 ) + 1)/alpha;
	filtered[0] >>= 1;
	filtered[1] = ( ( (filtered[1]<<1) + 1 )*( alpha-1 ) + ( buffer[1] << 5 ) + 1)/alpha;
	filtered[1] >>= 1;
	filtered[2] = ( ( (filtered[2]<<1) + 1 )*( alpha-1 ) + ( buffer[2] << 5 ) + 1)/alpha;
	filtered[2] >>= 1;

	if ( oscTime >= oscPeriod )
	{
		oscTime -= oscPeriod;
		chSysLockFromIsr();
			uint16_t v16;
			uint8_t vLow, vHigh;

			if ( (chIQGetEmptyI( &eaux_queue ) >= 2) &&
			     (chIQGetEmptyI( &eref_queue ) >= 2) &&
			     (chIQGetEmptyI( &iaux_queue ) >= 2) )
			{
                v16 = filtered[0];
                vLow = (uint8_t)(v16 & 0x00FF);
                vHigh = (uint8_t)((v16 >> 8) & 0x00FF);
                chIQPutI( &eaux_queue, vLow );
                chIQPutI( &eaux_queue, vHigh );

                v16 = filtered[1];
                vLow = (uint8_t)(v16 & 0x00FF);
                vHigh = (uint8_t)((v16 >> 8) & 0x00FF);
                chIQPutI( &eref_queue, vLow );
                chIQPutI( &eref_queue, vHigh );

                v16 = filtered[2];
                vLow = (uint8_t)(v16 & 0x00FF);
                vHigh = (uint8_t)((v16 >> 8) & 0x00FF);
                chIQPutI( &iaux_queue, vLow );
                chIQPutI( &iaux_queue, vHigh );
			}
		chSysUnlockFromIsr();
	}
}






#include "adc_ctrl.h"
#include "ch.h"
#include "hal.h"

#include "dac.h"

#define OSC_QUEUE_SZ 	256

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

InputQueue eaux_queue, eref_queue, iaux_queue;
uint8_t     eaux_queue_buffer[OSC_QUEUE_SZ],
			eref_queue_buffer[OSC_QUEUE_SZ],
			iaux_queue_buffer[OSC_QUEUE_SZ];
int oscPeriod = 10000;
int oscTime   = 0;

typedef TMode enum { TDAC, TONEPULSE, TMEANDR, TSWEEP, TFEEDBACK };

static void processDac( void );
static void processOnePulse( void );
static void processMeandr( void );
static void processSaw( void );
static void processFb( int value );

static void writeDac( void );
static void processOsc( adcSample_t * buffer );

static void convAdcReadyCb( ADCDriver * adcp, adcsample_t * buffer, size_t n )
{
	if ( fbEn )
		processFb( buffer[fbInIndex] );
	else
		processDac();
	processOsc( buffer );
}

#define ADC_NUM_CHANNELS 3
#define AFC_BUF_DEPTH    2
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
#define ADC_SAMPLING  ADC_SAMPLE_7P5

static const ADCConversionGroup adcGroup =
{
    TRUE,
    ADC_NUM_CHANNELS,
    convAdcReadyCb,
    NULL,
    0, 0,           /* CR1, CR2 */
    0,
    ADC_SMPR2_SMP_AN10( ADC_SAMPLING ) |
    ADC_SMPR2_SMP_AN11( ADC_SAMPLING ) |
    ADC_SMPR2_SMP_AN12( ADC_SAMPLING ),
    ADC_SQR1_NUM_CH( ADC_NUM_CHANNELS ),
    0,
    ADC_SQR3_SQ1_N( ADC_CHANNEL_IN10 ) |
    ADC_SQR3_SQ2_N( ADC_CHANNEL_IN11 ) |
    ADC_SQR3_SQ3_N( ADC_CHANNEL_IN12 )
};




void initAdc( void )
{
	// Oscilloscope queues initialization.
	chIQInit( &eaux_queue, eaux_queue_buffer, OSC_QUEUE_SZ, 0 );
	chIQInit( &eref_queue, eref_queue_buffer, OSC_QUEUE_SZ, 0 );
	chIQInit( &iaux_queue, iaux_queue_buffer, OSC_QUEUE_SZ, 0 );
    // Init ADC pins.
    palSetGroupMode( CONV_ADC_PORT, PAL_PORT_BIT( CONV_ADC_BUCK_VOLT_PIN )  |
    	                            PAL_PORT_BIT( CONV_ADC_BOOST_VOLT_PIN ) |
    	                            PAL_PORT_BIT( CONV_ADC_SOLAR_VOLT_PIN ) |
    	                            PAL_PORT_BIT( CONV_ADC_BOOST_CURR_PIN ) |
				                    PAL_PORT_BIT( CONV_ADC_BUCK_CURR_PIN ),
                                    0, PAL_MODE_INPUT_ANALOG );

    // Init ADC.
    adcStart( &ADCD1, NULL );
    adcStartConversion( &ADCD1, &adcGroup, adcSamples, ADC_BUF_DEPTH );
}


void setOscPeriod( uint32_t t )
{

}

void setFbSetpoint( int sp )
{

}

void setFbInput( int ind )
{

}

void setFbGain( int num, int den )
{

}

void setFbEn( int en )
{

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

static void processFb( int value )
{

}

static void processDac( void )
{

}

static void writeDac( void )
{
	// Write DAc values.
	DacCfg dacs;
	dacs.dac1 = dacHigh;
	dacs.dac2 = dacLow;
	dacSet( &dacs );
}

static void processOsc( adcSample_t * buffer )
{
	oscTime += 1;
	if ( oscTime >= oscPeriod )
	{
		oscTime -= oscPeriod;
		chSysLock();
			uint16_t v16;
			uint8_t vLow, vHigh;

			v16 = buffer[0];
			vLow = (uint8_t)(v16 & 0x00FF);
			vHigh = (uint8_t)((v16 >> 8) & 0x00FF);
			chIQPutI( &eaux_queue, vLow );
			chIQPutI( &eaux_queue, vHigh );

			v16 = buffer[1];
			vLow = (uint8_t)(v16 & 0x00FF);
			vHigh = (uint8_t)((v16 >> 8) & 0x00FF);
			chIQPutI( &eref_queue, vLow );
			chIQPutI( &eref_queue, vHigh );

			v16 = buffer[2];
			vLow = (uint8_t)(v16 & 0x00FF);
			vHigh = (uint8_t)((v16 >> 8) & 0x00FF);
			chIQPutI( &iaux_queue, vLow );
			chIQPutI( &iaux_queue, vHigh );

		chSysUnlock();
	}
}





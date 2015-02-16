
#include "adc_ctrl.h"
#include "ch.h"
#include "hal.h"

#define EAUX_IND 0
#define EREF_IND 1
#define IAUX_IND 2

static void convAdcReadyCb( ADCDriver * adcp, adcsample_t * buffer, size_t n )
{
    (void)adcp;
    //(void)buffer;
    (void)n;
    // Buck
    if ( buffer[ BUCK_CURR_IND ] > buckCurr )
    {
        buckPwm -= buckGain;
	if ( buckPwm < 0 )
	    buckPwm = 0;
	pwmEnableChannelI(&CONV_PWM, PWM_BUCK_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, buckPwm ) );
    }
    else
    {
        if ( buffer[ BUCK_VOLT_IND ] < buckVolt )
        {
    	    buckPwm += buckGain;
	    if ( buckPwm > 10000 )
    	        buckPwm = 10000;
            pwmEnableChannelI(&CONV_PWM, PWM_BUCK_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, buckPwm ) );
        }
        else if ( buffer[ BUCK_VOLT_IND ] > buckVolt )
        {
    	    buckPwm -= buckGain;
	    if ( buckPwm < 0 )
	        buckPwm = 0;
    	    pwmEnableChannelI(&CONV_PWM, PWM_BUCK_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, buckPwm ) );
        }
    }
    // Boost
    if ( buffer[ BOOST_CURR_IND ] > boostCurr )
    {
        boostPwm -= boostGain;
        if ( boostPwm < 0 )
	    boostPwm = 0;
        pwmEnableChannelI(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, boostPwm ) );
    }
    else
    {
        if ( buffer[ SOLAR_VOLT_IND ] >= solarVolt )
        {
            if ( buffer[ BOOST_VOLT_IND ] < boostVolt )
            {
                boostPwm += boostGain;
                if ( boostPwm > boostMaxPwm )
                    boostPwm = boostMaxPwm;
                pwmEnableChannelI(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, boostPwm ) );
            }
            else if ( buffer[ BOOST_VOLT_IND ] > boostVolt )
            {
                boostPwm -= boostGain;
                if ( boostPwm < 0 )
                    boostPwm = 0;
                pwmEnableChannelI(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, boostPwm ) );
            }
        }
        else
        {
            boostPwm = 0;
    	    pwmEnableChannelI(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, 0 ) );
        }
    }
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




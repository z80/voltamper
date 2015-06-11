
#include "ch.h"
#include "hal.h"

#include "iwdg.h"
#include "led_ctrl.h"
#include "dac.h"
#include "adc_ctrl.h"
#include "cpu_io.h"

int main(void)
{
    halInit();
    chSysInit();

    initLed();
    dacInit();
    //initAdc();
    //cpu_io_init();

    while (TRUE)
    {
    	DacCfg dac;
    	//cpu_io_process();
        setLeds( 1 );
    	dac.dac1 = 0;
    	dac.dac2 = 0;
        dacSet( &dac );
    	chThdSleepMilliseconds( 1000 );
        setLeds( 2 );
    	dac.dac1 = 2047;
    	dac.dac2 = 2047;
        dacSet( &dac );
    	chThdSleepMilliseconds( 1000 );
        setLeds( 4 );
    	dac.dac1 = 4095;
    	dac.dac2 = 4095;
        dacSet( &dac );
    	chThdSleepMilliseconds( 1000 );
    }
    return 0;
}

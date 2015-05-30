
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
    //dacInit();
    //initAdc();
    //cpu_io_init();

    while (TRUE)
    {
    	//cpu_io_process();
        setLeds( 1 );
    	chThdSleepMilliseconds( 1000 );
        setLeds( 2 );
    	chThdSleepMilliseconds( 1000 );
        setLeds( 4 );
    	chThdSleepMilliseconds( 1000 );
    }
    return 0;
}


#include "ch.h"
#include "hal.h"

#include "iwdg.h"
#include "led_ctrl.h"
#include "dac.h"

int main(void)
{
    halInit();
    chSysInit();

    initLed();
    dacInit();

    while (TRUE)
    {
        chThdSleepMilliseconds( 250 );
    }
    return 0;
}

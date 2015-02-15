
#include "ch.h"
#include "hal.h"

#include "iwdg.h"
#include "led_ctrl.h"

int main(void)
{
    halInit();
    chSysInit();

    initLed();

    while (TRUE)
    {
        chThdSleepMilliseconds( 250 );
    }
    return 0;
}

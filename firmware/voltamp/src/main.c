
#include "ch.h"
#include "hal.h"

#include "iwdg.h"
#include "i2c_ctrl.h"

int main(void)
{
    halInit();
    chSysInit();



    while (TRUE)
    {
        chThdSleepMilliseconds( 250 );
    }
    return 0;
}

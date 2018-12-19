#include <stdlib.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "helpers.h"
#include "chprintf.h"
#include "shell.h"
#include "shellcommands.h"

#if 0

#include "wdog.h"
#include "env.h"
#include "pwm.h"
#include "exti.h"
#include "spi.h"

#include "threadkiller.h"
#include "blinker.h"
#include "gps.h"

#include "adc.h"
#include "i2c.h"

#include "auxlink.h"
#include "messaging.h"
#endif

char *environment;
char **environ;


int main(void)
{
    halInit();
    chSysInit();
//    wdogTKInit(WDG_TIMEOUT_NORMAL);

    sdStart(&SD6, NULL);  /* Serial console in USART6, 115200 */

    consoleStream = (BaseSequentialStream *) &SD6;


    PRINT("\n\r");
    PRINT("\n\r");
    PRINT("Telakone AUX IO\n\r");
    PRINT("---------------\n\r");
    PRINT("\n\r");

#if 0
    spiTKInit();

    environment = chHeapAlloc(NULL, ENV_PAGE_SIZE);
    environ = chHeapAlloc(NULL, ENV_PAGE_SIZE*sizeof(char*));

    memset(environment, 0, ENV_PAGE_SIZE);
    memset(environ, 0, ENV_PAGE_SIZE*sizeof(char*));

    PRINT(" - Loaded %d variables\n\r", envLoader());

    rtcSTM32SetPeriodicWakeup(&RTCD1, NULL);

    pwmTKInit();
    extiTKInit();

    crcStart(&CRCD1, NULL);

    i2cTKInit();
    adcTKInit();
    adcTKStartConv();
    auxLinkInit(0x00);

    wdogTKKick();
#endif
#ifndef TK_USE_WDOG
    PRINT(" - Watchdog is disabled\n\r");
#endif

    PRINT(" - Initialisation complete\n\r");

#if 0
    /* Start threads */
    startThreadKiller();
    startBlinkerThread(); /* Controls the external warning lamps on OUT1 */
    startGpsThread();     /* GPS Receiver and 1PPS handler thread */

    startI2cThread();
    startMessagingThread(); /* Parses messages from network */

    startAuxLinkThread(); /* Auxiliary device link */
#endif
    PRINT(" - Threads started\n\r");

    PRINT("\n\r");
//    cmd_status((BaseSequentialStream *)&SD6, 0, NULL);

    /* Everything is initialised, turh red led off */
    palClearLine(LINE_LED_RED);

    shellInit();

    chThdCreateFromHeap(NULL, SHELL_WA_SIZE, "shell", NORMALPRIO + 1, shellThread, (void *)&shell_cfg_uart);

    while (true)
    {
//        wdogTKKick();
        chThdSleepMilliseconds(500);
        palToggleLine(LINE_LED_GRN);
//        palToggleLine(PAL_LINE(GPIOA, 5U));
    }
}

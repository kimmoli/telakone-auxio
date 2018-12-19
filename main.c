#include <stdlib.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "helpers.h"
#include "chprintf.h"
#include "shell.h"
#include "shellcommands.h"

#include "pwm.h"

#include "threadkiller.h"
#include "blinker.h"
#include "auxlink.h"
#include "auxmotor.h"

#if 0

#include "wdog.h"
#include "env.h"
#include "exti.h"
#include "spi.h"

#include "gps.h"

#include "adc.h"
#include "i2c.h"

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

    pwmTKInit();

    uint8_t addr = 0x10 | (palReadGroup(GPIOC, 0x03, 0) ^ 0x03); // Address jumpers are at PC1,PC0
    PRINT("- AUX Link address %02X\n\r", addr);

    auxLinkInit(addr);

#if 0
    crcStart(&CRCD1, NULL);

    wdogTKKick();
#endif

#ifndef TK_USE_WDOG
    PRINT(" - Watchdog is disabled\n\r");
#endif

    PRINT(" - Initialisation complete\n\r");

    /* Start threads */
    startThreadKiller();
    startBlinkerThread();
    startAuxmotorThread(0);
    startAuxmotorThread(1);
    startAuxLinkThread(); /* Auxiliary device link */

#if 0
    startMessagingThread(); /* Parses messages from network */

#endif
    PRINT(" - Threads started\n\r");

    PRINT("\n\r");
//    cmd_status((BaseSequentialStream *)&SD6, 0, NULL);

    /* Everything is initialised, turn red led off */
    palClearLine(LINE_LED_RED);

    shellInit();

    chThdCreateFromHeap(NULL, SHELL_WA_SIZE, "shell", NORMALPRIO + 1, shellThread, (void *)&shell_cfg_uart);

    while (true)
    {
//        wdogTKKick();
        chThdSleepMilliseconds(500);
        palToggleLine(LINE_LED_GRN);
    }
}

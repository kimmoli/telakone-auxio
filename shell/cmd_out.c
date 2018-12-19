#include <stdlib.h>
#include "hal.h"
#include "chprintf.h"
#include "shellcommands.h"
#include "pwm.h"

void cmd_out(BaseSequentialStream *chp, int argc, char *argv[])
{
    int channel;
    int newValue;

    if (argc == 2)
    {
        channel = strtol(argv[0], NULL, 0);
        newValue = strtol(argv[1], NULL, 0);

        if (channel >= 1 || channel <= 8 || newValue >= 0 || newValue <= 100)
        {
            if (channel == 1)
            {
                palWriteLine(LINE_OUT_1, newValue == 0 ? 0 : 1);
            }
            else if (channel == 3)
            {
                palWriteLine(LINE_OUT_3, newValue == 0 ? 0 : 1);
            }
            else if (channel == 4)
            {
                palWriteLine(LINE_OUT_4, newValue == 0 ? 0 : 1);
            }
            else if (channel == 5)
            {
                palWriteLine(LINE_OUT_5, newValue == 0 ? 0 : 1);
            }
            else
            {
                pwmSetChannel(channel, 100, newValue);
                chprintf(chp, "Setting output %d to %d %%\n\r", channel, newValue);
            }
            return;
        }
    }

    chprintf(chp, "out channel dutycycle\n\r");
    chprintf(chp, "Channels 2,6,7,8 support PWM\n\r");
    chprintf(chp, "Channels 1,3,4,5 0 off, >= 1 on\n\r");
    chprintf(chp, "\n\r");
    chprintf(chp, "1 - %d\n\r", palReadLine(LINE_OUT_1));
    chprintf(chp, "2 - %d %%\n\r", pwmGetChannel(TK_PWM_OUT2, 100));
    chprintf(chp, "3 - %d\n\r", palReadLine(LINE_OUT_3));
    chprintf(chp, "4 - %d\n\r", palReadLine(LINE_OUT_4));
    chprintf(chp, "5 - %d\n\r", palReadLine(LINE_OUT_5));
    chprintf(chp, "6 - %d %%\n\r", pwmGetChannel(TK_PWM_OUT6, 100));
    chprintf(chp, "7 - %d %%\n\r", pwmGetChannel(TK_PWM_OUT7, 100));
    chprintf(chp, "8 - %d %%\n\r", pwmGetChannel(TK_PWM_OUT8, 100));
}



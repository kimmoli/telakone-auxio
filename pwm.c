#include "hal.h"
#include "pwm.h"
#include "hal_community.h"

const PWMConfig pwmcfg1 =
{
    1000000,                                  /* 1 MHz PWM clock frequency.   */
    500,                                      /* PWM period 500 us, 2kHz */
    NULL,
    {
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_DISABLED, NULL},
    },
    0,
    0
};

const PWMConfig pwmcfg5 =
{
    1000000,                                  /* 1 MHz PWM clock frequency.   */
    100,                                      /* PWM period 100 us 10kHz */
    NULL,
    {
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_DISABLED, NULL},
    },
    0,
    0
};

const PWMConfig pwmcfg9 =
{
    1000000,                                  /* 1 MHz PWM clock frequency.   */
    100,                                      /* PWM period 100 us 10kHz */
    NULL,
    {
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_ACTIVE_HIGH, NULL},
        {PWM_OUTPUT_DISABLED, NULL},
        {PWM_OUTPUT_DISABLED, NULL},
    },
    0,
    0
};

void pwmSetChannel(int ch, int range, int value)
{
    switch (ch)
    {
        case TK_PWM_OUT2:
            pwmEnableChannelI(&PWMD5, 0,  PWM_FRACTION_TO_WIDTH(&PWMD5, range, value)); break;
        case TK_PWM_OUT6:
            pwmEnableChannelI(&PWMD1, 0,  PWM_FRACTION_TO_WIDTH(&PWMD1, range, value)); break;
        case TK_PWM_OUT7:
            pwmEnableChannelI(&PWMD1, 1,  PWM_FRACTION_TO_WIDTH(&PWMD1, range, value)); break;
        case TK_PWM_OUT8:
            pwmEnableChannelI(&PWMD1, 2,  PWM_FRACTION_TO_WIDTH(&PWMD1, range, value)); break;

        case TK_PWM_MOTOR1H1:
            pwmEnableChannelI(&PWMD9, 1,  PWM_FRACTION_TO_WIDTH(&PWMD9, range, value)); break;
        case TK_PWM_MOTOR1H2:
            pwmEnableChannelI(&PWMD9, 0,  PWM_FRACTION_TO_WIDTH(&PWMD9, range, value)); break;
        case TK_PWM_MOTOR2H1:
            pwmEnableChannelI(&PWMD5, 1,  PWM_FRACTION_TO_WIDTH(&PWMD5, range, value)); break;
        case TK_PWM_MOTOR2H2:
            pwmEnableChannelI(&PWMD5, 2,  PWM_FRACTION_TO_WIDTH(&PWMD5, range, value)); break;
        default:
            ;
    }
}

int pwmGetChannel(int ch, int range)
{
    int width = 0;
    int period = 1;

    switch (ch)
    {
        case TK_PWM_OUT2:
            width = PWMD5.tim->CCR[0];
            period = PWMD5.period;
            break;
        case TK_PWM_OUT6:
            width = PWMD1.tim->CCR[0];
            period = PWMD1.period;
            break;
        case TK_PWM_OUT7:
            width = PWMD5.tim->CCR[1];
            period = PWMD5.period;
            break;
        case TK_PWM_OUT8:
            width = PWMD5.tim->CCR[2];
            period = PWMD5.period;
            break;
        case TK_PWM_MOTOR1H1:
            width = PWMD9.tim->CCR[1];
            period = PWMD9.period;
            break;
        case TK_PWM_MOTOR1H2:
            width = PWMD9.tim->CCR[0];
            period = PWMD9.period;
            break;
        case TK_PWM_MOTOR2H1:
            width = PWMD5.tim->CCR[1];
            period = PWMD5.period;
            break;
        case TK_PWM_MOTOR2H2:
            width = PWMD5.tim->CCR[2];
            period = PWMD5.period;
            break;
        default:
            ;
    }
    return (range * width) / period;
}

void pwmTKInit(void)
{
    pwmStart(&PWMD1, &pwmcfg1);
    pwmStart(&PWMD5, &pwmcfg5);
    pwmStart(&PWMD9, &pwmcfg9);
}

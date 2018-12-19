#ifndef TK_PWM_H
#define TK_PWM_H

#define TK_PWM_OUT2     2
#define TK_PWM_OUT6     6
#define TK_PWM_OUT7     7
#define TK_PWM_OUT8     8
#define TK_PWM_MOTOR1H1  11
#define TK_PWM_MOTOR1H2  12
#define TK_PWM_MOTOR2H1  13
#define TK_PWM_MOTOR2H2  14

void pwmTKInit(void);
void pwmSetChannel(int ch, int range, int value);
int pwmGetChannel(int ch, int range);

#define pwmTKEnableChannelI(pwmp, channel, width) do {                     \
    (pwmp)->enabled |= ((pwmchnmsk_t)1U << (pwmchnmsk_t)(channel));          \
    pwm_TK_lld_enable_channel(pwmp, channel, width);                             \
    } while (false)

void pwm_TK_lld_init(void);
void pwm_TK_lld_start(PWMDriver *pwmp);
void pwm_TK_lld_enable_channel(PWMDriver *pwmp, pwmchannel_t channel, pwmcnt_t width);
void pwmTKStart(PWMDriver *pwmp, const PWMConfig *config);

#endif


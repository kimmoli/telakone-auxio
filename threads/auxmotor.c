#include <stdlib.h>
#include "hal.h"
#include "auxmotor.h"
#include "pwm.h"
#include "helpers.h"

static virtual_timer_t linearaccel_vt;
event_source_t auxMotorEvent;

static volatile int newValue = 0;
static volatile int prevValue = 0;
static volatile int currentValue = 0;

const int linearaccelstep = 10;
const int linearacceldelay = 50;

static MotorConfig motorconf[] =
{
    { LINE_MOTOR1_L1, LINE_MOTOR1_L2, TK_PWM_MOTOR1H1, TK_PWM_MOTOR1H2 },
    { LINE_MOTOR2_L1, LINE_MOTOR2_L2, TK_PWM_MOTOR2H1, TK_PWM_MOTOR2H2 }
};

static THD_FUNCTION(auxmotorThread, arg)
{
    MotorConfig *mc = arg;

    event_listener_t elAuxMotor;
    eventflags_t  flags;

    chEvtRegisterMask(&auxMotorEvent, &elAuxMotor, 0x100);

    while (!chThdShouldTerminateX())
    {
        if (chEvtWaitAnyTimeout(0x100, MS2ST(25)) != 0)
        {
            flags = chEvtGetAndClearFlags(&elAuxMotor);

            if (flags & AUXMOTOR_EVENT_STOP)
            {
                auxmotorControl(mc, 0);
            }
            else if (flags & AUXMOTOR_EVENT_SET)
            {
                auxmotorControl(mc, (int8_t)(flags & 0xff));
            }
        }
    }

    chThdExit(MSG_OK);
}

void startAuxmotorThread(int motor)
{
    chEvtObjectInit(&auxMotorEvent);
    chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(512), (motor ? "auxmotor2" : "auxmotor1"), NORMALPRIO+1, auxmotorThread, &motorconf[motor]);
}

void linearaccelcb(void *arg)
{
    MotorConfig *mc = arg;

    if (newValue > (currentValue + linearaccelstep))
        currentValue += linearaccelstep;
    else if (newValue < (currentValue - linearaccelstep))
        currentValue -= linearaccelstep;
    else
        currentValue = newValue;

    if (prevValue*currentValue < 0) /* change direction */
    {
        currentValue = 0;
    }

    if (currentValue == 0) /* stop */
    {
        palClearLine(mc->motorl1);//LINE_MOTORL1);
        palClearLine(mc->motorl2);//LINE_MOTORL2);
        pwmSetChannel(mc->motorh1_pwm, 100, 0);//TK_PWM_MOTORH1, 100, 0);
        pwmSetChannel(mc->motorh2_pwm, 100, 0);//TK_PWM_MOTORH2, 100, 0);
    }
    else if (currentValue < 0) /* in */
    {
        palSetLine(mc->motorl1);//LINE_MOTORL1);
        palClearLine(mc->motorl2);//LINE_MOTORL2);
        pwmSetChannel(mc->motorh1_pwm, 100, 0);//TK_PWM_MOTORH1, 100, 0);
        pwmSetChannel(mc->motorh2_pwm, 100, 0);//TK_PWM_MOTORH2, 100, abs(currentValue));
    }
    else if (currentValue) /* out */
    {
        palClearLine(mc->motorl1);//LINE_MOTORL1);
        palSetLine(mc->motorl2);//LINE_MOTORL2);
        pwmSetChannel(mc->motorh1_pwm, 100, 0);//TK_PWM_MOTORH1, 100, abs(currentValue));
        pwmSetChannel(mc->motorh2_pwm, 100, 0);//TK_PWM_MOTORH2, 100, 0);
    }

    prevValue = currentValue;

    if (newValue != currentValue)
    {
        chSysLockFromISR();
        chVTSetI(&linearaccel_vt, MS2ST(linearacceldelay), linearaccelcb, mc);
        chSysUnlockFromISR();
    }
}

void auxmotorControl(MotorConfig *mc, int value)
{
    if (value == currentValue)
        return;

    newValue = value;

    chVTSet(&linearaccel_vt, MS2ST(linearacceldelay), linearaccelcb, mc);
}

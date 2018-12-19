#ifndef TK_AUXMOTOR_H
#define TK_AUXMOTOR_H

#define AUXMOTOR_EVENT_STOP    0x4000
#define AUXMOTOR_EVENT_SET     0x8000

typedef struct
{
    ioline_t motorl1;
    ioline_t motorl2;
    int motorh1_pwm;
    int motorh2_pwm;
} MotorConfig;

extern event_source_t auxMotorEvent;

void startAuxmotorThread(int motor);
void auxmotorControl(MotorConfig *mc, int value);

#endif


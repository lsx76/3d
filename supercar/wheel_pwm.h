#ifndef __WHEEL_PWM_H__
#define __WHEEL_PWM_H__

#include "tim.h"
#include "wheel_config.h"


//void set_motor_speed(uint16_t num, int32_t speed);

void set_motor_speed(motor_t *motor, int32_t speed);

#endif



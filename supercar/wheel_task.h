#ifndef __WHEEL_TASK_H__
#define __WHEEL_TASK_H__

#include "pid.h"
#include "wheel_pwm.h"
 
extern pid_data_t motor1_pid_data;
extern pid_data_t motor2_pid_data;
extern pid_data_t motor3_pid_data;
extern pid_data_t motor4_pid_data;

extern pid_paramer_t motor1_pid_paramer;
extern pid_paramer_t motor2_pid_paramer;
extern pid_paramer_t motor3_pid_paramer;
extern pid_paramer_t motor4_pid_paramer;

int32_t read_freq(motor_t *motor);
void motor_pid(void);
void motor_pid_data_init(pid_data_t *motor_pid_data);

//void set_motor1_pid(uint16_t num,float p,float i,float d);
#endif


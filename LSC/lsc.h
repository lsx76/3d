#ifndef __LSC_H__
#define __LSC_H__

#include "usart.h"

void cmd_action_group_run(uint8_t action_group,uint16_t number);
void cmd_action_group_speed(uint8_t action_group,uint16_t speed);
void cmd_action_group_stop(void);
void servogroup_Init(void);
void servogroup_Stepped_distinguish(void);
void servogroup_catch_Steppedplatform_2(void);
void servogroup_catch_Steppedplatform_3(void);
void servogroup_catch_Steppedplatform_1(void);
void servogroup_catch_Steppedplatform_4(void);
void servogroup_catch_Steppedplatform_5(void);
void servogroup_catch_Steppedplatform_6(void);
void servogroup_catch_Stripplatform(void);
void servogroup_ic_Stripplatform(void);

void servogroup_sayyes(void);
void servogroup_sayno(void);

#endif

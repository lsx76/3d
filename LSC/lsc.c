#include "lsc.h"

/**********************************************************************
 * @Name    cmd_action_group_run
 * @declaration : 发送动作组指令
 * @param   action_group 动作组编号      number  执行次数
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void cmd_action_group_run(uint8_t action_group,uint16_t number)
{
    uint8_t command[7];
    command[0] = 0x55;
    command[1] = 0x55;
    command[2] = 0x05;
    command[3] = 0x06;
    command[4] = action_group;
    command[5] = number&0XFF;
    command[6] = (number>>8)&0XFF;
    HAL_UART_Transmit(&huart8,command,7,1000);
}

/**********************************************************************
 * @Name    cmd_action_group_speed
 * @declaration : 调节动作组执行速度
 * @param   action_group 动作组编号      speed  执行速度
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void cmd_action_group_speed(uint8_t action_group,uint16_t speed)
{
    uint8_t command[7];
    command[0] = 0x55;
    command[1] = 0x55;
    command[2] = 0x05;
    command[3] = 0x0B;
    command[4] = action_group;
    command[5] = speed&0XFF;
    command[6] = (speed>>8)&0XFF;
    HAL_UART_Transmit(&huart8,command,7,1000);  //发送动作组编号和执行速度
}

/**********************************************************************
  * 函数名：cmd_action_group_stop
  * 描述: 发送停止命令
  * 参数：无   
  * 返回值:无
***********************************************************************/
void cmd_action_group_stop()
{
    uint8_t command[4];
    command[0] = 0x55;
    command[1] = 0x55;
    command[2] = 0x02;
    command[3] = 0x07;
    HAL_UART_Transmit(&huart8,command,4,1000);
}

/**********************************************************************
  * 函数名：servogroup_Init
  * 描述: 动作组初始化
  * 参数：无   
  * 返回值:无
***********************************************************************/
void servogroup_Init()
{
    cmd_action_group_run(0x00,1);   //发送动作组指令0x00 执行一次
}

//阶梯平台检测
void servogroup_Stepped_distinguish()
{
    cmd_action_group_speed(0x01,275);     //设定动作组0x01的执行速度是175
    cmd_action_group_run(0x01,1);        //执行一次动作组0x01
}

//从第二平台拿球
void servogroup_catch_Steppedplatform_2()
{
    cmd_action_group_speed(0x02,150);
    cmd_action_group_run(0x02,1);
}

void servogroup_catch_Steppedplatform_1()
{
    cmd_action_group_speed(0x03,150);
    cmd_action_group_run(0x03,1);
}

void servogroup_catch_Steppedplatform_3()
{
    cmd_action_group_speed(0x04,150);
    cmd_action_group_run(0x04,1);
}

void servogroup_catch_Steppedplatform_4()
{
    cmd_action_group_speed(0x33,150);
    cmd_action_group_run(0x33,1);
}

void servogroup_catch_Steppedplatform_5()
{
    cmd_action_group_speed(0x35,150);
    cmd_action_group_run(0x35,1);
}

void servogroup_catch_Steppedplatform_6()
{
    cmd_action_group_speed(0x36,150);
    cmd_action_group_run(0x36,1);
}

//动作组检测圆盘机
void servogroup_catch_Stripplatform()
{
    cmd_action_group_speed(0x15,350);       
    cmd_action_group_run(0x15,1);         
}

//动作组圆盘机到获取id
void servogroup_ic_Stripplatform()
{
    cmd_action_group_speed(0x17,200);       
    cmd_action_group_run(0x17,1);         
}

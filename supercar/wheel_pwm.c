#include "wheel_pwm.h"

/* PWM动力最大值 */
#define MOTOR_SPEED_MAX 10000

///**********************************************************************************************************
//*函 数 名: motor_set_speed
//*功能说明: 将pwm_pluse赋值给motor结构体中的speed 并向其通道注入动力
//*形    参: motor结构体的地址   动力
//*返 回 值: 无
//*备    注: 为适应usmart，将入口参数调整为  电机编号  动力( 8.1 修改 ）
//				   为适应十字交叉全向轮布局，须判断 
//**********************************************************************************************************/
//void set_motor_speed(uint16_t num, int32_t speed)
//{
//    int32_t ccr = 0;
//		motor_t* motor;
//		if(num == 1)
//			motor = &motor1;
//		else if(num == 2)
//			motor  = &motor2;
//		else if(num == 3)
//			motor = &motor3;
//		else 
//			motor = &motor4;
//	
//		if(num==1||num==2)
//		{
//    if (speed >= 0)
//    {
//        if (speed > MOTOR_SPEED_MAX)
//            ccr = MOTOR_SPEED_MAX;
//        else
//            ccr = speed;

//        motor->speed = ccr;

//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, motor->speed);
//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, 0);
//    }

//    else if (speed < 0)
//    {
//        if (speed < -MOTOR_SPEED_MAX)
//            ccr = MOTOR_SPEED_MAX;
//        else
//            ccr = -speed;

//        motor->speed = ccr;

//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, motor->speed);
//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, 0);
//    }
//		}
//		
//		if(num==3||num==4)
//		{
//    if (speed >= 0)
//    {
//        if (speed > MOTOR_SPEED_MAX)
//            ccr = MOTOR_SPEED_MAX;
//        else
//            ccr = speed;

//        motor->speed = ccr;

//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, motor->speed);
//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, 0);
//    }

//    else if (speed < 0)
//    {
//        if (speed < -MOTOR_SPEED_MAX)
//            ccr = MOTOR_SPEED_MAX;
//        else
//            ccr = -speed;

//        motor->speed = ccr;

//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, motor->speed);
//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, 0);
//    }
//		}
//}

/**********************************************************************
 * @Name    set_motor_speed
 * @declaration : 将pwm_pluse赋值给motor结构体中的speed  并向其通道注入动力
 * @param   motor  motor结构体的地址 speed 动力
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void set_motor_speed(motor_t *motor, int32_t speed)
{
    int32_t ccr = 0;

    if (speed >= 0)
    {
        if (speed > MOTOR_SPEED_MAX)
            ccr = MOTOR_SPEED_MAX;
        else
            ccr = speed;

        motor->speed = ccr;

        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, motor->speed);
        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, 0);
    }

    else if (speed < 0)
    {
        if (speed < -MOTOR_SPEED_MAX)
            ccr = MOTOR_SPEED_MAX;
        else
            ccr = -speed;

        motor->speed = ccr;

        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, motor->speed);
        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, 0);
    }
}


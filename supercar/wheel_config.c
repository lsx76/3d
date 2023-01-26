#include "wheel_config.h"
#include "wheel.h"

/* 定义电机数据类型 */
motor_t motor1;
motor_t motor2;
motor_t motor3;
motor_t motor4;
uint16_t val;
//定义面向轮子时，轮子顺时针转为正转（A不为0正转）
extern double motor_target[5];

	/**********************************************************************************************************
*函 数 名: set_motor1val
*功能说明: 设置某定时器的某个通道的占空比
*形    参: 占空比大小
*返 回 值: 无
*备    注: 为调试usmart写的函数，在小车行驶过程中无实际应用
**********************************************************************************************************/
void set_motor1val(uint16_t val)
{
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,val);
}


	/**********************************************************************************************************
*函 数 名: set_motor
*功能说明: 设置某个电机的目标速度值
*形    参: 目标速度值的大小
*返 回 值: 无
*备    注: 为逐个电机调pid写的适用于usmart的函数，在小车行驶过程中无实际运用
**********************************************************************************************************/
void set_motor(uint16_t speed)
{
	motor_target[1]=speed;
}


	/**********************************************************************************************************
*函 数 名: motor1_Enable
*功能说明: 初始化motor1结构体 并使能其对应时钟与中断
*形    参: motor结构体的地址
*返 回 值: 无
**********************************************************************************************************/
void motor1_Enable(motor_t *motor)
{
    motor->htim_pwm = &htim1;
    motor->channel_A = TIM_CHANNEL_2;
    motor->channel_B = TIM_CHANNEL_1;
    motor->speed = 0;

    motor->htim_ic = &htim5;
    motor->ic_channel = TIM_CHANNEL_1;
    motor->IC_GPIO_Port_v = MOTOR3_ENCODER_GPIO_Port;
    motor->IC_Pin_v = MOTOR3_ENCODER_Pin;

    motor->updata = 0;
    motor->freq = 0 ;

    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_A);
    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_B);
    HAL_TIM_IC_Start_IT(motor->htim_ic, motor->ic_channel);
}


/**********************************************************************************************************
*函 数 名: motor2_Enable
*功能说明: 初始化motor2结构体 并使能其对应时钟与中断
*形    参: motor结构体的地址
*返 回 值: 无
**********************************************************************************************************/

void motor2_Enable(motor_t *motor)
{
    motor->htim_pwm = &htim1;
    motor->channel_A = TIM_CHANNEL_3;
    motor->channel_B = TIM_CHANNEL_4;
    motor->speed = 0;

    motor->htim_ic = &htim5;
    motor->ic_channel = TIM_CHANNEL_3;
    motor->IC_GPIO_Port_v = MOTOR4_ENCODER_GPIO_Port;
    motor->IC_Pin_v = MOTOR4_ENCODER_Pin;

    motor->updata = 0;
    motor->freq = 0;

    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_A);
    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_B);
    HAL_TIM_IC_Start_IT(motor->htim_ic, motor->ic_channel);
}

/**********************************************************************************************************
*函 数 名: motor3_Enable
*功能说明: 初始化motor2结构体 并使能其对应时钟与中断
*形    参: motor结构体的地址
*返 回 值: 无
**********************************************************************************************************/
void motor3_Enable(motor_t *motor)
{
    motor->htim_pwm = &htim2;
    motor->channel_A = TIM_CHANNEL_4;
    motor->channel_B = TIM_CHANNEL_3;
    motor->speed = 0;

    motor->htim_ic = &htim3;
    motor->ic_channel = TIM_CHANNEL_1;
    motor->IC_GPIO_Port_v = MOTOR1_ENCODER_GPIO_Port;
    motor->IC_Pin_v = MOTOR1_ENCODER_Pin;

    motor->updata = 0;
    motor->freq = 0;

    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_A);
    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_B);
    HAL_TIM_IC_Start_IT(motor->htim_ic, motor->ic_channel);
}

/**********************************************************************************************************
*函 数 名: motor4_Enable
*功能说明: 初始化motor2结构体 并使能其对应时钟与中断
*形    参: motor结构体的地址
*返 回 值: 无
**********************************************************************************************************/
void motor4_Enable(motor_t *motor)
{
    motor->htim_pwm = &htim2;
    motor->channel_A = TIM_CHANNEL_1;
    motor->channel_B = TIM_CHANNEL_2;
    motor->speed = 0;

    motor->htim_ic = &htim3;
    motor->ic_channel = TIM_CHANNEL_3;
    motor->IC_GPIO_Port_v = MOTOR2_ENCODER_GPIO_Port;
    motor->IC_Pin_v = MOTOR2_ENCODER_Pin;

    motor->updata = 0;
    motor->freq = 0;

    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_A);
    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_B);
    HAL_TIM_IC_Start_IT(motor->htim_ic, motor->ic_channel);
}

void car_go(void)
{
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);//1轮反转
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,0);//2轮正转
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,0);//4轮反转
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,0);//3轮正转
	
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4,0);

}

void car_left(void)
{
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,2000);//1轮正转
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,2000);//3轮反转
	
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,2000);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,2000);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4,0);

}

void car_rightback(void)
{
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,0);
	
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,2000);//1轮反转
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,2000);//2轮反转
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,2100);//3轮正转
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4,2000);//4轮正转

}

void car_turn(void)
{
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,2000);//1轮正转
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,2000);//2轮正转
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,0);
	
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,2100);//3轮正转
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4,2000);//4轮正转

}



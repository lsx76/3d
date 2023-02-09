#include "wheel_task.h"
#include "usart.h"

extern double motor_target[5];
//extern int val_track_front;
//extern int val_track_back;

/* 定义四个电机进行pid操作的数据 */
pid_data_t motor1_pid_data;
pid_data_t motor2_pid_data;
pid_data_t motor3_pid_data;
pid_data_t motor4_pid_data;

/* 电机1最外层pid控制参数 */
pid_paramer_t motor1_pid_paramer = {
    .integrate_max = 7000,
    .kp = 78,
    .ki = 3.5,
    .kd = 1.8,
    .control_output_limit = 9000
};

/* 电机2最外层pid控制参数 */
pid_paramer_t motor2_pid_paramer = {
    .integrate_max = 7000,
    .kp = 78,
    .ki = 3.5,
    .kd = 1.8,
    .control_output_limit = 9000
};

/* 电机3最外层pid控制参数 */
pid_paramer_t motor3_pid_paramer = {
    .integrate_max = 7000,
    .kp = 78,
    .ki = 3.5,
    .kd = 1.8,
    .control_output_limit = 9000
};

/* 电机4最外层pid控制参数 */
pid_paramer_t motor4_pid_paramer = {
    .integrate_max = 7000,
    .kp = 78,
    .ki = 3.5,
    .kd = 1.8,
    .control_output_limit = 9000
};


/**********************************************************************************************************
*函 数 名: set_motor1_pid
*功能说明: 用来在usmart上调整pid参数
*形    参: 电机编号 p i d
*返 回 值: 无
*备    注: 最终调试时觉得这样pid参数不能直观的表现出来所以弃用
**********************************************************************************************************/

//void set_motor1_pid(uint16_t num,float p,float i,float d)
//{
//	pid_paramer_t* motor_pid_paramer;
//	if(num == 1)
//			motor_pid_paramer = &motor1_pid_paramer;
//		else if(num == 2)
//			motor_pid_paramer = &motor1_pid_paramer;
//		else if(num == 3)
//			motor_pid_paramer = &motor1_pid_paramer;
//		else 
//			motor_pid_paramer = &motor1_pid_paramer;
//		
//		motor_pid_paramer->kp = p;
//		motor_pid_paramer->ki = i;
//		motor_pid_paramer->kd = d;
//		
//		
//}

/**********************************************************************
 * @Name    motor_pid_data_init
 * @declaration : 电机pid初始化
 * @param   motor_pid_data 电机pid结构体
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void motor_pid_data_init(pid_data_t *motor_pid_data)
{
    motor_pid_data->expect = 0;
    motor_pid_data->feedback = 0;

    motor_pid_data->err = 0;
    motor_pid_data->last_err = 0;
    motor_pid_data->last2_err=0;
    motor_pid_data->integrate = 0;
    motor_pid_data->delta = 0;
    motor_pid_data->dis_err = 0;

    motor_pid_data->control_output = 0;

    motor_pid_data->short_circuit_flag = 0;
    motor_pid_data->err_callback = NULL;
    motor_pid_data->pri_data = NULL;
}

/**********************************************************************************************************
*函 数 名: read_freq
*功能说明: 读取motor结构体中的freq并返回
*形    参: motor结构体的地址 
*返 回 值: 电机转动频率（反应速度）
**********************************************************************************************************/

/**********************************************************************
 * @Name    read_freq
 * @declaration : 读取motor结构体中的freq并返回 
 * @param   motor 电机结构体
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
int32_t read_freq(motor_t *motor)
{   double temp = motor->freq;
    motor->freq = 0;
	return temp;
}


/**********************************************************************
 * @Name    motor_pid
 * @declaration : 电机pid 
 * @param   None 
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void motor_pid()
{
   /*计算电机最终目标值*/
   motor1_pid_data.expect = motor_target[1] ;//+ val_track_front + val_track_back;
   motor2_pid_data.expect = motor_target[2] ;//+ val_track_front + val_track_back;
   motor3_pid_data.expect = motor_target[3] ;//+ val_track_front + val_track_back;
   motor4_pid_data.expect = motor_target[4] ;//+ val_track_front + val_track_back;
  
   /*读取当前电机转速*/
   motor1_pid_data.feedback = read_freq(&motor1);
   motor2_pid_data.feedback = read_freq(&motor2);
   motor3_pid_data.feedback = read_freq(&motor3);
   motor4_pid_data.feedback = read_freq(&motor4);
  
	/*进行pid运算 并将输出值注入电机通道*/
//   set_motor_speed(4, pid_incremental(&motor4_pid_data,&motor4_pid_paramer));
//   set_motor_speed(1, pid_incremental(&motor1_pid_data,&motor1_pid_paramer));
//   set_motor_speed(2, pid_incremental(&motor2_pid_data,&motor2_pid_paramer));
//   set_motor_speed(3, pid_incremental(&motor3_pid_data,&motor3_pid_paramer));
	set_motor_speed(&motor1, pid_incremental(&motor1_pid_data,&motor1_pid_paramer));
    set_motor_speed(&motor2, pid_incremental(&motor2_pid_data,&motor2_pid_paramer));
    set_motor_speed(&motor3, pid_incremental(&motor3_pid_data,&motor3_pid_paramer));
    set_motor_speed(&motor4, pid_incremental(&motor4_pid_data,&motor4_pid_paramer));
   
   printf("%f , %f\n",motor2_pid_data.expect ,motor2_pid_data.feedback );
   // printf("%f,%f,%f,%f,%f,%f\n",motor1_pid_data.feedback,motor2_pid_data.feedback,motor3_pid_data.feedback,motor4_pid_data.feedback,motor1_pid_data.expect,motor3_pid_data.expect); 
}





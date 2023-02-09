#include "imu_task.h"
#include "time_delay.h"

pid_data_t imu_pid_data;

/* 陀螺仪pid控制参数 */
pid_paramer_t imu_pid_paramer = {
    .integrate_max = 500,
    .kp = 2.8,
    .ki = 0,
    .kd = 0,
    . control_output_limit = 1000
}; 
 
/**********************************************************************
 * @Name    set_imu_status
 * @declaration : 设置是否开启陀螺仪
 * @param   attitude 姿态角结构体  status 状态
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void set_imu_status(ATTITUDE_t *attitude,bool status)
{
    attitude->status = status;
}
  
/**********************************************************************
 * @Name    imu_pid_data_init
 * @declaration : 初始陀螺仪pid数据
 * @param   imu_pid_data 陀螺仪pid结构体 
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void imu_pid_data_init(pid_data_t *imu_pid_data)
{
    imu_pid_data->expect = 0;
    imu_pid_data->feedback = 0;

    imu_pid_data->err = 0;
    imu_pid_data->last_err = 0;
    imu_pid_data->last2_err=0;
    imu_pid_data->integrate = 0;
    imu_pid_data->delta = 0;
    imu_pid_data->dis_err = 0;

    imu_pid_data->control_output = 0;

    imu_pid_data->short_circuit_flag = 0;
    imu_pid_data->err_callback = NULL;
    imu_pid_data->pri_data = NULL;
}

/**********************************************************************
 * @Name    set_turn_angle
 * @declaration : 设置目标角度
 * @param   attitude 姿态角结构体  target_angle 目标角度
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void set_turn_angle(ATTITUDE_t *attitude,int target_angle)
{
    attitude->target_angle = target_angle;
}

/**********************************************************************
 * @Name    imu_calibration
 * @declaration : 校准当前参考系z轴
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void imu_calibration()
{
    float current_yaw = 0, last_yaw = 0;
    uint8_t init_times = 0;
    while(init_times <= 100) {
        current_yaw = attitude.yaw;
        if (__fabs(current_yaw-last_yaw)<10) {
            HAL_Delay(10);
            init_times++;
        } else {
            init_times = 0;
        }
        last_yaw = current_yaw;
    }
    
    attitude.refer_angle = current_yaw;    //基准角度
    //imu.init_ = current_yaw <= 180 ? -current_yaw : 360 - current_yaw;
  //  HAL_Delay(500);
}

/**********************************************************************
 * @Name    imu_pid
 * @declaration : 陀螺仪pid
 * @param   attitude 姿态角结构体
 * @retval   : pid_positional(&imu_pid_data, &imu_pid_paramer) pid输出值
 * @author  hoson_stars
 ***********************************************************************/
int imu_pid(ATTITUDE_t *attitude)
{
    if(attitude->status == true) {
        imu_pid_data.expect = attitude->target_angle;
        if ((attitude->yaw - attitude->refer_angle) > 180)
            attitude->yaw -= 360;
        else if ((attitude->yaw - attitude->refer_angle) < -180)
            attitude->yaw += 360;

        imu_pid_data.feedback = attitude->yaw - attitude->refer_angle;
				//printf("yaw=%f\n,refer=%f\n",attitude->yaw,attitude->refer_angle);
				
        
        if(__fabs(imu_pid_data.feedback-imu_pid_data.expect)<=1.5) return 0;   //3度范围内认为已达到目标值
        else return pid_positional(&imu_pid_data, &imu_pid_paramer);
    }
    else return 0;
}

/**********************************************************************
 * @Name    self_turn
 * @declaration : 车体自转
 * @param   angle 目标转动角度  逆时针正 顺时针负
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void self_turn(int angle)
{
    imu_calibration();
    set_turn_angle(&attitude,angle);  
    set_imu_status(&attitude,true);
    delay_ms(3000);
//    set_imu_status(&attitude,false);
    imu_pid_data_init(&imu_pid_data);
}






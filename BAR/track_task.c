#include "track_task.h"

pid_data_t track_pid_data;

/* 循迹pid控制参数 */
pid_paramer_t track_pid_paramer = {
    .integrate_max = 5,
    .kp = 2.5,
    .ki = 0,
    .kd = 0.1,
    .control_output_limit = 40
};

/* 计算循迹偏差值所用权重*/
float row_weight[9] = {0,-4,-3,-2,-1,1,2,3,4};   //左偏输出负  右偏输出正
float vertical_weight[9] = {0,-4,-3,-2,-1,1,2,3,4};    //上偏输出负  下偏输出正


void set_track_status(TRACKINGBOARD_t *trackboard,bool status)
{
    trackboard->status = status;
}

/**********************************************************************
 * @Name    track_pid_data_init
 * @declaration : 初始化循迹pid数据
 * @param   track_pid_data 循迹板pid结构体
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void track_pid_data_init(pid_data_t *track_pid_data)
{
    track_pid_data->expect = 0;
    track_pid_data->feedback = 0;

    track_pid_data->err = 0;
    track_pid_data->last_err = 0;
    track_pid_data->last2_err=0;
    track_pid_data->integrate = 0;
    track_pid_data->delta = 0;
    track_pid_data->dis_err = 0;

    track_pid_data->control_output = 0;

    track_pid_data->short_circuit_flag = 0;
    track_pid_data->err_callback = NULL;
    track_pid_data->pri_data = NULL;
}

/**********************************************************************
 * @Name    calculate_diviation
 * @declaration :计算循迹板的偏离值
 * @param   trackboard 循迹板结构体  weight 权重
 * @retval   : div 偏离值
 * @author  hoson_stars
 ***********************************************************************/
int calculate_diviation(TRACKINGBOARD_t *trackboard,float weight[])
{
    int div = 0;
    for(int i=1;i<=8;i++){
        div += trackboard->ttl_msg[i] * weight[i];
    }
    return div;
}

/**********************************************************************
 * @Name    track_pid
 * @declaration :循迹pid
 * @param   trackboard 循迹板结构体  weight 权重
 * @retval   : pid_positional(&track_pid_data, &track_pid_paramer) pid输出量
 * @author  hoson_stars
 ***********************************************************************/
int track_pid(TRACKINGBOARD_t *trackboard,float weight[])
{
    if(trackboard->status == true) {
        track_pid_data.expect = 0;
        track_pid_data.feedback = calculate_diviation(trackboard,weight);        
        return pid_positional(&track_pid_data, &track_pid_paramer);    
    }
    else return 0;
}


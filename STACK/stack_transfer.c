#include "stack_transfer.h"
#include "lsc.h"
#include "journey.h"
#include "openmv.h"
#include "time_delay.h"
#include "snow.h"
#include "wheel.h"
#include "time_cnt.h"
//#include "motor.h"

#define yes 1       //找到小球
#define no  0       //未找到

bool if_ball = false;     //标记是否读到ic卡数据

extern uint32_t waittime; //waittime==1,延时10ms

extern uint8_t putBallOrder[9];

int cnt = 0;

/*定义仓库中随机工件的状态*/
int storage_state[4][5] = {no};    //未实现的想法1

/*第四列工件不需要被倒垛的标志位*/
int need_to_transfer[4]={0};      //未实现想法2

/**********************************************************************
 * @Name    scan_ball
 * @declaration : 获取小球id
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void scan_ball()
{
    waittime = 400;
    while(waittime!=0) {
        Get_openmv(&openmv);
        if(openmv.message ==0x01) {
            if_ball = true;
            break;
        }
    }
}

int error_red_1 = 0;
int error_red_2 = 0;
int error_red_3 = 0;

/**********************************************************************
 * @Name    stack_transfer_red
 * @declaration : 倒垛全过程
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void stack_transfer_red()
{
	
	tell_openmv_to_transfer_red();
	tell_openmv_to_transfer_red();
	tell_openmv_to_transfer_red();
	tell_openmv_to_transfer_red();
	tell_openmv_to_transfer_red();
	tell_openmv_to_transfer_red();
	tell_openmv_to_transfer_red();
	tell_openmv_to_transfer_red();            // 将目标色域调整为红半场立体仓库内部目标色域
	
	for(int i=0;i<3;i++){
		openmv.message = 0;                  //标志位清零
		switch(i){
			case 0:
				cmd_action_group_speed(0x1D,175);
				cmd_action_group_run(0x1D,1);
				delay_ms(800);break;
		  	case 1:
				cmd_action_group_speed(0x26,175);
				cmd_action_group_run(0x26,1);
				delay_ms(800);break;
			case 2:
				cmd_action_group_speed(0x27,175);
				cmd_action_group_run(0x27,1);
				delay_ms(1300);break;
		}       //将机械臂以1.75倍速提升到指定检测高度   
		
		set_chassis_speed(5,20,0);
		delay_ms(500);            //冲过第一个边缘
		
		baohu_transfer:
		if(error_red_1>=3) 
		{
			hit_bar_red();
			move_to_bar_right_red();
			error_red_1 = 0;           //去掉这一步行，检测完三个小格后会继续进入这个if，不会执行下一层
			continue;
		}
		if(error_red_2>=3) 
		{
			hit_bar_red();
			move_to_bar_right_red();
			error_red_2 = 0;
			continue;
		}
		if(error_red_3>=3) break;
		set_chassis_speed(0,20,0);
		delay_ms(1000);              //每行检测三个小格，三次检测不到执行下一行，第三行检测不到直接执行入仓操作
		while(1)
		{
			if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;              //检测到一个边缘，证明到达第一个小格
			
		}
		if(i == 0) error_red_1++;
		if(i == 1) error_red_2++;
		if(i == 2) error_red_3++;
		set_chassis_speed(0,0,0);
		tell_openmv_to_transfer();
		tell_openmv_to_transfer();
		tell_openmv_to_transfer();
		tell_openmv_to_transfer();
		tell_openmv_to_transfer();             //停车找是否有小球，多发几次以防通信不畅
		
		waittime = 100;
		while(1){
			if(waittime == 0){
				tell_openmv_to_loosen();
				goto baohu_transfer;         //等openmv 1s，检测不到就检查下一个小格
			}
			if(openmv.message == 0x01) break;        //检测到小球，挑出循环
		}
		set_chassis_speed(0,0,0);
		openmv.message = 0;
		
		
	  switch(i){
			case 0:
				cmd_action_group_speed(0x28,300);
				cmd_action_group_run(0x28,1);
				delay_ms(800);break;
		  case 1:
				cmd_action_group_speed(0x2A,300);
				cmd_action_group_run(0x2A,1);
				delay_ms(800);break;
			case 2:
				cmd_action_group_speed(0x2C,300);
				cmd_action_group_run(0x2C,1);
				delay_ms(800);break;
		}       //以三倍速将机械臂伸进去
		
		tell_claw_to_catch();
		delay_ms(100);
		
		switch(i){
			case 0:
				cmd_action_group_speed(0x29,300);
				cmd_action_group_run(0x29,1);
				delay_ms(700);break;
			case 1:
				cmd_action_group_speed(0x2B,300);
				cmd_action_group_run(0x2B,1);
				delay_ms(800);break;
			case 2:
				cmd_action_group_speed(0x2D,175);
				cmd_action_group_run(0x2D,1);
				delay_ms(900);break;
		}      //三倍速将机械臂收回
		hit_bar_red();
		move_to_bar_right_red();        //回到仓库右边缘
	  switch(i){
			case 0:
				cmd_action_group_speed(0x1D,175);
				cmd_action_group_run(0x1D,1);
				delay_ms(800);break;
		  case 1:
				cmd_action_group_speed(0x26,175);
				cmd_action_group_run(0x26,1);
				delay_ms(800);break;
			case 2:
				cmd_action_group_speed(0x27,175);
				cmd_action_group_run(0x27,1);
				delay_ms(1200);break;
		}       //机械臂检测对应层的边缘
		while(1)
		{
			set_chassis_speed(5,20,0);
			if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
		}       //找到边缘
		set_chassis_speed(0,0,0);
		switch(i){
			case 0:
				cmd_action_group_speed(0x1F,100);
				cmd_action_group_run(0x1F,1);
				delay_ms(2500);break;
		  case 1:
				cmd_action_group_speed(0x20,300);
				cmd_action_group_run(0x20,1);
				delay_ms(800);break;
			case 2:
				cmd_action_group_speed(0x21,300);	 
				cmd_action_group_run(0x21,1);
				delay_ms(800);break;
		}       //将球放入仓库
//		tell_openmv_to_loosen2();
//		delay_ms(500);               //此处注释掉是因为出现通信不畅的bug，将这部分代码放入到switch中bug没有再出现
		switch(i){
			case 0:
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(500);
				cmd_action_group_speed(0x23,175);
				cmd_action_group_run(0x23,1);
				delay_ms(800);break;
		  case 1:
				printf("start\r\n");                             //用来debug的
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(500);
				printf("over\r\n");                               //用来debug的
				cmd_action_group_speed(0x24,175);
				cmd_action_group_run(0x24,1);
				delay_ms(1300);break;
			case 2:
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(500);
				cmd_action_group_speed(0x25,175);
				cmd_action_group_run(0x25,1);
				delay_ms(800);break;
		}       //将机械臂拿出
		switch(i){
			case 0:
				error_red_1 = 0;break;
		    case 1:
				error_red_2 = 0;break;
			case 2:
				error_red_3 = 0;break;
		}
		hit_bar_red();
		move_to_bar_right_red();           //回到仓库右边缘
	}
	cmd_action_group_speed(0x00,175);
	cmd_action_group_run(0x00,1);
	delay_ms(700);                        //将机械臂恢复到初始化位置，避免下个动作与上个动作连贯时产生的不必要的碰撞
	
}

/**********************************************************************
 * @Name    stack_transfer_blue
 * @declaration : 蓝半场倒垛全过程
 * @param   None
 * @retval   : 无
 * @author  hoson_stras
 ***********************************************************************/
void stack_transfer_blue()
{
	
	tell_openmv_to_transfer_blue();
	tell_openmv_to_transfer_blue();
	tell_openmv_to_transfer_blue();
	tell_openmv_to_transfer_blue();
	tell_openmv_to_transfer_blue();
	
	for(int i=0;i<3;i++){
		openmv.message = 0;
		switch(i){
			case 0:
				cmd_action_group_speed(0x2E,175);
				cmd_action_group_run(0x2E,1);
				delay_ms(800);break;
		  case 1:
				cmd_action_group_speed(0x26,175);
				cmd_action_group_run(0x26,1);
				delay_ms(800);break;
			case 2:
				cmd_action_group_speed(0x30,175);
				cmd_action_group_run(0x30,1);
				delay_ms(1300);break;
		}
		
		set_chassis_speed(10,20,0);
		delay_ms(500);
		
		baohu_transfer:
		if(error_red_1>=3) 
		{
			hit_bar_red();
			move_to_bar_right_red();
			error_red_1 = 0;
			continue;
		}
		if(error_red_2>=3) 
		{
			hit_bar_red();
			move_to_bar_right_red();
			error_red_2 = 0;
			continue;
		}
		if(error_red_3>=3) break;
		set_chassis_speed(0,20,0);
		delay_ms(1000);
		while(1)
		{
			if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
			
		}
		if(i == 0) error_red_1++;
		if(i == 1) error_red_2++;
		if(i == 2) error_red_3++;
		set_chassis_speed(0,0,0);
		tell_openmv_to_transfer();
		tell_openmv_to_transfer();
		tell_openmv_to_transfer();
		tell_openmv_to_transfer();
		tell_openmv_to_transfer();
		
		waittime = 100;
		while(1){
			if(waittime == 0){
				tell_openmv_to_loosen();
				goto baohu_transfer;
			}
			if(openmv.message == 0x01) break;
		}
		set_chassis_speed(0,0,0);
		openmv.message = 0;
		
		
	  switch(i){
			case 0:
				cmd_action_group_speed(0x28,300);
				cmd_action_group_run(0x28,1);
				delay_ms(800);break;
		  case 1:
			    cmd_action_group_speed(0x2A,300);
				cmd_action_group_run(0x2A,1);
				delay_ms(800);break;
			case 2:
				cmd_action_group_speed(0x2C,300);
				cmd_action_group_run(0x2C,1);
				delay_ms(800);break;
		}
		
		tell_claw_to_catch();
		delay_ms(100);
		
		switch(i){
			case 0:
				cmd_action_group_speed(0x29,300);
				cmd_action_group_run(0x29,1);
				delay_ms(700);break;
			case 1:
				cmd_action_group_speed(0x2B,300);
				cmd_action_group_run(0x2B,1);
				delay_ms(800);break;
			case 2:
				cmd_action_group_speed(0x2D,175);
				cmd_action_group_run(0x2D,1);
				delay_ms(900);break;
		}
		hit_bar_red();
		move_to_bar_right_red();
	  switch(i){
			case 0:
				cmd_action_group_speed(0x1D,175);
				cmd_action_group_run(0x1D,1);
				delay_ms(800);break;
		  case 1:
				cmd_action_group_speed(0x26,175);
				cmd_action_group_run(0x26,1);
				delay_ms(800);break;
			case 2:
				cmd_action_group_speed(0x27,175);
				cmd_action_group_run(0x27,1);
				delay_ms(1200);break;
		}
		while(1)
		{
			set_chassis_speed(10,20,0);
			if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
		}
		set_chassis_speed(0,0,0);
		switch(i){
			case 0:
				cmd_action_group_run(0x1F,1);
				delay_ms(2500);break;
		  	case 1:
		 		cmd_action_group_speed(0x20,300);
				cmd_action_group_run(0x20,1);
				delay_ms(800);break;
			case 2:
				cmd_action_group_speed(0x21,300);	 
				cmd_action_group_run(0x21,1);
				delay_ms(800);break;
		}
//		tell_openmv_to_loosen2();
//		delay_ms(500);
		switch(i){
			case 0:
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(500);
				cmd_action_group_speed(0x23,175);
				cmd_action_group_run(0x23,1);
				delay_ms(800);break;
		  case 1:
				printf("start\r\n");
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(500);
				printf("over\r\n");
				cmd_action_group_speed(0x24,175);
				cmd_action_group_run(0x24,1);
				delay_ms(1300);break;
			case 2:
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(10);
				tell_openmv_to_loosen2();
				delay_ms(500);
				cmd_action_group_speed(0x25,175);
				cmd_action_group_run(0x25,1);
				delay_ms(800);break;
		}
		switch(i){
			case 0:
				error_red_1 = 0;break;
		  case 1:
				error_red_2 = 0;break;
			case 2:
				error_red_3 = 0;break;
		}
		hit_bar_red();
		move_to_bar_right_red();
	}
	cmd_action_group_speed(0x00,175);
	cmd_action_group_run(0x00,1);
	delay_ms(700);
	
}

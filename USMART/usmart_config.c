#include "usmart.h"
#include "usmart_str.h"
#include "main.h"
////////////////////////////用户配置区///////////////////////////////////////////////
//这下面要包含所用到的函数所申明的头文件(用户自己添加) 
#include "wheel_config.h"
#include "wheel_pwm.h"
#include "wheel.h"
#include "wheel_task.h"
#include "turn_task.h"
#include "lsc.h"
								 
extern void led_set(u8 sta);
extern void test_fun(void(*ledset)(u8),u8 sta);										  
//函数名列表初始化(用户自己添加)
//用户直接在这里输入要执行的函数名及其查找串
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//如果使能了读写操作
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif		   
	
    (void*)set_motor1val,"void set_motor1val(uint16_t val)",
	  (void*)set_motor_speed,"void set_motor_speed(uint_16 num, int32_t speed)",
		(void*)set_chassis_speed,"void set_chassis_speed (float x, float y, float w)",
		(void*)set_motor,"void set_motor(uint16_t speed)",
		(void*)move_by_encoder,"void move_by_encoder(int  direct, int val)",
//		(void*)set_motor1_pid,"void set_motor1_pid(uint16_t num,float p,float i,float d)",
		(void*)span,"void span(int store_id)",
		(void*)servogroup_Init,"void servogroup_Init(void)",
};						  
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//函数控制管理器初始化
//得到各个受控函数的名字
//得到函数总数量
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//函数数量
	0,	  	//参数数量
	0,	 	//函数ID
	1,		//参数显示类型,0,10进制;1,16进制
	0,		//参数类型.bitx:,0,数字;1,字符串	    
	0,	  	//每个参数的长度暂存表,需要MAX_PARM个0初始化
	0,		//函数的参数,需要PARM_LEN个0初始化
};   




















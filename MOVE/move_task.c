#include<move_task.h> 
#include<main,h>

/**********************************************************************
  * 函数名：hit_baffle_red
  * 描述: 撞击挡板
  * 参数：无
  * 返回值:无
***********************************************************************/
void hit_baffle_red()
{
 	 while(1) 
	  {
      set_chassis_speed(-50, 0, 0);
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 1&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0) {
          set_chassis_speed(-15, 0, -10);
        }
        
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 0&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 1) {
          set_chassis_speed(-15, 0, 10);
        }
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 1&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 1)break;
	  }
     while(1) 
	 {
       set_chassis_speed(-50, -30, 0);
       if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 1) break;
     }	
}

/**********************************************************************
  * 函数名：runto_stile
  * 描  述:到阶梯去 
  * 参  数:无
  * 返回值:无
***********************************************************************/
void runto_stile_red()
{
	 set_chassis_speed(-20,0,0);
	 HAL_Delay(500);
	 set_chassis_speed(-50,0,0);
	 HAL_Delay(1800);
	 set_chassis_speed(0,100,0);
	 HAL_Delay(3500);//走到阶梯平台前面
}

#include "bar.h"
#include <stdbool.h>
#include "usart.h"

//test
/* 定义并初始化接收循迹板信息结构体 */
TRACKINGBOARD_t row_bar = {
    .id = ROW_BAR,
    .ttl_msg = {0},
    .div = 0,
};

TRACKINGBOARD_t vertical_bar = {
    .id = VERTICAL_BAR,
    .ttl_msg = {0},
    .div = 0,
};


bool rowbar[9]={0};
bool verticalbar[9]={0};

//横向循迹板
#define    read_PD8_in      HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)         //D1
#define    read_PB15_in     HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)        //D2
#define    read_PB12_in     HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)        //D3
#define    read_PA15_in     HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15)        //D4
#define    read_PB13_in     HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)        //D5
#define    read_PD3_in      HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3)         //D6
#define    read_PD1_in      HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_1)         //D7
#define    read_PD0_in      HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)         //D8


//纵向循迹板  JP4
#define    read_PE10_in      HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_10)         //D1
#define    read_PA8_in       HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)          //D2
#define    read_PC9_in       HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9)          //D3
#define    read_PE15_in      HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_15)         //D4
#define    read_PD15_in      HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_15)         //D5
#define    read_PD14_in      HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_14)         //D6
#define    read_PD10_in      HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_10)         //D7
#define    read_PE12_in      HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)         //D8



/**********************************************************************
 * @Name    read_rowbar
 * @declaration : 读取横向循迹板激光检测返回电平状态 ###黑色返回0 白色返回1###
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void read_rowbar()
{
    row_bar.ttl_msg[1] = !read_PD8_in;                  
    row_bar.ttl_msg[2] = !read_PB15_in;
    row_bar.ttl_msg[3] = !read_PB12_in;
    row_bar.ttl_msg[4] = !read_PA15_in;
    row_bar.ttl_msg[5] = !read_PB13_in;
    row_bar.ttl_msg[6] = !read_PD3_in;
    row_bar.ttl_msg[7] = !read_PD1_in;
    row_bar.ttl_msg[8] = !read_PD0_in;
}

/**********************************************************************
 * @Name    read_verticalbar
 * @declaration : 读取纵向循迹板激光检测返回电平状态 ###黑色返回0 白色返回1###
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void read_verticalbar()
{
    vertical_bar.ttl_msg[1] = !read_PE10_in;                  
    vertical_bar.ttl_msg[2] = !read_PA8_in;
    vertical_bar.ttl_msg[3] = !read_PC9_in;
    vertical_bar.ttl_msg[4] = !read_PE15_in;
    vertical_bar.ttl_msg[5] = !read_PD15_in;
    vertical_bar.ttl_msg[6] = !read_PD14_in;
    vertical_bar.ttl_msg[7] = !read_PD10_in;
    vertical_bar.ttl_msg[8] = !read_PE12_in;
}

/**********************************************************************
 * @Name    send_rowbar_message
 * @declaration : 向主控发送循迹信息
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void send_rowbar_message()
{
    uint8_t i=0,rowbar_cnt=0;
    
	for(i=1;i<9;i++)
    {
    	if(row_bar.ttl_msg[i]==1)
    	{
    		
			rowbar_cnt++;
    		
    	}
    }
				
		HAL_UART_Transmit(&huart1, &rowbar_cnt, 1, 0xffff);
		rowbar_cnt=0;
}

/**********************************************************************
 * @Name    send_verticalbar_message
 * @declaration : 向主控发送循迹信息
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void send_verticalbar_message()
{
    uint8_t i=0,verticalbar_cnt=0;
    
	for(i=1;i<9;i++)
    {
    	if(vertical_bar.ttl_msg[i]==1)
    	{
    		
			verticalbar_cnt++;
    		
    	}
    }
				
		HAL_UART_Transmit(&huart1, &verticalbar_cnt, 1, 0xffff);
		verticalbar_cnt=0;
}

/**********************************************************************
 * @Name    count_verticalbar_message
 * @declaration : 计算竖循迹板有几根管在白线上 
 * @param   None
 * @retval   : verticalbar_cnt 计算结果
 * @author  hoson_stars
 ***********************************************************************/
int count_verticalbar_message()
{
    int i=0,verticalbar_cnt=0;
    
	for(i=1;i<9;i++)
    {
    	if(vertical_bar.ttl_msg[i]==1)
    	{
    		
			verticalbar_cnt++;
    		
    	}
    }
		return verticalbar_cnt;
}

/**********************************************************************
 * @Name   count_rowbar_message
 * @declaration : 计算横循迹板有几根管在白线上 
 * @param   None
 * @retval   : verticalbar_cnt 计算结果
 * @author  hoson_stars
 ***********************************************************************/
int count_rowbar_message()
{
    int i=0,rowbar_cnt=0;
    
	for(i=1;i<9;i++)
    {
    	if(row_bar.ttl_msg[i]==1)
    	{
    		
			rowbar_cnt++;
    		
    	}
    }
		return rowbar_cnt;
}


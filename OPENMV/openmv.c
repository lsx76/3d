#include "openmv.h"
#include "time_delay.h"

#define HeadByte1  0x2C      //传输数据帧帧头1
#define HeadByte2  0x12      //传输数据帧帧头2
#define CmdByte    0x01      //传输数据帧命令帧
#define StatusByte 0x02      //传输数据帧状态帧
#define EndByte    0x5B      //传输数据帧帧尾

/* 定义openmv信息结构体 */
OPENMV_t openmv;


uint8_t OPENMV_Rx_BUF[OPENMV_Rx_MAX_DATA_SIZE] = {0};





/**********************************************************************
  * 函数名：Get_openmv
  * 描述: 解析出openmv发回的状态
  * 参数：openmv信息结构体
  * 返回值:无
***********************************************************************/
void Get_openmv(OPENMV_t *openmv)
{
	
        if((OPENMV_Rx_BUF[0] == HeadByte1) && 
            (OPENMV_Rx_BUF[1] == HeadByte2) && 
             (OPENMV_Rx_BUF[2] == StatusByte) &&
              (OPENMV_Rx_BUF[4] == EndByte)) {
                openmv->message = OPENMV_Rx_BUF[3];
        }
}

/**********************************************************************
  * 函数名：tell_openmv_to_distinguish_Strip
  * 描述: 告诉openmv 机械臂已经升起 可以开始识别条形平台
  * 参数：无
  * 返回值:无
***********************************************************************/
void tell_openmv_to_distinguish_Strip()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x01;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * 函数名：tell_openmv_to_loosen
  * 描述: 告诉openmv 机械臂已经放下 可以松开爪子
  * 参数：无
  * 返回值:无
***********************************************************************/
void tell_openmv_to_loosen()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x02;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,200);
}

/**********************************************************************
  * 函数名：tell_openmv_to_loosen
  * 描述: 告诉openmv 机械臂已经放下 可以松开爪子
  * 参数：无
  * 返回值:无
***********************************************************************/
void tell_openmv_to_loosen2()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x09;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,200);
}

/**********************************************************************
  * 函数名：tell_openmv_to_loosen
  * 描述: 告诉openmv 机械臂已经放下 可以松开爪子
  * 参数：无
  * 返回值:无
***********************************************************************/
void tell_openmv_to_loosen3()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x0A;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,200);
}

/**********************************************************************
  * 函数名：tell_openmv_to_distinguish_Stepped
  * 描述: 告诉openmv 机械臂已经升起 可以开始识别阶梯平台
  * 参数：无
  * 返回值:无
***********************************************************************/
  void tell_openmv_to_distinguish_Stepped()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x03;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * 函数名：tell_claw_to_catch()
  * 描述: 机械臂已下降到阶梯平台对应高度 告诉爪子可以抓取
  * 参数：无
  * 返回值:无
***********************************************************************/
void tell_claw_to_catch()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x04;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
	  delay_ms(100);
}

/**********************************************************************
  * 函数名：distinguish_red
  * 描述: 告知爪子 识别红球
  * 参数：无
  * 返回值:无
***********************************************************************/
void distinguish_red()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x05;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * 函数名：distinguish_blue
  * 描述: 告知爪子 识别蓝球
  * 参数：无
  * 返回值:无
***********************************************************************/
void distinguish_blue()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x06;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * 函数名：tell_openmv_to_transfer
  * 描述: 告知openmv  开始倒垛的识别
  * 参数：无
  * 返回值:无
***********************************************************************/
void tell_openmv_to_transfer()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x07;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * 函数名：tell_openmv_to_catch_stake()
  * 描述: 告知openmv  开始立桩的识别
  * 参数：无
  * 返回值:无
***********************************************************************/
void tell_openmv_to_catch_stake()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x08;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * 函数名：tell_openmv_to_transfer_blue()
  * 描述: 告知openmv  开始蓝半场倒剁的识别
  * 参数：无
  * 返回值:无
***********************************************************************/
void tell_openmv_to_transfer_blue()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x09;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * 函数名：tell_openmv_to_transfer_red()
  * 描述: 告知openmv  开始红半场倒剁的识别
  * 参数：无
  * 返回值:无
***********************************************************************/
void tell_openmv_to_transfer_red()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x00;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

void tell_openmv_to_catch_red_disc()
{
    uint8_t command[5];
    command[0] = 0x2C; 
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x0A;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000); 
}








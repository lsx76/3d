

/****************************************_HOSON-----------2022.8.20**************************************************************/

#include"m294.h" 
#include"usart.h"
#include"time_delay.h"


unsigned char Uart6RxBuf[UART6_RX_BUF_LEN];
unsigned char Uart6RxDataConut = 0;
unsigned char Rx6Flag = 0;
unsigned char ballID[16]={0};
extern uint8_t M294_Rx_buffer;

/**********************************************************************
 * @Name    ReadBlockData
 * @declaration : 获取小球ic卡中指定扇区指定快的数据
 * @param   ballID 小球id结构体
 * @retval   : status 获取状态
 * @author  hoson_stars
 ***********************************************************************/
unsigned char ReadBlockData(unsigned char *ballID)
{
	unsigned char status;
	unsigned char i;
	unsigned char pkt[22];
	status = STATUS_ERR;
	if(Uart6RxDataConut > 0) //判断串口是否接收到数据
	{
		if(Rx6Flag == 1)//判断串口是否接收到一帧完整数据
		{	
			Rx6Flag = 0;
			for(i=0;i<22;i++) //自动读数据块的数据包长度固定为22字节
			{
				pkt[i] = Uart6RxBuf[i]; //将串口接收数组内的数据复制到pkt数组中
			}
			if(pkt[21] == 0xCE)  //判断校验和是否正确
			{
				if(pkt[4] == STATUS_OK)	//判断是否正确的读到卡
				{
					//04 16 03 20 00 22 22 22 22 22 22 22 22 22 22 22 22 22 22 22 22 CE 
					if((pkt[0] == 0x04)&&(pkt[1] == 0x16)&&(pkt[2] == 0x03)&&(pkt[3] == 0x20))//对数据包进行判断
					{
						for(i=0;i<16;i++)//获取16字节数据
						{
							ballID[i] = pkt[i+5];//从数组的第5个字节开始为数据，共16字节
						}
						status = STATUS_OK;		 //成功返回0
					}
				}
			}
					for(i=0;i<Uart6RxDataConut;i++)//清空串口接收数组
		{
			Uart6RxBuf[i] = 0x00; 
		}
		Uart6RxDataConut = 0x00;
		}
 	} 
	return status;			//返回状态
}

/**********************************************************************
 * @Name    recivem294_IRQ
 * @declaration : 将读取读数据逐个存到数组中
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void recivem294_IRQ(void)
{	
	Uart6RxBuf[Uart6RxDataConut]=M294_Rx_buffer;
	Uart6RxDataConut++;
	if(Uart6RxDataConut >= UART6_RX_BUF_LEN)
	{
		Uart6RxDataConut = 0;
	}
	if(Uart6RxDataConut == 0x16)
	{
		Rx6Flag = 1;
	}
	
  HAL_UART_Receive_IT(&huart6,&M294_Rx_buffer, 1);
}

/**********************************************************************
 * @Name    send_ballID
 * @declaration : 将获取到的小球id发送到上位机
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void send_ballID(uint8_t *ballID)
{
	uint8_t ballid=0;
	ballid=ballID[1];
	HAL_UART_Transmit(&huart1,&ballid,1,0xffff);
}


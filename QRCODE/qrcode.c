#include "qrcode.h"
#include "stdio.h"


QRCODE_t qrcode ;

/* 数据包最大信息长度 */
#define QRCODE_Rx_MAX_DATA_SIZE 20


unsigned char Uart2RxDataConut = 0;
uint8_t QRCODE_Rx_BUF[QRCODE_Rx_MAX_DATA_SIZE] = {0};
unsigned char Rx2Flag = 0;

/**********************************************************************
  * 函数名：Get_qrcode
  * 描述: 解析出二维码发回数据
  * 参数：二维码信息结构体
  * 返回值:无 
***********************************************************************/
uint8_t Get_qrcode(QRCODE_t *qrcode)
{
	uint8_t qrstatus;
	qrstatus = 0x00;
	if(Rx2Flag == 1)
	{
		Rx2Flag = 0;
		if(QRCODE_Rx_BUF[0] == 'H'&&QRCODE_Rx_BUF[1] == 'E'&&QRCODE_Rx_BUF[2] == 'A'&&QRCODE_Rx_BUF[3] == 'D')
			{
				if(QRCODE_Rx_BUF[5] == 'T'&&QRCODE_Rx_BUF[6] == 'A'&&QRCODE_Rx_BUF[7] == 'I'&&QRCODE_Rx_BUF[8] == 'L')
				{
					qrcode->message = QRCODE_Rx_BUF[4];        //二维码传回的是字符类型
					qrstatus = 0x01;
					printf("ok!");
				}
			}
			for(int i = 0;i < 9; i++)
			{
				QRCODE_Rx_BUF[i]=0x00;
			}
			Uart2RxDataConut = 0;
		}
	return qrstatus;
}

/**********************************************************************
  * 函数名：QR_trigger_1
  * 描述: 发送设置码 命令触发1模式（发送命令后触发识读，当识读成功或者
          超过“单次识读时长”或者收到“命令触发停止”后，设备停止识读）
  * 参数：无
  * 返回值:无
***********************************************************************/
void QR_trigger_1(){  
	uint8_t command[12]={'$','1','0','8','0','0','0','-','A','D','B','0'};      //发送二维码请求命令$108000-ADB0
    HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
  * 函数名：QR_trigger_2
  * 描述: 发送命令后触发持续识读，只有当发送“命令触发停止”后设备才会停止识读；
  * 参数：无
  * 返回值:无
***********************************************************************/
void QR_trigger_2(){
	uint8_t command[12]={'$','1','0','8','0','0','1','-','9','E','8','0'};      //发送二维码请求命令$108000-ADB0
    HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
  * 函数名：QR_trigger_2
  * 描述: 发送命令后触发持续识读，只有当发送“命令触发停止”后设备才会停止识读；
  * 参数：无
  * 返回值:无
***********************************************************************/
void QR_trigger_stop(){
	uint8_t command[12]={'$','1','0','8','0','0','3','-','F','8','E','3'};      //发送二维码请求命令$108000-ADB0
    HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
  * 函数名：QR_restart
  * 描述: 重启二维码设备
  * 参数：无
  * 返回值:无
***********************************************************************/
void QR_restart(){  
	uint8_t command[12]={'$','0','1','0','5','0','0','-','E','E','1','9'};      //发送二维码重启命令
    HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
  * 函数名：QR_user
  * 描述: 恢复用户默认设置
  * 参数：无
  * 返回值:无
***********************************************************************/
void QR_restore_default(){     
	uint8_t command[12]={'$','0','1','0','2','0','2','-','D','9','5','6'};      //恢复用户设置
    HAL_UART_Transmit(&huart7,command,12,500);
}

void send_qrcode(QRCODE_t *qrcode)
{
	uint8_t num=0;
	num=qrcode->message;
	HAL_UART_Transmit(&huart1,&num,1,0xffff); 
}




void reciveqrcode_IRQ(void)
{
// 	QRCODE_Rx_BUF[Uart2RxDataConut]=qrcode_Rx_buffer;
//	Uart2RxDataConut++;
//	if(Uart2RxDataConut >= QRCODE_Rx_MAX_DATA_SIZE)
//	{
//		Uart2RxDataConut = 0;
//	}
//	if(Uart2RxDataConut == 0x09) 
//	{
//		Rx2Flag = 1;
//	}
//  HAL_UART_Receive_IT(&huart7,&qrcode_Rx_buffer, 1);
	printf("ok");
}

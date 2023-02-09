#include "qrcode.h"
#include "stdio.h"


QRCODE_t qrcode ;

/* 数据包最大信息长度 */
#define QRCODE_Rx_MAX_DATA_SIZE 20


unsigned char Uart2RxDataConut = 0;
uint8_t QRCODE_Rx_BUF[QRCODE_Rx_MAX_DATA_SIZE] = {0};
unsigned char Rx2Flag = 0;

/**********************************************************************
 * @Name    Get_qrcode
 * @declaration : 解析二维码模块发回的数据
 * @param   qrcode 二维码信息结构体
 * @retval   : 无
 * @author  hoson_stars
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
 * @Name    QR_trigger_1
 * @declaration : 设置二维码识读模式1（发送命令后触发识读，当识读成功或者
                 超过“单次识读时长”或者收到“命令触发停止”后，设备停止识读）
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void QR_trigger_1(){  
	uint8_t command[12]={'$','1','0','8','0','0','0','-','A','D','B','0'};      //发送二维码请求命令$108000-ADB0
  HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
 * @Name    QR_trigger_2
 * @declaration : 设置二维码识读模式2（发送命令后触发持续识读，只有当发送
 *                “命令触发停止”后设备才会停止识读）
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void QR_trigger_2(){
	uint8_t command[12]={'$','1','0','8','0','0','1','-','9','E','8','0'};      //发送二维码请求命令$108000-ADB0
  HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
 * @Name    QR_trigger_stop
 * @declaration : 设置二维码停止识读
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void QR_trigger_stop(){
	uint8_t command[12]={'$','1','0','8','0','0','3','-','F','8','E','3'};      //发送二维码请求命令$108000-ADB0
  HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
 * @Name    QR_restart
 * @declaration : 重启二维码设备
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void QR_restart(){  
	uint8_t command[12]={'$','0','1','0','5','0','0','-','E','E','1','9'};      //发送二维码重启命令
  HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
 * @Name    QR_restore_default
 * @declaration : 回复用户设置
 * @param   None
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void QR_restore_default(){     
	uint8_t command[12]={'$','0','1','0','2','0','2','-','D','9','5','6'};      //恢复用户设置
  HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
 * @Name    send_qrcode
 * @declaration : 向上位机发送获取到的二维码信息
 * @param   qrcode 二维码信息结构体
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void send_qrcode(QRCODE_t *qrcode)
{
	uint8_t num=0;
	num=qrcode->message;
	HAL_UART_Transmit(&huart1,&num,1,0xffff); 
}


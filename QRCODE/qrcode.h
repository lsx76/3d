#ifndef __QRCODE_H__
#define __QRCODE_H__

#include "usart.h"
#include <stdbool.h>

extern uint8_t qrcode_Rx_buffer;

typedef struct {
    UART_HandleTypeDef *huart;
    uint8_t message;
    bool status;
		uint8_t last_message;
} QRCODE_t;

extern QRCODE_t qrcode;

uint8_t Get_qrcode(QRCODE_t *qrcode);
void QR_trigger_1(void);
void QR_restart(void);
void QR_restore_default(void);
void QR_trigger_2(void);
void QR_trigger_stop(void);
void send_qrcode(QRCODE_t *qrcode);
void reciveqrcode_IRQ(void);
#endif


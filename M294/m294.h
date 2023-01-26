#ifndef UART_H
#define UART_H

#define UART6_RX_BUF_LEN  30

#define STATUS_OK     0x00
#define STATUS_ERR    0x01

extern unsigned char ballID[16];


unsigned char ReadBlockData(unsigned char *ballID);
unsigned char RxCheckSum(unsigned char *ptr,unsigned char len);
void recivem294_IRQ(void);
void send_ballID(unsigned char *ballID);


#endif


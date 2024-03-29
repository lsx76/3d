#ifndef __OPENMV_H__
#define __OPENMV_H__

#include "usart.h"
#include <stdbool.h>

typedef struct {
    UART_HandleTypeDef *huart;
    uint8_t message;
    bool status;
} OPENMV_t;

#define OPENMV_Rx_MAX_DATA_SIZE 6
extern OPENMV_t openmv;
extern uint8_t OPENMV_Rx_BUF[OPENMV_Rx_MAX_DATA_SIZE];

void Get_openmv(OPENMV_t *openmv);

void tell_openmv_to_distinguish_Strip(void);
void tell_openmv_to_distinguish_Stepped(void);
void tell_openmv_to_loosen(void);
void tell_claw_to_catch(void);
void distinguish_red(void);
void distinguish_blue(void);
void tell_openmv_to_transfer(void);
void tell_openmv_to_catch_stake(void);
void tell_openmv_to_loosen2(void);
void tell_openmv_to_loosen3(void);

void tell_openmv_to_transfer_blue(void);
void tell_openmv_to_transfer_red(void);

void tell_openmv_to_catch_red_disc(void);
#endif


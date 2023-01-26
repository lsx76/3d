#ifndef __BAR_H__
#define __BAR_H__

#include "stm32f7xx_hal.h"
#include <stdbool.h>

/* 循迹板id信息 */
typedef enum {      
    ROW_BAR,
    VERTICAL_BAR,
} bar_id_t;

typedef struct {
  UART_HandleTypeDef *huart;//没用 
  int16_t div;
  bar_id_t id;//可能有用 
  bool ttl_msg[9];//看怎么把原来写的转化到这里来 
  bool status;
} TRACKINGBOARD_t;

extern TRACKINGBOARD_t row_bar;
extern TRACKINGBOARD_t vertical_bar;

void read_rowbar(void);
void read_verticalbar(void);
int count_verticalbar_message(void);
int count_rowbar_message(void);
void send_verticalbar_message(void);
void send_rowbar_message(void);

#endif

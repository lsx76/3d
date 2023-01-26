#ifndef __TRACKBOARD_H__
#define __TRACKBOARD_H__

#include "usart.h"
#include <stdbool.h>

/* 循迹板id信息 */
typedef enum {      
    ROW_BAR,
    VERTICAL_BAR,
} bar_id_t;

/* 循迹板总信息 */
typedef struct {
  UART_HandleTypeDef *huart;//没用 
  int16_t div;
  bar_id_t id;//可能有用 
  bool ttl_msg[9];//看怎么把原来写的转化到这里来 
  bool status;
} TRACKINGBOARD_t;

extern TRACKINGBOARD_t row_bar;
extern TRACKINGBOARD_t vertical_bar;

void receive_trackboard_Init(TRACKINGBOARD_t *trackboard);//初始化dma，没用 
void receive_trackboard_IRQ(TRACKINGBOARD_t *trackboard);//dma中断没用 
void Get_trackboard(TRACKINGBOARD_t *trackboard);//解码 
#endif

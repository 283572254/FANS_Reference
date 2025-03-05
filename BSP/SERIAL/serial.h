#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "main.h"


/************************* 可移植的串口配置 *************************/


extern uint8_t g_data_ready_flag;      // 数据接收完成标志位
#define UART_DMA_BUFFER_SIZE 256    // DMA接收缓冲区大小
#define BUFFER_SIZE 256            // 发送缓冲区大小
#define DMA_TX_BUFFER_SIZE 32  // DMA 发送缓冲区大小


extern uint8_t uart_rx_dma_buffer[UART_DMA_BUFFER_SIZE];  // DMA接收缓冲区

void UART_Driver_Init(UART_HandleTypeDef *huart) ;
#endif




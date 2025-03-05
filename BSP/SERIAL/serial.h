#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "main.h"


/************************* ����ֲ�Ĵ������� *************************/


extern uint8_t g_data_ready_flag;      // ���ݽ�����ɱ�־λ
#define UART_DMA_BUFFER_SIZE 256    // DMA���ջ�������С
#define BUFFER_SIZE 256            // ���ͻ�������С
#define DMA_TX_BUFFER_SIZE 32  // DMA ���ͻ�������С


extern uint8_t uart_rx_dma_buffer[UART_DMA_BUFFER_SIZE];  // DMA���ջ�����

void UART_Driver_Init(UART_HandleTypeDef *huart) ;
#endif




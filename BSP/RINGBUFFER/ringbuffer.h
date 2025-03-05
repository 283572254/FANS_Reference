#ifndef RINGBUFFER_H
#define RINGBUFFER_H
#include "main.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h> 


/************************* ����ֲ�Ĵ������� *************************/
// #define USART_INSTANCE    USART2           // Ĭ�ϴ���Ϊ USART2���޸�Ϊ��������ʱ��ֻ��Ҫ�޸���һ��
// #define USART_HANDLE      huart2           // ���ھ��
// #define DMA_INSTANCE      hdma_usart2_rx   // DMAʵ��
// #define RX_DMA_BUFFER     uart_rx_dma_buffer  // ����DMA������
// #define USART_IRQn        USART2_IRQn      // �����жϺ�


/***************************  ���λ����� ***************************/
#define RINGBUFFER_SIZE 256  // �����������û�������С
typedef struct {
    uint32_t w;                        // дָ��
    uint32_t r;                        // ��ָ��
    uint8_t buffer[RINGBUFFER_SIZE];   // ���ݴ洢������
    uint32_t itemCount;                // ��ǰ������������
} ringbuffer_t;

/***************************  ���λ�����ȫ�ֱ��� **********/

extern ringbuffer_t husart_rx_rb;  // ���ջ��λ�����
extern ringbuffer_t husart_tx_rb;  // ���ͻ��λ�����

/***************************  ���λ�����API ***************************/
void ringbuffer_init(ringbuffer_t *rb);
bool ringbuffer_is_empty(ringbuffer_t *rb);
bool ringbuffer_is_full(ringbuffer_t *rb);
uint32_t ringbuffer_write(ringbuffer_t *rb, uint8_t data);
uint32_t ringbuffer_read(ringbuffer_t *rb, uint8_t *data);
/*************************** ����DMA��ʼ�� ***************************/
// void UART_DMA_Init(UART_HandleTypeDef *huart) ;
// void u_SendArray(uint8_t *array, uint16_t len);



#endif  // RINGBUFFER_H


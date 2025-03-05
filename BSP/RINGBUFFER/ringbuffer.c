#include "../BSP/RINGBUFFER/ringbuffer.h"
#include "usart.h"

ringbuffer_t husart_rx_rb;  // 接收环形缓冲区
ringbuffer_t husart_tx_rb;  // 发送环形缓冲区




void ringbuffer_init(ringbuffer_t *rb) {
    rb->w = 0;
    rb->r = 0;
    rb->itemCount = 0;
}

bool ringbuffer_is_empty(ringbuffer_t *rb) {
    return rb->itemCount == 0;
}

bool ringbuffer_is_full(ringbuffer_t *rb) {
    return rb->itemCount == RINGBUFFER_SIZE;
}

uint32_t ringbuffer_write(ringbuffer_t *rb, uint8_t data) {
    if (ringbuffer_is_full(rb)) {
        return 0;
    }
    
    rb->buffer[rb->w] = data;
    rb->w = (rb->w + 1) % RINGBUFFER_SIZE;
    rb->itemCount++;
    return 1;
}

uint32_t ringbuffer_read(ringbuffer_t *rb, uint8_t *data) {
    if (ringbuffer_is_empty(rb)) {
        return 0;
    }
    
    *data = rb->buffer[rb->r];
    rb->r = (rb->r + 1) % RINGBUFFER_SIZE;
    rb->itemCount--;
    return 1;
}





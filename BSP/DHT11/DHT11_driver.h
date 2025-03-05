#ifndef DHT11_DRIVER_H_
#define DHT11_DRIVER_H_

#include "main.h"




// DHT11���ݽṹ
typedef struct {
    uint8_t humidity;    // ʪ��
    uint8_t temperature; // �¶�
} DHT11_Data_t;

// DHT11��ʼ��
void DHT11_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

// ��ȡDHT11����
uint8_t DHT11_Read(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,DHT11_Data_t *data);


#endif // !DHT11_DRIVER_H_

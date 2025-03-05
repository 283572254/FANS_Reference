#ifndef DHT11_DRIVER_H_
#define DHT11_DRIVER_H_

#include "main.h"




// DHT11数据结构
typedef struct {
    uint8_t humidity;    // 湿度
    uint8_t temperature; // 温度
} DHT11_Data_t;

// DHT11初始化
void DHT11_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

// 读取DHT11数据
uint8_t DHT11_Read(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,DHT11_Data_t *data);


#endif // !DHT11_DRIVER_H_

#ifndef LED_DRIVER_H
#define LED_DRIVER_H
#include "main.h"

// LED配置结构体
typedef struct {
    GPIO_TypeDef *GPIOx;  // GPIO端口（如GPIOA）
    uint16_t GPIO_Pin;    // GPIO引脚（如GPIO_PIN_5）
} LED_ConfigTypeDef;

// LED句柄
typedef struct {
    LED_ConfigTypeDef config;
} LED_HandleTypeDef;

// 打开LED
void LED_On(LED_HandleTypeDef *hled);
void LED_Off(LED_HandleTypeDef *hled);
void LED_Toggle(LED_HandleTypeDef *hled);

void LED_Init(LED_HandleTypeDef *hled);
// PWM调光初始化（需要定时器和通道）
void LED_PWM_Init(TIM_HandleTypeDef *htim, uint32_t Channel);

// 设置PWM占空比（0-100）
void LED_SetBrightness(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t brightness);

#endif /* LED_DRIVER_H */








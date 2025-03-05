#ifndef LED_DRIVER_H
#define LED_DRIVER_H
#include "main.h"

// LED���ýṹ��
typedef struct {
    GPIO_TypeDef *GPIOx;  // GPIO�˿ڣ���GPIOA��
    uint16_t GPIO_Pin;    // GPIO���ţ���GPIO_PIN_5��
} LED_ConfigTypeDef;

// LED���
typedef struct {
    LED_ConfigTypeDef config;
} LED_HandleTypeDef;

// ��LED
void LED_On(LED_HandleTypeDef *hled);
void LED_Off(LED_HandleTypeDef *hled);
void LED_Toggle(LED_HandleTypeDef *hled);

void LED_Init(LED_HandleTypeDef *hled);
// PWM�����ʼ������Ҫ��ʱ����ͨ����
void LED_PWM_Init(TIM_HandleTypeDef *htim, uint32_t Channel);

// ����PWMռ�ձȣ�0-100��
void LED_SetBrightness(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t brightness);

#endif /* LED_DRIVER_H */








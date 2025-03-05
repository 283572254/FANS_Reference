#include "../BSP/LED/Led_driver.h"
// ��̬��������LED����
static LED_ConfigTypeDef LED_Config;


void LED_Init(LED_HandleTypeDef *hled)
{
    // �����û�����
    LED_Config.GPIOx = hled->config.GPIOx;
    LED_Config.GPIO_Pin = hled->config.GPIO_Pin;
 
    // ����GPIOʱ��
    if (LED_Config.GPIOx == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (LED_Config.GPIOx == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } // ����GPIO�˿�����

    // ����GPIO����
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED_Config.GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_Config.GPIOx, &GPIO_InitStruct);
}

// ��LED
void LED_On(LED_HandleTypeDef *hled) {
    HAL_GPIO_WritePin(hled->config.GPIOx, hled->config.GPIO_Pin, GPIO_PIN_SET);
}

// �ر�LED
void LED_Off(LED_HandleTypeDef *hled) {
    HAL_GPIO_WritePin(hled->config.GPIOx, hled->config.GPIO_Pin, GPIO_PIN_RESET);
}

// �л�LED״̬
void LED_Toggle(LED_HandleTypeDef *hled) {
    HAL_GPIO_TogglePin(hled->config.GPIOx, hled->config.GPIO_Pin);
}
// PWM�����ʼ������Ҫ��ʱ����ͨ����
void LED_PWM_Init(TIM_HandleTypeDef *htim, uint32_t Channel) {
    // ����PWM
    HAL_TIM_PWM_Start(htim, Channel);
}

// ����PWMռ�ձȣ�0-100��
void LED_SetBrightness(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t brightness) {
    if (brightness > 100) brightness = 100;  // ���Ʒ�Χ

    // ����ռ�ձȶ�Ӧ��CCRֵ
    uint32_t pulse = (htim->Instance->ARR * brightness) / 100;
    __HAL_TIM_SET_COMPARE(htim, Channel, pulse);
}










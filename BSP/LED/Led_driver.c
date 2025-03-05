#include "../BSP/LED/Led_driver.h"
// 静态变量保存LED配置
static LED_ConfigTypeDef LED_Config;


void LED_Init(LED_HandleTypeDef *hled)
{
    // 保存用户配置
    LED_Config.GPIOx = hled->config.GPIOx;
    LED_Config.GPIO_Pin = hled->config.GPIO_Pin;
 
    // 启用GPIO时钟
    if (LED_Config.GPIOx == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (LED_Config.GPIOx == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } // 其他GPIO端口类似

    // 配置GPIO引脚
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED_Config.GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_Config.GPIOx, &GPIO_InitStruct);
}

// 打开LED
void LED_On(LED_HandleTypeDef *hled) {
    HAL_GPIO_WritePin(hled->config.GPIOx, hled->config.GPIO_Pin, GPIO_PIN_SET);
}

// 关闭LED
void LED_Off(LED_HandleTypeDef *hled) {
    HAL_GPIO_WritePin(hled->config.GPIOx, hled->config.GPIO_Pin, GPIO_PIN_RESET);
}

// 切换LED状态
void LED_Toggle(LED_HandleTypeDef *hled) {
    HAL_GPIO_TogglePin(hled->config.GPIOx, hled->config.GPIO_Pin);
}
// PWM调光初始化（需要定时器和通道）
void LED_PWM_Init(TIM_HandleTypeDef *htim, uint32_t Channel) {
    // 启动PWM
    HAL_TIM_PWM_Start(htim, Channel);
}

// 设置PWM占空比（0-100）
void LED_SetBrightness(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t brightness) {
    if (brightness > 100) brightness = 100;  // 限制范围

    // 计算占空比对应的CCR值
    uint32_t pulse = (htim->Instance->ARR * brightness) / 100;
    __HAL_TIM_SET_COMPARE(htim, Channel, pulse);
}










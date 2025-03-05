#include "../BSP/KEY/Key_driver.h"




void Button_Init(Button_HandleTypeDef *hButton, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t debounce_time) 
{
    hButton->GPIOx = GPIOx;
    hButton->GPIO_Pin = GPIO_Pin;
    hButton->debounce_time = debounce_time;
    hButton->prev_state = BUTTON_STATE_RELEASED;
    hButton->last_press_time = 0;
    // 启用GPIO时钟
    if (GPIOx == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (GPIOx == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (GPIOx == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } // 其他GPIO端口类似

    // 配置GPIO引脚为输入模式
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;          // 输入模式
    GPIO_InitStruct.Pull = GPIO_PULLUP;              // 无上拉/下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;     // 低速
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// 检测按键事件
Button_Event Button_GetEvent(Button_HandleTypeDef *hButton) 
{
    Button_State current_state = HAL_GPIO_ReadPin(hButton->GPIOx, hButton->GPIO_Pin) == GPIO_PIN_RESET ? BUTTON_STATE_PRESSED : BUTTON_STATE_RELEASED;
    uint32_t current_time = HAL_GetTick();

    // 检测状态变化
    if (current_state != hButton->prev_state) {
        // 去抖动处理
        if (current_time - hButton->last_press_time > hButton->debounce_time) {
            hButton->prev_state = current_state;
            hButton->last_press_time = current_time;

            if (current_state == BUTTON_STATE_PRESSED) {
                return BUTTON_EVENT_PRESSED;  // 按键按下事件
            } else {
                return BUTTON_EVENT_RELEASED; // 按键释放事件
            }
        }
    }

    return BUTTON_EVENT_NONE;  // 无事件
}










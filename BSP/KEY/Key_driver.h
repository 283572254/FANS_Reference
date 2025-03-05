#ifndef __KEY_DRIVER_H__
#define __KEY_DRIVER_H__

#include "main.h"

// 按键状态
typedef enum {
    BUTTON_STATE_RELEASED = 0,  // 按键释放
    BUTTON_STATE_PRESSED        // 按键按下
} Button_State;

// 按键事件
typedef enum {
    BUTTON_EVENT_NONE = 0,      // 无事件
    BUTTON_EVENT_PRESSED,       // 按键按下事件
    BUTTON_EVENT_RELEASED       // 按键释放事件
} Button_Event;

// 按键句柄
typedef struct {
    GPIO_TypeDef *GPIOx;        // GPIO端口
    uint16_t GPIO_Pin;          // GPIO引脚
    Button_State prev_state;    // 上一次的状态
    uint32_t debounce_time;     // 去抖动时间（毫秒）
    uint32_t last_press_time;   // 上一次按下时间
} Button_HandleTypeDef;

// 初始化按键
void Button_Init(Button_HandleTypeDef *hButton, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t debounce_time);

// 检测按键事件
Button_Event Button_GetEvent(Button_HandleTypeDef *hButton);

#endif /* __KEY_DRIVER_H__ */


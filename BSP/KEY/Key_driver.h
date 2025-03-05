#ifndef __KEY_DRIVER_H__
#define __KEY_DRIVER_H__

#include "main.h"

// ����״̬
typedef enum {
    BUTTON_STATE_RELEASED = 0,  // �����ͷ�
    BUTTON_STATE_PRESSED        // ��������
} Button_State;

// �����¼�
typedef enum {
    BUTTON_EVENT_NONE = 0,      // ���¼�
    BUTTON_EVENT_PRESSED,       // ���������¼�
    BUTTON_EVENT_RELEASED       // �����ͷ��¼�
} Button_Event;

// �������
typedef struct {
    GPIO_TypeDef *GPIOx;        // GPIO�˿�
    uint16_t GPIO_Pin;          // GPIO����
    Button_State prev_state;    // ��һ�ε�״̬
    uint32_t debounce_time;     // ȥ����ʱ�䣨���룩
    uint32_t last_press_time;   // ��һ�ΰ���ʱ��
} Button_HandleTypeDef;

// ��ʼ������
void Button_Init(Button_HandleTypeDef *hButton, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t debounce_time);

// ��ⰴ���¼�
Button_Event Button_GetEvent(Button_HandleTypeDef *hButton);

#endif /* __KEY_DRIVER_H__ */


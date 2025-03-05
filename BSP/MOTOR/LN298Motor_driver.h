#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"   

#define MOTOR_USE_GPIO 0

// �������
typedef enum {
    MOTOR_DIR_FORWARD = 0,
    MOTOR_DIR_BACKWARD
} Motor_Direction;

// ������ƽṹ��
typedef struct {
    GPIO_TypeDef *DIR_GPIOx;      // �������GPIO�˿�
    uint16_t DIR_GPIO_Pin;        // �������GPIO����
    GPIO_TypeDef *ENA_GPIOx;       // ʹ��A����GPIO�˿�
    uint16_t ENA_GPIO_Pin;         // ʹ��A����GPIO����
    GPIO_TypeDef *ENB_GPIOx;       // ʹ��B����GPIO�˿�
    uint16_t ENB_GPIO_Pin;         // ʹ��B����GPIO����
    TIM_HandleTypeDef *PWM_htim;  // PWM��ʱ�����
    uint32_t PWM_ChannelP;         // PWMͨ��
    uint32_t PWM_ChannelN;         // PWMͨ��
} Motor_HandleTypeDef;

// ��ʼ��PWM
void PWM_Init(TIM_HandleTypeDef *htim, uint32_t Channel);

// ����PWMռ�ձ�
void PWM_SetDuty(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t duty);

// ��ʼ�����
void Motor_Init(Motor_HandleTypeDef *hMotor);

// ���õ������
void Motor_Set_DieSpeed(Motor_HandleTypeDef *hMotor, Motor_Direction dir, uint8_t speed) ;

// ���õ���ٶ�

#endif /* __MOTOR_H__ */




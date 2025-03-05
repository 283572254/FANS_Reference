#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"   

#define MOTOR_USE_GPIO 0

// 电机方向
typedef enum {
    MOTOR_DIR_FORWARD = 0,
    MOTOR_DIR_BACKWARD
} Motor_Direction;

// 电机控制结构体
typedef struct {
    GPIO_TypeDef *DIR_GPIOx;      // 方向控制GPIO端口
    uint16_t DIR_GPIO_Pin;        // 方向控制GPIO引脚
    GPIO_TypeDef *ENA_GPIOx;       // 使能A控制GPIO端口
    uint16_t ENA_GPIO_Pin;         // 使能A控制GPIO引脚
    GPIO_TypeDef *ENB_GPIOx;       // 使能B控制GPIO端口
    uint16_t ENB_GPIO_Pin;         // 使能B控制GPIO引脚
    TIM_HandleTypeDef *PWM_htim;  // PWM定时器句柄
    uint32_t PWM_ChannelP;         // PWM通道
    uint32_t PWM_ChannelN;         // PWM通道
} Motor_HandleTypeDef;

// 初始化PWM
void PWM_Init(TIM_HandleTypeDef *htim, uint32_t Channel);

// 设置PWM占空比
void PWM_SetDuty(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t duty);

// 初始化电机
void Motor_Init(Motor_HandleTypeDef *hMotor);

// 设置电机方向
void Motor_Set_DieSpeed(Motor_HandleTypeDef *hMotor, Motor_Direction dir, uint8_t speed) ;

// 设置电机速度

#endif /* __MOTOR_H__ */




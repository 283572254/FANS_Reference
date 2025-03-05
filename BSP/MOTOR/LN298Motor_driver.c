#include "../BSP/MOTOR/LN298Motor_driver.h"

// ��ʼ�������������
void Motor_GPIO_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// ��ʼ��PWM
void PWM_Init(TIM_HandleTypeDef *htim, uint32_t Channel) {
    HAL_TIM_PWM_Start(htim, Channel);
}

// ����PWMռ�ձ�
void PWM_SetDuty(TIM_HandleTypeDef *htim, uint32_t Channel, uint8_t duty) {
    if (duty > 100) duty = 100;  // ����ռ�ձȷ�Χ
    uint32_t pulse = (htim->Instance->ARR * duty) / 100;
    __HAL_TIM_SET_COMPARE(htim, Channel, pulse);
}

void Motor_Init(Motor_HandleTypeDef *hMotor) 
{
#if MOTOR_USE_GPIO //�Ƿ���Ҫ���ſ���
    // ��ʼ�������������
    Motor_GPIO_Init(hMotor->DIR_GPIOx, hMotor->DIR_GPIO_Pin);
    //��ʼʹ�ܿ�������
    Motor_GPIO_Init(hMotor->ENA_GPIOx, hMotor->ENA_GPIO_Pin);
#endif
    // ��ʼ��PWM
    PWM_Init(hMotor->PWM_htim, hMotor->PWM_ChannelP);
    PWM_Init(hMotor->PWM_htim, hMotor->PWM_ChannelN);


}

// ���õ��������ٶ�
void Motor_Set_DieSpeed(Motor_HandleTypeDef *hMotor, Motor_Direction dir, uint8_t speed) 
{
    if (dir == MOTOR_DIR_FORWARD) 
    {
        PWM_SetDuty(hMotor->PWM_htim, hMotor->PWM_ChannelP, speed);
        PWM_SetDuty(hMotor->PWM_htim, hMotor->PWM_ChannelN, 0);
    } else 
    {
        PWM_SetDuty(hMotor->PWM_htim, hMotor->PWM_ChannelP, 0);
        PWM_SetDuty(hMotor->PWM_htim, hMotor->PWM_ChannelN, speed);
    }
    
}


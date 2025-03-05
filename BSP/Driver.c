#include "../BSP/Driver.h"
// 定义电机控制句柄
Motor_HandleTypeDef hMotor;
Button_HandleTypeDef hButton1;
Button_HandleTypeDef hButton2;
Button_HandleTypeDef hButton3;
LED_HandleTypeDef hgps_led,hbat_led;
void Driver_Init(void)
{
    
    hgps_led.config.GPIOx = GPS_LED_GPIO_Port;
    hgps_led.config.GPIO_Pin = GPS_LED_Pin;
    hbat_led.config.GPIOx = BAT_LED_GPIO_Port;
    hbat_led.config.GPIO_Pin = BAT_LED_Pin;

    hMotor.PWM_htim = &htim2;  // 假设使用TIM2
    hMotor.PWM_ChannelP = TIM_CHANNEL_1;
    hMotor.PWM_ChannelN = TIM_CHANNEL_2;

    LED_PWM_Init(&htim2,TIM_CHANNEL_3);
    Motor_Init(&hMotor);
    // Initialize the driver here

    LED_Init(&hgps_led);
    LED_Init(&hbat_led);
    Button_Init(&hButton1,KEY1_GPIO_Port,KEY1_Pin,50);
    Button_Init(&hButton2,KEY2_GPIO_Port,KEY2_Pin,50);
    Button_Init(&hButton3,KEY3_GPIO_Port,KEY3_Pin,50);
    delay_init();
    UART_Driver_Init(&huart1);
}




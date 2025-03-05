#include "User_time.h"
#include "tim.h"
#include "User.h"
#include "../BSP/Driver.h"

extern float fvolt_value;
static uint32_t g_u32Userminute = 0;
static UserButton logButton;
static DHT11_Data_t logDHT_date;
extern DHT11_Data_t DHT11_Get(void);

void User_time_init(void)
{
    HAL_TIM_Base_Start_IT(&htim1);
    
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{ 
    static uint16_t count = 0;
    if(htim == &htim1)
    {   
        count++;
        if(count == 1000)
        {
            g_u32Userminute++;
            count = 0;
            logButton = Button_Output();
            logDHT_date = DHT11_Get();
            printf("Log temperature:%d\r\n",logDHT_date.temperature);
            printf("Log Button1:%d\r\n",logButton.button1);
            printf("Log Button2:%d\r\n",logButton.button2);
            printf("Log Button3:%d\r\n",logButton.button3);
            printf("fvolt_value:%f\r\n",fvolt_value);
        }
        if(g_u32Userminute == 2)
        {
            g_u32Userminute = 0;
        }
    }
}








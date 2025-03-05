#include "User.h"
#include "User_time.h"
#include "../BSP/Driver.h"
#include "../USER/Protocol/GPS_protocol.h"
typedef enum {
    FAN_MANUAL_CONTROL = 0,  // 手动控制状态
    FAN_AUTO_CONTROL,        // 自动控制状态
    FAN_DISABLED             // 禁用状态
} Fan_Control_State;

extern Button_HandleTypeDef hButton1;
extern Button_HandleTypeDef hButton2;
extern Button_HandleTypeDef hButton3;
extern Motor_HandleTypeDef hMotor;
extern LED_HandleTypeDef hgps_led,hbat_led;;



static UserButton userButton;
static DHT11_Data_t dht11_data;
static Fan_Control_State fan_state = FAN_AUTO_CONTROL;  // 初始状态为自动控制

static uint32_t last_manual_operation_time = 0;         // 最后一次手动操作时间
static uint32_t last_operation_time = 0;  // 最后一次操作时间
static uint32_t last_auto_off_time = 0;   // 最后一次自动关闭时间
static uint8_t  is_auto_control_enabled = 1; // 温控系统是否启用
static uint32_t adc_value = 0;
float fvolt_value = 0.0;


void User_Buttion_Init(void);
void User_GetButton(UserButton *Button);
void Fan_Control(uint8_t mode);
void Light_Control(uint8_t mode);
void Temperature_Control(void);
void Gps_start(uint8_t mode);

uint32_t Is_Timeout(uint32_t start_time, uint32_t timeout)
{
    return (HAL_GetTick() - start_time) > timeout?  1: 0;
}

void User_Buttion_Init(void)
{
    userButton.button1 = 0;
    userButton.button2 = 0;
    userButton.button3 = 0;
}

void User_Init(void)
{
    // User initialization code here
    Driver_Init();
    User_time_init();
	User_Buttion_Init();
    HAL_ADCEx_Calibration_Start(&hadc1);
	Motor_Set_DieSpeed(&hMotor,MOTOR_DIR_FORWARD,0);
}


void User_GetButton(UserButton *Button)
{
    // User button code here
    Button_Event event1, event2, event3;
    event1 = Button_GetEvent(&hButton1);
    event2 = Button_GetEvent(&hButton2);
    event3 = Button_GetEvent(&hButton3);
    if(event1 == BUTTON_EVENT_RELEASED)
    {
        
        Button->button1++;
        if(Button->button1 > 3)
        {
            Button->button1 = 0;
        }
        Fan_Control(userButton.button1);
    }
    else if(event2 == BUTTON_EVENT_RELEASED)
    {
        Button->button2++;
        if(Button->button2 > 3)
        {
            Button->button2 = 0;
        }
    }
    else if(event3 == BUTTON_EVENT_RELEASED)
    {
        Button->button3++;
        if(Button->button3 > 2)
        {
            Button->button3 = 0;
        }
    }

}

void Fan_Control(uint8_t mode)
{
    switch (mode)
    {
        case 0:
            Motor_Set_DieSpeed(&hMotor,MOTOR_DIR_FORWARD,0);
            break;
        case 1:
            Motor_Set_DieSpeed(&hMotor,MOTOR_DIR_FORWARD,25);
            break;
        case 2:
            Motor_Set_DieSpeed(&hMotor,MOTOR_DIR_FORWARD,50);
            break;
        case 3:
            Motor_Set_DieSpeed(&hMotor,MOTOR_DIR_FORWARD,75);
            break;
        default:
            break;
    }
    fan_state = FAN_MANUAL_CONTROL;
    last_manual_operation_time = HAL_GetTick();
}

void Light_Control(uint8_t mode)
{
    switch (mode)
    {
        case 0:
            LED_SetBrightness(&htim2,TIM_CHANNEL_3,0);
            break;
        case 1:
            LED_SetBrightness(&htim2,TIM_CHANNEL_3,10);
            break;
        case 2:
            LED_SetBrightness(&htim2,TIM_CHANNEL_3,50);
            break;
        case 3:
            LED_SetBrightness(&htim2,TIM_CHANNEL_3,100);
            break;
        default:
            break;
    }
}

void Temperature_Control(void)
{
    

    // 读取温度
    
    if (DHT11_Read(DHT11_DO_GPIO_Port,DHT11_DO_Pin,&dht11_data))
     {
        if (dht11_data.temperature > 30 && is_auto_control_enabled )
         {
            // 温度超过30°C，自动开启低档位风速
            Motor_Set_DieSpeed(&hMotor,MOTOR_DIR_FORWARD,25);
            last_operation_time = HAL_GetTick();;  // 更新操作时间
            is_auto_control_enabled = 0;
        }

    }
    // 检测手动操作是否超时
    if (fan_state == FAN_MANUAL_CONTROL && Is_Timeout(last_manual_operation_time, 120000))
    {  // 2分钟（120秒）
        fan_state = FAN_AUTO_CONTROL;  // 切换到自动控制状态
        is_auto_control_enabled = 1;
    }
    // 检测是否禁用温控系统
    if (fan_state == FAN_DISABLED) 
    {
        if (Is_Timeout(last_auto_off_time, 21600000)) 
        {  // 6小时（21600秒）
            fan_state = FAN_AUTO_CONTROL;  // 重新启用温控系统
        }
    }
    // 检测无人操作
    if (fan_state == FAN_AUTO_CONTROL && Is_Timeout(last_operation_time, 120000)&&is_auto_control_enabled==0)
    {  // 2分钟（120秒）
         // 关闭风扇
        last_auto_off_time = HAL_GetTick(); // 记录自动关闭时间
				Motor_Set_DieSpeed(&hMotor,MOTOR_DIR_FORWARD,0);
        fan_state = FAN_DISABLED;  // 禁用温控系统
    }
   
}


void Gps_start(uint8_t mode)
{
    if(mode == 2)
    {
        LED_On(&hgps_led);
    }
    else
    {
        LED_Off(&hgps_led);
    }
}


uint32_t Adc_get_data(void)
{
        // 启动ADC转换
        if (HAL_ADC_Start(&hadc1) != HAL_OK)
        {
            printf("ADC start error\r\n");
            // 错误处理
        }
    
        // 等待转换完成
        if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK) 
        {
            
            uint32_t adc_value = HAL_ADC_GetValue(&hadc1);  // 获取转换结果
            return adc_value;
        }
        return 0;
}

void Discharge_Control(void)
{
    static uint32_t toggle_time = 0;
    adc_value = Adc_get_data();
    fvolt_value = (float)adc_value * 3.3 / 4095;
    if(fvolt_value < 1.55&&Is_Timeout(toggle_time,1000))
    {
        toggle_time = HAL_GetTick();
        LED_Toggle(&hbat_led);
    }
}

void User_Loop(void)
{
    // User loop code here
    // This function is called in a loop in the main program
    User_GetButton(&userButton);
    Temperature_Control();
    Light_Control(userButton.button2);
    Gps_start(userButton.button3);
    Discharge_Control();
    process_uart_data();

}

UserButton Button_Output(void)
{
    UserButton state = userButton;
    return state;
}

DHT11_Data_t DHT11_Get(void)
{

  return dht11_data;
  
}



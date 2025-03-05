#include "../BSP/DHT11/DHT11_driver.h"
#include "./delay/delay.h"
// 设置GPIO为输出模式
void DHT11_GPIO_Set_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// 设置GPIO为输入模式
void DHT11_GPIO_Set_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) 
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// 从DHT11读取一位数据
static uint8_t DHT11_Read_Bit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    uint8_t retry = 0;
    uint8_t bit = 0;

    // 等待DHT11输出高电平
    while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0 && retry < 100) {
        delay_us(1);
        retry++;
    }
    retry = 0;

    // 延时40us后读取电平
    delay_us(40);
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1) {
        bit = 1;
    }

    // 等待DHT11输出低电平
    while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1 && retry < 100) {
        delay_us(1);
        retry++;
    }
    retry = 0;

    return bit;
}

// 从DHT11读取一字节数据
static uint8_t DHT11_Read_Byte(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    uint8_t byte = 0;
    for (uint8_t i = 0; i < 8; i++) {
        byte <<= 1;
        byte |= DHT11_Read_Bit(GPIOx, GPIO_Pin);
    }
    return byte;
}

// 读取DHT11数据
uint8_t DHT11_Read(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,DHT11_Data_t *data) {
    uint8_t retry = 0;
    uint8_t buffer[5] = {0};

    // 设置GPIO为输出模式
    DHT11_GPIO_Set_Output(GPIOx, GPIO_Pin);

    // 发送开始信号
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
    HAL_Delay(18);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
    delay_us(20);

    // 设置GPIO为输入模式
    DHT11_GPIO_Set_Input(GPIOx, GPIO_Pin);

    // 等待DHT11响应
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0) {
        while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0 && retry < 100) {
            delay_us(1);
            retry++;
        }
        retry = 0;
        while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1 && retry < 100) {
            delay_us(1);
            retry++;
        }
        retry = 0;

        // 读取40位数据
        for (uint8_t i = 0; i < 5; i++) {
            buffer[i] = DHT11_Read_Byte(GPIOx, GPIO_Pin);
        }

        // 校验数据
        uint8_t sum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
        if (sum == buffer[4]) {
            data->humidity = buffer[0];
            data->temperature = buffer[2];
            return 1;
        }
    }

    return 0;
}



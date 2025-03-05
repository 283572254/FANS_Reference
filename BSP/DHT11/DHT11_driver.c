#include "../BSP/DHT11/DHT11_driver.h"
#include "./delay/delay.h"
// ����GPIOΪ���ģʽ
void DHT11_GPIO_Set_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// ����GPIOΪ����ģʽ
void DHT11_GPIO_Set_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) 
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// ��DHT11��ȡһλ����
static uint8_t DHT11_Read_Bit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    uint8_t retry = 0;
    uint8_t bit = 0;

    // �ȴ�DHT11����ߵ�ƽ
    while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0 && retry < 100) {
        delay_us(1);
        retry++;
    }
    retry = 0;

    // ��ʱ40us���ȡ��ƽ
    delay_us(40);
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1) {
        bit = 1;
    }

    // �ȴ�DHT11����͵�ƽ
    while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1 && retry < 100) {
        delay_us(1);
        retry++;
    }
    retry = 0;

    return bit;
}

// ��DHT11��ȡһ�ֽ�����
static uint8_t DHT11_Read_Byte(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    uint8_t byte = 0;
    for (uint8_t i = 0; i < 8; i++) {
        byte <<= 1;
        byte |= DHT11_Read_Bit(GPIOx, GPIO_Pin);
    }
    return byte;
}

// ��ȡDHT11����
uint8_t DHT11_Read(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,DHT11_Data_t *data) {
    uint8_t retry = 0;
    uint8_t buffer[5] = {0};

    // ����GPIOΪ���ģʽ
    DHT11_GPIO_Set_Output(GPIOx, GPIO_Pin);

    // ���Ϳ�ʼ�ź�
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
    HAL_Delay(18);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
    delay_us(20);

    // ����GPIOΪ����ģʽ
    DHT11_GPIO_Set_Input(GPIOx, GPIO_Pin);

    // �ȴ�DHT11��Ӧ
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

        // ��ȡ40λ����
        for (uint8_t i = 0; i < 5; i++) {
            buffer[i] = DHT11_Read_Byte(GPIOx, GPIO_Pin);
        }

        // У������
        uint8_t sum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
        if (sum == buffer[4]) {
            data->humidity = buffer[0];
            data->temperature = buffer[2];
            return 1;
        }
    }

    return 0;
}



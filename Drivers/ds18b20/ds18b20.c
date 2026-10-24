#include "ds18b20.h"

static TIM_HandleTypeDef *ds18b20_tim;

static void delay_us(uint16_t us) {
    __HAL_TIM_SET_COUNTER(ds18b20_tim, 0);
    while (__HAL_TIM_GET_COUNTER(ds18b20_tim) < us);
}

static void Set_Pin_Output(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static uint8_t DS18B20_Start(void) {
    uint8_t Response = 0;
    Set_Pin_Output();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    delay_us(480);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    delay_us(80);

    if (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1))) Response = 1;
    else Response = 0;

    delay_us(400);
    return Response;
}

static void DS18B20_Write(uint8_t data) {
    Set_Pin_Output();
    for (int i=0; i<8; i++) {
        if ((data & (1<<i)) != 0) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
            delay_us(1);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
            delay_us(60);
        } else {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
            delay_us(60);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
            delay_us(1);
        }
    }
}

static uint8_t DS18B20_Read(void) {
    uint8_t value = 0;
    for (int i=0; i<8; i++) {
        Set_Pin_Output();
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
        delay_us(2);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
        delay_us(10);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)) {
            value |= (1<<i);
        }
        delay_us(50);
    }
    return value;
}

void DS18B20_Init(TIM_HandleTypeDef *htim) {
    ds18b20_tim = htim;
}

float DS18B20_ReadTemperature(void) {
    uint8_t Temp_LSB, Temp_MSB;
    uint16_t raw_temp;
    
    if (DS18B20_Start()) {
        DS18B20_Write(0xCC);
        DS18B20_Write(0x44);
        HAL_Delay(750);

        DS18B20_Start();
        DS18B20_Write(0xCC);
        DS18B20_Write(0xBE);

        Temp_LSB = DS18B20_Read();
        Temp_MSB = DS18B20_Read();
        
        raw_temp = ((uint16_t)Temp_MSB << 8) | Temp_LSB;
        return (float)raw_temp * 0.0625;
    }
    return -999.0f; // Ошибка чтения
}

#ifndef DRIVERS_DS18B20_DS18B20_H_
#define DRIVERS_DS18B20_DS18B20_H_

#include "stm32f4xx_hal.h"

// Передаем указатель на таймер, который вы настроили в .ioc (например, &htim1)
void DS18B20_Init(TIM_HandleTypeDef *htim);

// Функция опроса датчика. Возвращает температуру в градусах Цельсия
float DS18B20_ReadTemperature(void);

#endif /* DRIVERS_DS18B20_DS18B20_H_ */

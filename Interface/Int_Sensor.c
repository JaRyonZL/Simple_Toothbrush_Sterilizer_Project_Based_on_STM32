/*
 * @Descripttion: 霍尔传感器检测盖子状态接口
 * @Author: JaRyon
 * @version: 
 * @Date: 2026-02-06 11:36:29
 */
#include "Int_Sensor.h"

/**
 * @brief 获取当前盖子状态 
 * 
 * @return uint8_t 1-开盖 0-合盖
 */
uint8_t Int_Sensor_Get(void)
{
    GPIO_PinState state = HAL_GPIO_ReadPin(Sensor_GPIO_Port, Sensor_Pin);
    return state ? 1 : 0;
}

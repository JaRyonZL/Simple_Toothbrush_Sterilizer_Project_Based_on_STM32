/*
 * @Descripttion: 开关按键接口
 * @Author: JaRyon
 * @version: 
 * @Date: 2026-02-05 20:39:25
 */
#include "Int_Key.h"

/**
 * @brief 获取按键状态
 * 
 * @return uint8_t 按键状态值 0-按下 1-未按下
 */
uint8_t Int_Key_Get(void)
{
    GPIO_PinState state = HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
    return (uint8_t)state;
}

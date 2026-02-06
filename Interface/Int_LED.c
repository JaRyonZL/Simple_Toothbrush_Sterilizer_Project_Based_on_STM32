/*
 * @Descripttion: LED照明灯接口
 * @Author: JaRyon
 * @version: 
 * @Date: 2026-02-05 19:50:57
 */
#include "Int_LED.h"

/**
 * @brief 开启全部照明灯
 * 
 */
void Int_LED_AllOpen(void)
{
    // 拉低引脚，点亮LED
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
}

/**
 * @brief 关闭所有的照明灯
 * 
 */
void Int_LED_AllClose(void)
{
    // 拉高引脚，关闭LED
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
}

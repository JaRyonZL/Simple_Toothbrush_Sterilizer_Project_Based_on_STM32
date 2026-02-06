/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2026-02-05 20:04:57
 */
#include "Int_Heat.h"

/**
 * @brief 开始加热
 * 
 */
void Int_Heat_Start(void)
{
    // 引脚拉高，开始加热
    HAL_GPIO_WritePin(HEAT_GPIO_Port, HEAT_Pin, GPIO_PIN_SET);
}

/**
 * @brief 停止加热
 * 
 */
void Int_Heat_Stop(void)
{
    // 引脚拉低，停止加热
    HAL_GPIO_WritePin(HEAT_GPIO_Port, HEAT_Pin, GPIO_PIN_RESET);
}

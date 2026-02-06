/*
 * @Descripttion: 吹风风扇控制接口
 * @Author: JaRyon
 * @version: 
 * @Date: 2026-02-05 20:04:36
 */
#include "Int_Fan.h"

/**
 * @brief 启动风扇
 * 
 */
void Int_Fan_Start(void)
{
    // 拉高引脚，启动风扇
    HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, GPIO_PIN_SET);
}

/**
 * @brief 关闭风扇
 * 
 */
void Int_Fan_Close(void)
{
    // 拉低引脚，关闭风扇
    HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, GPIO_PIN_RESET);
}


/*
 * @Descripttion: 
 * @Author: JaRyon
 * @version: 
 * @Date: 2026-02-06 12:23:21
 */
#include "Int_Ray.h"


/**
 * @brief 初始化紫外线控制的PWM方波参数
 * 
 */
void Int_Ray_Init(void)
{
    __HAL_TIM_SetCounter(&htim2, 0);                    // 清零计数器
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 100);   // 初始化比较值 25%
}

/**
 * @brief 开启紫外线消毒
 * 
 */
void Int_Ray_Start(void)
{
    // 开启定时器1
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}

/**
 * @brief 停止紫外线消毒
 * 
 */
void Int_Ray_Stop(void)
{
    // 关闭定时器1
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
}

/**
 * @brief 设置紫外线消毒功率（设置占空比）
 * 
 * @param duty 范围 0~200
 */
void Int_Ray_SetDuty(uint16_t duty) 
{
    // 限制设置范围
    if(duty > 200)
    {
        duty = 200;
    }

    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, duty);
}


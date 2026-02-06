/*
 * @Descripttion:
 * @Author: JaRyon
 * @version:
 * @Date: 2026-02-06 14:21:04
 */
#include "Int_NixieTube.h"

// 记录显示数字与引脚的映射值 即 下标-显示数字 下标元素-该设置的段选引脚电平
const uint8_t NixieTube_ShowNum[11] = {
    0x7E, // 0
    0x0C, // 1
    0xB6, // 2
    0x9E, // 3
    0XCC, // 4
    0XDA, // 5
    0XFA, // 6
    0X0E, // 7
    0XFE, // 8
    0XDE, // 9
    0xFF, // 无显示
};

/**
 * @brief 数码管显示数字
 *
 * @param num
 */
void Int_NixieTube_Show(uint8_t num)
{
    // 数字是否合法
    if (num > 99)
    {
        return;
    }

    // 仅一位数的显示 -- 显示在右边
    if (num < 10)
    {
        // 关闭全部数码管位选 -- 避免出现杂色
        HAL_GPIO_WritePin(DIG_1_GPIO_Port, DIG_1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(DIG_2_GPIO_Port, DIG_2_Pin, GPIO_PIN_SET);
        // 设置显示数字对应灯管的段选引脚 -- 显示数字
        GPIOA->ODR &= ~NixieTube_ShowNum[10]; // 每次设置数字前清除显示
        GPIOA->ODR |= NixieTube_ShowNum[num];
        // 开启右边数码管 -- 显示一位数字
        HAL_GPIO_WritePin(DIG_2_GPIO_Port, DIG_2_Pin, GPIO_PIN_RESET);

        HAL_Delay(5); // 延时暂留，确保显示亮度
    }
    else // 两位数的显示 -- 交替显示两数码管
    {
        // 分解十位和个位
        uint8_t unit = num % 10;
        uint8_t decade = num / 10;
        // 关闭两个数码管显示
        HAL_GPIO_WritePin(DIG_1_GPIO_Port, DIG_1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(DIG_2_GPIO_Port, DIG_2_Pin, GPIO_PIN_SET);
        // 设置第一个数码管数字
        GPIOA->ODR &= ~NixieTube_ShowNum[10]; // 每次设置数字前清除显示
        GPIOA->ODR |= NixieTube_ShowNum[unit];
        // 开启第一个数码管
        HAL_GPIO_WritePin(DIG_2_GPIO_Port, DIG_2_Pin, GPIO_PIN_RESET);
        HAL_Delay(5);

        // 关闭第一个数码管
        HAL_GPIO_WritePin(DIG_2_GPIO_Port, DIG_2_Pin, GPIO_PIN_SET);

        // 设置第二个数码管数字
        GPIOA->ODR &= ~NixieTube_ShowNum[10]; // 每次设置数字前清除显示
        GPIOA->ODR |= NixieTube_ShowNum[decade];
        // 开启第二个数码管
        HAL_GPIO_WritePin(DIG_1_GPIO_Port, DIG_1_Pin, GPIO_PIN_RESET);
        HAL_Delay(5);
    }
}

/**
 * @brief 关闭数码管显示
 *
 */
void Int_NixieTube_Close(void)
{
    // 位选引脚拉高，段选全部置低
    HAL_GPIO_WritePin(DIG_1_GPIO_Port, DIG_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG_2_GPIO_Port, DIG_2_Pin, GPIO_PIN_SET);
    GPIOA->ODR &= ~NixieTube_ShowNum[10];
}

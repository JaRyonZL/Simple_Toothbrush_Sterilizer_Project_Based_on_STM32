/*
 * @Descripttion: 公共层串口调试，日志输出
 * @Author: JaRyon
 * @version: 
 * @Date: 2026-02-05 19:05:23
 */
#include "Com_Debug.h"


/**
 * @brief 重写fputc函数，重定向printf，使打印串口发送的数据
 * 
 * @param ch 
 * @param file 
 * @return int 
 */
int fputc(int ch, FILE * file)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100);
    return ch;
}


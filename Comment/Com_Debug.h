/*
 * @Descripttion:
 * @Author: JaRyon
 * @version:
 * @Date: 2026-02-05 19:05:37
 */
#ifndef __Com_Debug_H
#define __Com_Debug_H

#include "usart.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"

// 添加日志开关
#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG

// 只显示文件名，不显示完整路径
#define FILE_NAME strrchr(__FILE__, '\\') == NULL ? __FILE__ : strrchr(__FILE__, '\\') + 1
#define __FILE_NAME strrchr(FILE_NAME, '/') == NULL ? FILE_NAME : strrchr(FILE_NAME, '/') + 1

// 自定义日志打印内容 -- 增加文件名:行号 前缀
#define Debug_Print(format, ...) printf("[%s:%d] " format "\r\n", __FILE_NAME, __LINE__, ##__VA_ARGS__)

#else
#define Debug_Print(format, ...)

#endif



#endif

#ifndef __app_toothbrush_H
#define __app_toothbrush_H

#include "Com_Debug.h"
#include "Int_LED.h"
#include "Int_Fan.h"
#include "Int_Heat.h"
#include "Int_Key.h"
#include "Int_Sensor.h"
#include "Int_Ray.h"
#include "Int_NixieTube.h"

// 定义牙刷消毒器状态
typedef enum
{
    STATE_IDLE,         // 空闲状态
    STATE_RUNNING,      // 运行状态
    STATE_PAUSE         // 暂停状态
}TOOTHBRUSH_STATE;

void App_ToothBrush_Init(void);
void App_ToothBrush_Start(void);
void App_ToothBrush_Task(void);
void App_ToothBrush_Stop(void);

#endif /* __app_toothbrush_H__ */
/*** (C) COPYRIGHT 2025 END OF FILE ***/
 

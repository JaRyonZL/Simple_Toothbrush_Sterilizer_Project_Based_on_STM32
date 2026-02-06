#include "app_toothbrush.h"

static TOOTHBRUSH_STATE tb_state = STATE_IDLE;

static uint32_t tb_remain_time = 0; // 剩余消毒时间
static uint32_t tb_tick_last = 0;   // 上一时刻

/**
 * @brief 初始化牙刷消毒器
 *
 */
void App_ToothBrush_Init(void)
{
    // 初始化紫外线灯
    Int_Ray_Init();

    // 关闭全部模块
    Int_LED_AllClose();
    Int_Fan_Close();
    Int_Heat_Stop();
    Int_Ray_Stop();
    Int_NixieTube_Close();

    // 初始化默认消毒器状态为空闲
    tb_state = STATE_IDLE;

    // 清零剩余时间与上一时刻时间
    tb_remain_time = 0;
    tb_tick_last = 0;
}

/**
 * @brief 牙刷消毒任务
 *
 */
void App_ToothBrush_Task(void)
{
    // 计算每次执行的过去的时间
    uint32_t now = HAL_GetTick(); // 获取当前时刻时间
    uint32_t tick_past = now - tb_tick_last;
    tb_tick_last = now; // 更新上一时刻时间

    // 限制间隔长，避免倒计时突变
    if (tick_past > 1000) // 超过1s限制
    {
        tick_past = 1000;
    }

    // 进入状态机逻辑
    switch (tb_state)
    {
    case STATE_IDLE:
        if (Int_Key_Get() == 0)
        {
            // 按键按下，开始运行 牙刷消毒逻辑
            App_ToothBrush_Start();
        }
        break;
    case STATE_RUNNING:
        if (Int_Sensor_Get() == 1)
        {
            // 盖子被打开，消毒暂停
            tb_state = STATE_PAUSE;
            // 停止消毒，关闭相关执行器
            Int_Fan_Close();
            Int_Heat_Stop();
            Int_Ray_Stop();

            break;
        }

        // 运行消毒功能
        Int_Fan_Start();
        Int_Heat_Start();
        Int_Ray_Start();

        // 显示倒计时时间
        if (tb_remain_time > tick_past) // 倒计时时间大于零继续递减
        {
            tb_remain_time -= tick_past;
            Int_NixieTube_Show(tb_remain_time / 1000);
        }
        else
        {
            // 倒计时结束，停止消毒，返回空闲态
            App_ToothBrush_Stop();
        }
        break;
    case STATE_PAUSE:
        if (Int_Sensor_Get() == 0)
        {
            // 盖子盖上，继续消毒，进入运行态
            tb_state = STATE_RUNNING;
            // 重置上一时刻 (可选)
            tb_tick_last = HAL_GetTick();
        }

        // 仅保持显示倒计时
        Int_NixieTube_Show(tb_remain_time / 1000);
        break;

    default:
        App_ToothBrush_Init();
        break;
    }
}

/**
 * @brief 启动牙刷消毒器
 *
 */
void App_ToothBrush_Start(void)
{
    // 消毒器状态置为运行态
    tb_state = STATE_RUNNING;

    // 初始化剩余倒计时时间
    tb_remain_time = 90000;
    // 初始化上一时刻时间
    tb_tick_last = HAL_GetTick();

    // 启动照明灯和倒计时时间显示
    Int_LED_AllOpen();
    Int_NixieTube_Show(tb_remain_time / 1000);
}

/**
 * @brief 结束消毒
 *
 */
void App_ToothBrush_Stop(void)
{
    App_ToothBrush_Init();
}

// static uint8_t start_flag = 0; // 1-启动消毒 0-结束消毒

// static uint32_t cnt_curr = 0;  // 当前倒计时
// static uint32_t tick_curr = 0; // 当前时刻
// static uint32_t tick_last = 0; // 上一时刻

// /**
//  * @brief 初始化牙刷消毒器
//  *
//  */
// void App_ToothBrush_Init(void)
// {
//     Int_Ray_Init(); // 紫外线消毒初始化
//     // 默认关闭全部功能
//     Int_LED_AllClose();    // LED照明灯
//     Int_Fan_Close();       // 风扇
//     Int_Heat_Stop();       // 加热片
//     Int_Ray_Stop();        // 紫外线
//     Int_NixieTube_Close(); // 数码管
// }

// /**
//  * @brief 启动牙刷消毒
//  *
//  */
// void App_ToothBrush_Start(void)
// {
//     // 核心功能：按键按下，消毒，显示倒计时

//     // 按下按键，消毒功能启动 倒计时准备
//     if (start_flag == 0 && Int_Key_Get() == 0)
//     {
//         // 消毒标志置位
//         start_flag = 1;

//         // 倒计时启动，照明灯打开
//         Int_LED_AllOpen();
//         // 倒计时要显示出来了
//         cnt_curr = 90000;
//         Int_NixieTube_Show(cnt_curr / 1000);

//         // 获取当前时刻
//         tick_curr = HAL_GetTick();
//     }
//     // 消毒功能启动后，计算经过时间
//     if (start_flag == 1)
//     {
//         // 获取上一时刻时间
//         tick_last = tick_curr;
//         // 获取当前时刻
//         tick_curr = HAL_GetTick();
//         // 计算经过时间
//         uint32_t tick_past = tick_curr - tick_last;

//         // 盖子盖上时，开始倒计时，正在消毒
//         if (Int_Sensor_Get() == 0)
//         {
//             // 消毒...
//             // 烘干
//             Int_Fan_Start();
//             Int_Heat_Start();
//             // 消毒
//             Int_Ray_Start();

//             // 判断倒计时是否结束，进而判断是否继续消毒
//             if (cnt_curr >= tick_past)
//             {
//                 // 计算当前倒计时的时间
//                 cnt_curr = cnt_curr - tick_past;
//                 // 显示倒计时
//                 Int_NixieTube_Show(cnt_curr / 1000);
//             }
//             else
//             {
//                 // 倒计时结束，停止消毒，倒计时关闭
//                 start_flag = 0;
//                 App_ToothBrush_Init();
//             }
//         }
//         else
//         {
//             // 暂停消毒 - 倒计时暂停，消毒关闭
//             Int_Fan_Close();
//             Int_Heat_Stop();
//             // 消毒
//             Int_Ray_Stop();
//             // 显示暂停时的倒计时
//             Int_NixieTube_Show(cnt_curr / 1000);
//         }
//     }
// }

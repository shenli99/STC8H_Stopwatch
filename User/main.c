#include "STC8H.h"
// 移除不必要的头文件和声明
#include "Timer.h"
#include "Task.h"
#include "TM1650.h"
#include "Key.h"
#include "LED.h"
#include "Soft_I2C.h"

// 函数前向声明，解决函数未定义的错误
extern void Key_Process_Task(void);
extern void Time_Update_Task(void);

// 全局变量
unsigned char g_minute = 0;     // 分钟
unsigned char g_second = 0;     // 秒
unsigned int g_millisecond = 0; // 毫秒
bit g_running = 0;              // 运行状态
bit g_dot_flag = 1;             // 小数点闪烁标志
unsigned char g_dot_counter = 0; // 小数点闪烁计数器

/**
 * @brief 系统初始化
 */
void System_Init(void)
{
    unsigned int i;  // 变量声明必须在函数开头
    P_SW2 |= 0x80;	//允许访问扩展的特殊寄存器，XFR

    // 系统初始化，使用延时确保稳定
    for(i = 0; i < 10000; i++) _nop_();
    
    // 初始化各个模块 - 调整顺序以确保依赖关系
    Task_Init();        // 任务调度初始化
    Timer0_Init();      // 定时器初始化
    
    // 增加延时确保定时器稳定
    for(i = 0; i < 5000; i++) _nop_();
    
    TM1650_Init(TM1650_BRIGHTNESS_8);  // 数码管初始化
    Key_Init();         // 按键初始化
    LED_Init();         // LED初始化
    
    Task_Register(TASK_10MS, Key_Scan);

    // 初始显示00:00
    TM1650_Display_Zero();
    LED_Update(LED_STATE_RESET);  // 初始为清零状态
    
    TM1650_Clear();
    // 延时一段时间让硬件稳定
    for(i = 0; i < 50000; i++) _nop_();
    Stopwatch_Init();
}

/**
 * @brief 硬件测试函数
 */
// void Hardware_Test(void)
// {
//     unsigned int i;
    
//     // 测试LED灯 - 依次点亮
//     LED_Blue_Off();
//     LED_Green_On();
//     for(i = 0; i < 0xFFFE; i++) _nop_();
    
//     LED_Green_Off();
//     LED_Red_On();
//     for(i = 0; i < 0xFFFE; i++) _nop_();
    
//     LED_Red_Off();
//     LED_Blue_On();
//     for(i = 0; i < 0xFFFE; i++) _nop_();
    
//     LED_Blue_Off();
    
//     // 测试数码管
//     TM1650_Test();  // 显示8888
//     for(i = 0; i < 0xFFFE; i++) _nop_();
    
//     TM1650_SimpleTest();  // 显示1234
//     for(i = 0; i < 0xFFFE; i++) _nop_();
    
//     // 恢复初始状态
//     TM1650_Display_Zero();
//     LED_Update(LED_STATE_RESET);
// }

void main(void)
{
    System_Init();
    
    // 进行硬件测试
    // Hardware_Test();
    
    // LED_Blue_Off();

    // 注册任务函数到任务系统
    // Task_Register(TASK_1MS, Time_Update_Task);
    // Task_Register(TASK_10MS, Key_Process_Task);

    while(1)
    {
        Task_Dispatch();
    }
}
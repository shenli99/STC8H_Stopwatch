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
    
    // 初始显示00:00
    TM1650_Display_Zero();
    LED_Update(LED_STATE_RESET);  // 初始为清零状态
    
    // 延时一段时间让硬件稳定
    for(i = 0; i < 50000; i++) _nop_();
}

/**
 * @brief 硬件测试函数
 */
void Hardware_Test(void)
{
    unsigned int i;
    
    // 测试LED灯 - 依次点亮
    LED_Blue_Off();
    LED_Green_On();
    for(i = 0; i < 0xFFFE; i++) _nop_();
    
    LED_Green_Off();
    LED_Red_On();
    for(i = 0; i < 0xFFFE; i++) _nop_();
    
    LED_Red_Off();
    LED_Blue_On();
    for(i = 0; i < 0xFFFE; i++) _nop_();
    
    LED_Blue_Off();
    
    // 测试数码管
    TM1650_Test();  // 显示8888
    for(i = 0; i < 0xFFFE; i++) _nop_();
    
    TM1650_SimpleTest();  // 显示1234
    for(i = 0; i < 0xFFFE; i++) _nop_();
    
    // 恢复初始状态
    TM1650_Display_Zero();
    LED_Update(LED_STATE_RESET);
}

void main(void)
{
    System_Init();
    
    // 进行硬件测试
    // Hardware_Test();
    
    LED_Blue_Off();

    // 注册任务函数到任务系统
    // Task_Register(TASK_1MS, Time_Update_Task);
    // Task_Register(TASK_10MS, Key_Process_Task);
    
    while(1)
    {
        // Task_Dispatch();
    }
}

/**
 * @brief 时间更新任务
 */
// 简化Time_Update_Task函数
void Time_Update_Task(void)
{
    if(g_running)
    {
        g_millisecond++;
        
        // 每秒更新
        if(g_millisecond >= 1000)
        {
            g_millisecond = 0;
            g_second++;
            
            // 小数点闪烁
            g_dot_flag = !g_dot_flag;
            
            // 每分钟更新
            if(g_second >= 60)
            {
                g_second = 0;
                g_minute++;
                
                // 达到99:59自动停止并清零
                if(g_minute >= 100)
                {
                    g_minute = 0;
                    g_second = 0;
                    g_running = 0;
                    LED_Update(LED_STATE_RESET);
                }
            }
        }
        
        // 每100ms更新一次显示
        if(g_millisecond % 100 == 0)
        {
            TM1650_Display_Time(g_minute, g_second, g_dot_flag);
        }
    }
    else
    {
        // 暂停状态下每500ms更新一次小数点闪烁
        static unsigned char pause_counter = 0;
        pause_counter++;
        if(pause_counter >= 5)
        {
            pause_counter = 0;
            g_dot_flag = !g_dot_flag;
            TM1650_Display_Time(g_minute, g_second, g_dot_flag);
        }
    }
}
#include "UserStopwatch.h"

// 秒表变量
u32 stopwatch_count = 0;  // 毫秒计数
u8 stopwatch_state = STOPWATCH_STATE_RESET;  // 秒表状态
u8 dot_flag = 0;  // 小数点闪烁标志

// 秒表1ms任务函数
void Stopwatch_Update_1ms(void)
{
    if(stopwatch_state == STOPWATCH_STATE_RUN)
    {
        stopwatch_count++;
        if (stopwatch_count >= 60000)  // 最多计数到60秒
        {
            stopwatch_count = 0;
            Stopwatch_Reset();
        }

        if (stopwatch_count % 500 == 0)
        {
            dot_flag = !dot_flag;
        }
    }
}

// 秒表100ms任务函数
void Stopwatch_Update_100ms(void)
{
    Stopwatch_UpdateDisplay();
}

// 秒表50ms任务函数
void Stopwatch_Update_50ms(void)
{
    u8 key;
    key = Key_GetPressed();
    Stopwatch_Toggle(key);
}

// 秒表初始化
void Stopwatch_Init(void)
{
    u16 i;

    for(i = 0; i < 10000; i++) _nop_();
    
    Task_Init();  // 初始化任务系统
    Timer0_Init();  // 初始化定时器0

    for(i = 0; i < 5000; i++) _nop_();

    TM1650_Init(TM1650_BRIGHTNESS_8);  // 初始化数码管
    TM1650_Clear();  // 清除数码管显示

    Key_Init();  // 初始化按键
    Task_Register(TASK_10MS, Key_Scan);  // 注册按键扫描任务

    LED_Init();  // 初始化LED
    LED_Update(LED_STATE_RESET);  // 熄灭LED

    for(i = 0; i < 50000; i++) _nop_();

    stopwatch_count = 0;
    stopwatch_state = STOPWATCH_STATE_RESET;
    dot_flag = 0;
    
    // 注册任务函数
    Task_Register(TASK_1MS, Stopwatch_Update_1ms);
    Task_Register(TASK_100MS, Stopwatch_Update_100ms);
    Task_Register(TASK_50MS, Stopwatch_Update_50ms);
    
    LED_Update(LED_STATE_RESET);
    Stopwatch_UpdateDisplay();
}

// 秒表开始运行
void Stopwatch_Run(void)
{
    if(stopwatch_state != STOPWATCH_STATE_RUN)
    {
        stopwatch_state = STOPWATCH_STATE_RUN;
        LED_Update(LED_STATE_RUN);
    }
}

// 秒表停止运行
void Stopwatch_Stop(void)
{
    if(stopwatch_state == STOPWATCH_STATE_RUN)
    {
        stopwatch_state = STOPWATCH_STATE_STOP;
        LED_Update(LED_STATE_STOP);
    }
}

// 秒表复位
void Stopwatch_Reset(void)
{
    stopwatch_count = 0;
    stopwatch_state = STOPWATCH_STATE_RESET;
    dot_flag = 0;
    
    TM1650_Display_Time(0, 0, 0);
    LED_Update(LED_STATE_RESET);
}

// 秒表启动/停止切换
void Stopwatch_Toggle(u8 key)
{
    if(stopwatch_state == STOPWATCH_STATE_RUN)
    {
        if (key == 1) 
        {
            Stopwatch_Stop();
        }
        if (key == 2) 
        {

        }
    }
    else if(stopwatch_state == STOPWATCH_STATE_STOP)
    {
        if (key == 1) 
        {

        }
        if (key == 2) 
        {
            Stopwatch_Reset();
        }
    }else if (stopwatch_state == STOPWATCH_STATE_RESET)
    {
        if (key == 1) 
        {
            Stopwatch_Run();
        }
        if (key == 2) 
        {
            
        }
    }
}

// 更新秒表显示
void Stopwatch_UpdateDisplay(void)
{
    u8 minute, second;
    
    // 计算分和秒
    second = stopwatch_count / 1000;
    minute = second / 60;
    second = second % 60;
    
    // 显示时间
    TM1650_Display_Time(minute, second, dot_flag);
}
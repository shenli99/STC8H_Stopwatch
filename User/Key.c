#include "STC8H.h"
#include "Key.h"
#include "UserStopwatch.h"
#include "Task.h"

// 按键变量
unsigned char key1_buffer = 0;
unsigned char key2_buffer = 0;

unsigned char key1_pressed = 0;
unsigned char key2_pressed = 0;

/**
 * @brief 按键初始化
 */
void Key_Init(void)
{
    // 上拉电阻配置（按下接地）
    // P3.2和P3.3设置为输入模式，启用上拉电阻
    P3M1 &= ~0x0C;  // 清零P3.2和P3.3的模式位
    P3M0 &= ~0x0C;  // 设置为准双向口模式（默认上拉）
    
    // 使用内部上拉
    P3PU |= 0x0C;  // 设置P3.2和P3.3为上拉模式
    
    // 注册按键扫描任务
    // Task_Register(TASK_10MS, Key_Scan);
}

/**
 * @brief 按键扫描任务函数
 */
void Key_Scan(void)
{
    // 读取按键状态并处理消抖
    // 由于上拉，按键输入默认为1，按下时为0
    key1_buffer = (key1_buffer << 1) | KEY1;
    key2_buffer = (key2_buffer << 1) | KEY2;
    
    // 检测按键1是否按下（低电平有效）
    if((key1_buffer & 0x07) == 0x00)
    {
        // 按键1按下，切换秒表状态
        key1_buffer = 0xFF;  // 清除缓冲区，避免重复触发
        key1_pressed = 1;  // 按键1按下标志位置1
    }
    
    // 检测按键2是否按下
    if((key2_buffer & 0x07) == 0x00)
    {
        // 按键2按下，重置秒表
        key2_buffer = 0xFF;  // 清除缓冲区，避免重复触发
        key2_pressed = 1;  // 按键2按下标志位置1
    }
}

unsigned char Key_GetPressed()
{
    if (key1_pressed)
    {
        key1_pressed = 0;
        return 1;
    }
    else if (key2_pressed)
    {
        key2_pressed = 0;
        return 2;
    }
    else
    {
        return 0;
    }
}
#include "STC8H.h"
#include "intrins.h"
#include "LED.h"

/**
 * @brief LED初始化 - 共阳极，低电平点亮
 */
// 简化LED_Init函数，减少延时
void LED_Init(void)
{
    // 配置为推挽
    P0M1 &= ~0x07;
    P0M0 |= 0x07;
    P0 = 0xFF;
    
    // 共阳极LED：初始高电平熄灭
    LED_GREEN = 1;
    LED_RED = 1;
    LED_BLUE = 1;
}

// 简化LED_Update函数，移除不必要的延时
void LED_Update(unsigned char state)
{
    // 先关闭所有LED
    LED_GREEN = 1;
    LED_RED = 1;
    LED_BLUE = 1;
    
    // 根据状态点亮对应LED
    switch(state)
    {
        case LED_STATE_RUN:
            LED_GREEN = 0;
            break;
        case LED_STATE_STOP:
            LED_RED = 0;
            break;
        case LED_STATE_RESET:
            LED_BLUE = 0;
            break;
        default:
            break;
    }
}

/**
 * @brief 绿色LED点亮
 */
void LED_Green_On(void)
{
    LED_GREEN = 0;  // 低电平点亮
}

void LED_Green_Toggle(void)
{
    LED_GREEN = ~LED_GREEN;  // 翻转当前状态
}

/**
 * @brief 绿色LED熄灭
 */
void LED_Green_Off(void)
{
    LED_GREEN = 1;  // 高电平熄灭
}

/**
 * @brief 红色LED点亮
 */
void LED_Red_On(void)
{
    LED_RED = 0;  // 低电平点亮
}

void LED_Red_Toggle(void)
{
    LED_RED = ~LED_RED;  // 翻转当前状态
}

/**
 * @brief 红色LED熄灭
 */
void LED_Red_Off(void)
{
    LED_RED = 1;  // 高电平熄灭
}

/**
 * @brief 蓝色LED点亮
 */
void LED_Blue_On(void)
{
    LED_BLUE = 0;  // 低电平点亮
}

void LED_Blue_Toggle(void)
{
    LED_BLUE = ~LED_BLUE;  // 翻转当前状态
}

/**
 * @brief 蓝色LED熄灭
 */
void LED_Blue_Off(void)
{
    LED_BLUE = 1;  // 高电平熄灭
}
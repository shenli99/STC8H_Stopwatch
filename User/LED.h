#ifndef __LED_H__
#define __LED_H__

// LED引脚定义 - 绿色(运行)接P01，红色(暂停)接P00，蓝色(清零)接P02
sbit LED_RED = P0^0;  // 红色LED
sbit LED_GREEN   = P0^1;  // 绿色LED
sbit LED_BLUE  = P0^2;  // 蓝色LED

// LED状态定义
#define LED_STATE_RUN    0
#define LED_STATE_STOP   1
#define LED_STATE_RESET  2

// 函数声明
extern void LED_Init(void);
extern void LED_Green_On(void);
void LED_Green_Toggle(void);
extern void LED_Green_Off(void);
extern void LED_Red_On(void);
void LED_Red_Toggle(void);
extern void LED_Red_Off(void);
extern void LED_Blue_On(void);
void LED_Red_Toggle(void);
extern void LED_Blue_Off(void);
extern void LED_Update(unsigned char state);
extern void LED_Test(void);

#endif /* __LED_H__ */
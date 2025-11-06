#ifndef __KEY_H__
#define __KEY_H__

#include "common.h"
#include "UserStopwatch.h"
#include "Task.h"

// 按键引脚定义 - KEY1(启动/停止)接P32，KEY2(复位)接P33
sbit KEY1 = P3^2;  // KEY1(启动/停止)接P32
sbit KEY2 = P3^3;  // KEY2(复位)接P33

#define KEY_NONE 0
#define KEY_PRESSED 1
#define KEY_CAPTURE 2

// 函数声明
extern void Key_Init(void);
extern void Key_Scan(void);
extern unsigned char Key_GetPressed();

#endif /* __KEY_H__ */
#ifndef __USER_STOPWATCH_H__
#define __USER_STOPWATCH_H__

#include "STC8H.h"
#include "Type_def.h"
#include "TM1650.h"
#include "LED.h"
#include "Key.h"
#include "Task.h"

// 秒表状态
#define STOPWATCH_STATE_STOP    0  // 停止状态
#define STOPWATCH_STATE_RUN     1  // 运行状态
#define STOPWATCH_STATE_RESET   2  // 复位状态

// 函数声明
extern void Stopwatch_Init(void);
extern void Stopwatch_Run(void);
extern void Stopwatch_Stop(void);
extern void Stopwatch_Toggle(unsigned char key);
extern void Stopwatch_Reset(void);
extern void Stopwatch_UpdateDisplay(void);

#endif /* __USER_STOPWATCH_H__ */
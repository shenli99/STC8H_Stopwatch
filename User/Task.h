#ifndef __TASK_H__
#define __TASK_H__

#include "common.h"

// 任务ID枚举
typedef enum
{
    TASK_1MS,
    TASK_10MS,
    TASK_50MS,
    TASK_100MS,
    TASK_MAX
} Task_ID;

// 任务函数类型定义
typedef void (*Task_Func)(void);

// 任务控制块结构体
typedef struct
{
    Task_ID id;
    u16 period;
    u16 counter;
    Task_Func task_func;
} Task_CB;

// 函数声明
void Task_Init(void);
void Task_Dispatch(void);
void Task_1ms_Count(void);
void Task_Register(u8 task_id, Task_Func func);

#endif /* __TASK_H__ */
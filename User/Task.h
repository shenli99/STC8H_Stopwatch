#ifndef __TASK_H__
#define __TASK_H__

// 任务ID枚举
typedef enum
{
    TASK_1MS,
    TASK_10MS,
    TASK_100MS,
    TASK_1S,
    TASK_MAX
} Task_ID;

// 任务函数类型定义
typedef void (*Task_Func)(void);

// 任务控制块结构体
typedef struct
{
    Task_ID id;
    unsigned int period;
    unsigned int counter;
    Task_Func task_func;
} Task_CB;

// 函数声明
extern void Task_Init(void);
extern void Task_Dispatch(void);
extern void Task_1ms_Count(void);
extern void Task_Register(unsigned char task_id, Task_Func func);

#endif /* __TASK_H__ */
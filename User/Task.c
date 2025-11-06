#include "Task.h"

// 任务控制块数组
Task_CB task_table[TASK_MAX] = {
    {TASK_1MS, 1, 1, NULL},
    {TASK_10MS, 10, 10, NULL},
    {TASK_50MS, 50, 50, NULL},
    {TASK_100MS, 100, 100, NULL}
};

/**
 * @brief 任务初始化 - 确保所有任务正确初始化
 */
void Task_Init(void)
{
    unsigned char i;
    for(i = 0; i < TASK_MAX; i++)
    {
        task_table[i].counter = task_table[i].period;
        task_table[i].task_func = NULL;
    }
}

/**
 * @brief 任务计数更新（由定时器中断调用）
 */
void Task_1ms_Count(void)
{
    unsigned char i;
    for(i = 0; i < TASK_MAX; i++)
    {
        if(task_table[i].counter > 0)
        {
            task_table[i].counter--;
        }
    }
}

/**
 * @brief 任务调度 - 确保任务调用正确
 */
void Task_Dispatch(void)
{
    unsigned char i;
    for(i = 0; i < TASK_MAX; i++)
    {
        if(task_table[i].counter == 0)
        {
            task_table[i].counter = task_table[i].period;
            if(task_table[i].task_func != NULL)
            {
                task_table[i].task_func();
            }
        }
    }
}

/**
 * @brief 注册任务函数 - 确保正确覆盖
 */
void Task_Register(unsigned char task_id, Task_Func func)
{
    unsigned int i;  // 移到函数开头
    
    if(task_id < TASK_MAX)
    {
        // 先置空，再赋值，确保状态干净
        task_table[task_id].task_func = NULL;
        for(i = 0; i < 100; i++) _nop_(); // 短暂延时
        task_table[task_id].task_func = func;
        // 重置计数器
        task_table[task_id].counter = task_table[task_id].period;
    }
}

// 简化任务控制块，只保留必要功能
typedef struct {
    unsigned char Run;
    unsigned char Timer;
    unsigned char ItvTime;
} TASKCB;
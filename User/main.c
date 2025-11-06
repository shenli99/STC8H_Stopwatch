#include "Task.h"
#include "UserStopwatch.h"

void main(void)
{
    P_SW2 |= 0x80;	//允许访问扩展的特殊寄存器，XFR

    Stopwatch_Init();
    while(1)
    {
        Task_Dispatch();
    }
}
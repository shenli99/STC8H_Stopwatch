#ifndef __KEY_H__
#define __KEY_H__

// 按键引脚定义 - KEY1(启动/停止)接P32，KEY2(复位)接P33
sbit KEY1 = P3^2;  // KEY1(启动/停止)接P32
sbit KEY2 = P3^3;  // KEY2(复位)接P33

// 函数声明
extern void Key_Init(void);
extern void Key_Scan(void);

#endif /* __KEY_H__ */
extern unsigned char Key1_Read(void);
extern unsigned char Key2_Read(void);
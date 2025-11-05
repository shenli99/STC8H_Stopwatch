#include "STC8H.h"
#include "intrins.h"
#include "Softiic.h"
#include "TM1650.h"

// 共阴数码管段码表（0-9）
unsigned char code SEG_TAB[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

/**
 * @brief TM1650初始化
 */
void TM1650_Init(unsigned char brightness)
{
    unsigned int i;
    unsigned char ctrl_cmd;
    
    IIC_Init();
    
    // 延时等待TM1650上电稳定
    for(i = 0; i < 20000; i++)
    {
        _nop_();_nop_();_nop_();_nop_(); // 确保延时有效
    }
    
    // 清除显示
    TM1650_Clear();
    
    // 短暂延时
    for(i = 0; i < 100; i++) _nop_();
    
    // TM1650控制命令：正确的控制命令格式
    ctrl_cmd = 0x48 | (brightness & 0x07) | 0x08;  // 0x08是显示开启位
    
    // 直接使用IIC基本函数发送控制命令，确保时序正确
    IIC_Start();
    IIC_Send_Byte(TM1650_ADDR << 1);  // 发送器件地址+写命令
    IIC_Wait_Ack();
    IIC_Send_Byte(0x48);  // 发送控制寄存器地址
    IIC_Wait_Ack();
    IIC_Send_Byte(ctrl_cmd);  // 发送控制命令
    IIC_Wait_Ack();
    IIC_Stop();
    
    // 短暂延时
    for(i = 0; i < 100; i++) _nop_();
    
    // 显示初始化图案以确认正常工作
    TM1650_Display_Zero();
}

/**
 * @brief 显示时间 - 格式为 MM:SS
 */
// 优化前：带有多个延时的完整版本
void TM1650_Display_Time(unsigned char minute, unsigned char second, bit dot_flag)
{
    unsigned char seg_data[4];
    
    // 分解时间
    seg_data[0] = SEG_TAB[minute / 10];    // 分钟十位
    seg_data[1] = SEG_TAB[minute % 10] | (dot_flag ? 0x80 : 0);    // 分钟个位
    seg_data[2] = SEG_TAB[second / 10];    // 秒十位
    seg_data[3] = SEG_TAB[second % 10];    // 秒个位
    
    // 直接写入，移除多余延时
    TM1650_Write(0x68, seg_data[0]);
    TM1650_Write(0x6A, seg_data[1]);
    TM1650_Write(0x6C, seg_data[2]);
    TM1650_Write(0x6E, seg_data[3]);
}

/**
 * @brief 向TM1650写入一个字节
 */
// 移除不必要的延时和重试逻辑，简化通信函数
void TM1650_Write(unsigned char addr, unsigned char dat)
{
    IIC_Start();
    IIC_Send_Byte((TM1650_ADDR << 1) & 0xFE);
    IIC_Wait_Ack();
    IIC_Send_Byte(addr);
    IIC_Wait_Ack();
    IIC_Send_Byte(dat);
    IIC_Wait_Ack();
    IIC_Stop();
}

// 移除以下重复的函数定义（第107-114行）
/*
// 简化TM1650_Display_Time函数
// 删除重复的TM1650_Display_Time函数实现（第100-113行）
// 保留第一个完整的实现，或者根据需要进行优化

// 修改原来的TM1650_Display_Time函数（如果需要优化）
void TM1650_Display_Time(unsigned char minute, unsigned char second, bit dot_flag)
{
    unsigned char seg_data[4];
    
    // 使用正确的SEG_TAB数组而不是未定义的smg_code
    seg_data[0] = SEG_TAB[minute / 10];
    seg_data[1] = SEG_TAB[minute % 10] | (dot_flag ? 0x80 : 0);
    seg_data[2] = SEG_TAB[second / 10];
    seg_data[3] = SEG_TAB[second % 10];
    
    TM1650_Write(0x68, seg_data[0]);
    TM1650_Write(0x6A, seg_data[1]);
    TM1650_Write(0x6C, seg_data[2]);
    TM1650_Write(0x6E, seg_data[3]);
}
*/

/**
 * @brief 清除显示
 */
void TM1650_Clear(void)
{
    TM1650_Write(0x68, 0x00);
    TM1650_Write(0x6A, 0x00);
    TM1650_Write(0x6C, 0x00);
    TM1650_Write(0x6E, 0x00);
}

/**
 * @brief 显示00:00
 */
void TM1650_Display_Zero(void)
{
    TM1650_Write(0x68, 0x3F);  // 第一位显示0
    TM1650_Write(0x6A, 0x3F);  // 第二位显示0
    TM1650_Write(0x6C, 0x3F);  // 第三位显示0
    TM1650_Write(0x6E, 0x3F);  // 第四位显示0
}

/**
 * @brief 显示测试模式 - 显示8888
 */
void TM1650_Test(void)
{
    TM1650_Write(0x68, 0x7F);  // 第一位显示8
    TM1650_Write(0x6A, 0x7F);  // 第二位显示8
    TM1650_Write(0x6C, 0x7F);  // 第三位显示8
    TM1650_Write(0x6E, 0x7F);  // 第四位显示8
}

/**
 * @brief 简单数码管测试 - 显示1234
 */
void TM1650_SimpleTest(void)
{
    TM1650_Write(0x68, 0x06);  // 第一位显示1
    TM1650_Write(0x6A, 0x5B);  // 第二位显示2
    TM1650_Write(0x6C, 0x4F);  // 第三位显示3
    TM1650_Write(0x6E, 0x66);  // 第四位显示4
}
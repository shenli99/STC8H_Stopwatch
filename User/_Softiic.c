#include "STC8H.h"
#include "intrins.h"
#include "Softiic.h"

#define IIC_DELAY() _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();

/**
 * @brief IIC初始化 - 数码管SCL接P15，SDA接P14
 */
void IIC_Init(void)
{
    unsigned int i;  // 移到函数开头
    
    // 配置P1.4和P1.5为开漏输出模式
    P1M1 |= 0x30;   // 设置P1.4和P1.5为开漏模式
    P1M0 |= 0x30;  // 清零对应位
    
    // 不确定是否有外部上拉可以开启内部上拉
    // P1PU |= 0x30;   // 设置P1.4和P1.5为内部上拉
    // 关闭内部上拉
    P1PU &= ~0x30;  // 清零对应位
    // 内部上拉可能导致通信失败，但如果没有外部上拉只能选则内部上拉
    
    // 增加延时确保稳定
    for(i = 0; i < 5000; i++) _nop_();
}

/**
 * @brief IIC发送一个字节
 */
void IIC_Send_Byte(unsigned char dat)
{
    unsigned char i;  // 移到函数开头
    
    for(i = 0; i < 8; i++)
    {
        SDA = (dat & 0x80) ? 1 : 0;
        IIC_DELAY();
        SCL = 1;
        IIC_DELAY();
        IIC_DELAY();
        IIC_DELAY();
        SCL = 0;
        IIC_DELAY();
        dat <<= 1;
    }
    SDA = 1;
    IIC_DELAY();
}

/**
 * @brief IIC写入一个字节数据 - 增强稳定性版本
 */
void IIC_Write_One_Byte(unsigned char daddr, unsigned char addr, unsigned char dat)
{
    unsigned int retry = 0;
    unsigned int i;  // 移到函数开头
    
    // 多次尝试通信
    while(retry < 3)
    {
        IIC_Start();
        IIC_Send_Byte((daddr << 1) & 0xFE); // 确保是写命令
        
        if(IIC_Wait_Ack() == 0)
        {
            IIC_Send_Byte(addr);       // 发送寄存器地址
            if(IIC_Wait_Ack() == 0)
            {
                IIC_Send_Byte(dat);    // 发送数据
                IIC_Wait_Ack();
                IIC_Stop();
                // 成功发送，增加延时后返回
                for(i = 0; i < 50; i++) _nop_();
                return;
            }
        }
        
        IIC_Stop();
        retry++;
        // 重试前增加延时
        for(i = 0; i < 100; i++) _nop_();
    }
}

/**
 * @brief IIC起始信号 - 改进时序
 */
void IIC_Start(void)
{
    SDA = 1;
    IIC_DELAY();
    SCL = 1;
    IIC_DELAY();
    IIC_DELAY();
    SDA = 0;
    IIC_DELAY();
    SCL = 0;
    IIC_DELAY();
}

/**
 * @brief IIC停止信号 - 改进时序
 */
void IIC_Stop(void)
{
    SDA = 0;
    IIC_DELAY();
    SCL = 1;
    IIC_DELAY();
    IIC_DELAY();
    SDA = 1;
    IIC_DELAY();
}

/**
 * @brief 等待应答 - 增加超时检测
 */
bit IIC_Wait_Ack(void)
{
    bit ackbit;
    unsigned int wait_count = 0;
    
    SDA = 1;
    IIC_DELAY();
    SCL = 1;
    IIC_DELAY();
    
    // 增加超时检测
    while(SDA && (wait_count < 200))
    {
        wait_count++;
        IIC_DELAY();
    }
    
    if (wait_count >= 200)
    {
        ackbit = 1;
    } else {
        ackbit = 0;
    }
    SCL = 0;
    IIC_DELAY();
    
    return ackbit;
}
#ifndef __SOFTIIC_H__
#define __SOFTIIC_H__

// I2C引脚定义 - 数码管SCL接P15，SDA接P14
sbit SCL = P1^5;  // SCL接P15
sbit SDA = P1^4;  // SDA接P14

// 函数声明
extern void IIC_Init(void);
extern void IIC_Start(void);
extern void IIC_Stop(void);
extern bit IIC_Wait_Ack(void);
extern void IIC_Send_Byte(unsigned char dat);
extern void IIC_Write_One_Byte(unsigned char daddr, unsigned char addr, unsigned char dat);

#endif /* __SOFTIIC_H__ */
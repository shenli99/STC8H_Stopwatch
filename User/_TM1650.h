#ifndef __TM1650_H__
#define __TM1650_H__

// TM1650地址
#define TM1650_ADDR 0x24

// 亮度设置
#define TM1650_BRIGHTNESS_8 0x07  // 最亮
#define TM1650_BRIGHTNESS_7 0x06
#define TM1650_BRIGHTNESS_6 0x05
#define TM1650_BRIGHTNESS_5 0x04
#define TM1650_BRIGHTNESS_4 0x03
#define TM1650_BRIGHTNESS_3 0x02
#define TM1650_BRIGHTNESS_2 0x01
#define TM1650_BRIGHTNESS_1 0x00  // 最暗

// 函数声明
extern void TM1650_Init(unsigned char brightness);
extern void TM1650_Write(unsigned char addr, unsigned char dat);
extern void TM1650_Display_Time(unsigned char minute, unsigned char second, bit dot_flag);
extern void TM1650_Clear(void);
extern void TM1650_Test(void);
extern void TM1650_SimpleTest(void);
extern void TM1650_Display_Zero(void);

#endif /* __TM1650_H__ */
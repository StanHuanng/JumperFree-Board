/*
STC15F104E单片机特殊功能寄存器头文件
*/
#ifndef __STC15F104E_H__
#define __STC15F104E_H__

/*  BYTE Registers  */

sfr P3    = 0xB0;
sfr PSW   = 0xD0;
sfr ACC   = 0xE0;
sfr B     = 0xF0;
sfr SP    = 0x81;
sfr DPL   = 0x82;
sfr DPH   = 0x83;
/*
BIT5 LVDF 低压检测标记位 只要VCC小于芯片门槛电压 自动置1 需软件清0 同时也是低压检测中断标记位
BIT1 PD 为1进入掉电模式  硬件清0
BIT0 IDL 为1进入空闲模式 硬件清0
*/
sfr PCON  = 0x87;
sfr TCON  = 0x88;
sfr TMOD  = 0x89;
sfr TL0   = 0x8A;
sfr TL1   = 0x8B;
sfr TH0   = 0x8C;
sfr TH1   = 0x8D;
sfr IE    = 0xA8;
sfr IP    = 0xB8;

/*  PSW  */
sbit CY    = PSW^7;
sbit AC    = PSW^6;
sbit F0    = PSW^5;
sbit RS1   = PSW^4;
sbit RS0   = PSW^3;
sbit OV    = PSW^2;
sbit P     = PSW^0; //8052 only

/*  TCON  */
sbit TF1   = TCON^7;
sbit TR1   = TCON^6;
sbit TF0   = TCON^5;
sbit TR0   = TCON^4;
sbit IE1   = TCON^3;
sbit IT1   = TCON^2;
sbit IE0   = TCON^1;
sbit IT0   = TCON^0;

/*  IE  */
sbit EA    = IE^7;
sbit ELVD  = IE^6; //低压检测中断
sbit ET1   = IE^3;
sbit EX1   = IE^2;
sbit ET0   = IE^1;
sbit EX0   = IE^0;

/*  IP  */
sbit PT1   = IP^3;
sbit PX1   = IP^2;
sbit PT0   = IP^1;
sbit PX0   = IP^0;

/*  P3  */
sbit RD    = P3^7;
sbit WR    = P3^6;
sbit T1    = P3^5;
sbit T0    = P3^4;
sbit INT1  = P3^3;
sbit INT0  = P3^2;
sbit TXD   = P3^1;
sbit RXD   = P3^0;
/*IO口的设置寄存器
 四种模式
 P3M0 P1M1
 0      0    与普通的IO口一样
 0      1    设置为强推挽模式
 1      0    设置为高阻输入模式
 1      1    设置为高漏输出模式
*/

sfr P3M0=0XB2;
sfr P3M1=0XB1;
/*
AUXR寄存器
BIT7 T0X12 定时器0速度为传统12倍
BIT6 T1X12 定时器1速度为传统12倍
*/
sfr AUXR=0X8E;//不可以位寻址的
/*
CLK_DIV
时钟分频寄存器控制系统时钟的分频数。12倍速单片机上电默认是不分频的
0 0 0-晶振时钟
0 0 1-晶振时钟/2
0 1 0-晶振时钟/4
。。。。依次类推
*/
sfr CLK_DIV=0X97;


/*
内部时钟输出
IRC_CLK0 BIT7 EN_IRCO 使能时钟输出
   BIT3 DIVIRCO 为1使能内部2分频
*/
sfr IRC_CLKO=0XBB;
/*
外部中断使能和时钟输出寄存器
INT_CLKO 
BIT6 EX4 外部中断4使能   16 中断向量号
BIT5 EX3 外部中断3使能   11 中断向量号
BIT4 EX2 外部中断2使能   10 中断向量号  
BIT1 T1CLKO 允许P3.4管脚输出时钟  输出时钟频率由相应的定时器重装值来决定
BIT0 T0CLKO 允许P3.5管脚输出时钟
输出时钟频率=（sys_clk）/((256-TH0)*24)  工作在定时器方式28位自动重装模式下
*/
sfr INT_CLKO=0X8F;

/*
ISP/IAP控制寄存器
BIT7 IAPEN IAP操作使能
BIT6 SWBS 为1从ISP启动区启动 为0从用户应用程序区启动
BIT5 SWRST 为1产生软件复位
BIT4 CMD/FAIL ISP不成功该位置1
BIT2/1/0 
*/
//sfr IAP_CONTR=0XC7;
/*
看门狗控制寄存器
WDT_CONTR 
BIT7 WDT_FLAG 看门狗溢出标记
BIT5 EN_WDT 看门狗允许位
BIT4 CLR_WDT 清看门狗 为1看门狗计数值清零
BIT3 IDLE_WDT 为1在空闲模式下看门狗仍然工作
BIT2/1/0看门狗溢出时间选择
可硬件启动看门狗
*/
sfr WDT_CONTR=0XC1;

#endif

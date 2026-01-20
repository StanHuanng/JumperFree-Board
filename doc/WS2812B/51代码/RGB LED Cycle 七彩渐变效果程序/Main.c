/*------------------------------------------------------------------------------------
 * 项目名称:

     RGB LED 测试程序

 * 功能描述:

	 七彩渐变效果

 * 版权信息:

     (c) 飞翼电子, 2014.

 * 历史版本:
     2014-03-7:
       - 初始版本 V1.0.0;

 * 配置说明:
 	 - MCU    ：STC15W204S
	 - CPU频率：33MHz
-------------------------------------------------------------------------------------*/

#define Port P3
#define GREEN 0
#define RED 1
#define BLUE 2

/************************包含头文件***************************************************/

#include "STC15W.h"
#include "ws2812.h"
#include "delay.h"
#include "keypad.h"

/************************主程序*******************************************************/

void  main()
{
	unsigned char i;
	unsigned char j=0;
	unsigned char s[8][3]={{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5},
	{50,5,5},{50,5,5}};	//定义一个二维，每个括号内的三个数据对应一个像素点{G,R,B}

	DelayMs(200);					//上电等待延时

	Port=0xff;						//初始化端口为高电平

	while(1)
	{
		for(i=0;i<8;i++)	//修改数组中的数据,显示红色
		{
			s[i][RED]=85;
			s[i][GREEN]=1;
			s[i][BLUE]=1;
		}
		SendOneFrame(s);	//显示数组中的数据
		DelayMs(80);

		for(i=0;i<10;i++)	//修改数组中的数据,红到橙色渐变
		{
			for(j=0;j<8;j++)
			{
				s[j][RED]=(s[j][RED]-1);
				s[j][GREEN]=(s[j][GREEN]+2);
			}
			SendOneFrame(s);	//显示数组中的数据
			DelayMs(80);
		}

		for(i=0;i<8;i++)	//修改数组中的数据，显示橙色
		{
			s[i][RED]=75;
			s[i][GREEN]=23;
			s[i][BLUE]=0;
		}
		SendOneFrame(s);	//显示数组中的数据
		DelayMs(80);

		for(i=0;i<10;i++)	//修改数组中的数据,橙色到黄色渐变
		{
			for(j=0;j<8;j++)
			{
				s[j][GREEN]+=5;
			}
			SendOneFrame(s);	//显示数组中的数据
			DelayMs(80);
		}

		for(i=0;i<8;i++)	//修改数组中的数据,显示黄色
		{
			s[i][RED]=74;
			s[i][GREEN]=75;
			s[i][BLUE]=1;
		}
		SendOneFrame(s);	//显示数组中的数据
		DelayMs(80);	

		for(i=0;i<10;i++)	//修改数组中的数据,黄色到绿色渐变
		{
			for(j=0;j<8;j++)
			{
				s[j][RED]-=7;
				s[j][BLUE]+=1;
			}
			SendOneFrame(s);	//显示数组中的数据
			DelayMs(80);
		}

		for(i=0;i<8;i++)	//修改数组中的数据，显示绿色
		{
			s[i][RED]=0;
			s[i][GREEN]=75;
			s[i][BLUE]=9;
		}
		SendOneFrame(s);	//显示数组中的数据
		DelayMs(80);	

		for(i=0;i<10;i++)	//修改数组中的数据,绿色浅蓝色渐变
		{
			for(j=0;j<8;j++)
			{
				s[j][BLUE]+=6;
			}
			SendOneFrame(s);	//显示数组中的数据
			DelayMs(80);
		}

		for(i=0;i<8;i++)	//修改数组中的数据，显示浅蓝
		{
			s[i][RED]=0;
			s[i][GREEN]=75;
			s[i][BLUE]=72;
		}
		SendOneFrame(s);	//显示数组中的数据
		DelayMs(80);	

		for(i=0;i<10;i++)	//修改数组中的数据,浅蓝色到蓝色渐变
		{
			for(j=0;j<8;j++)
			{
				s[j][GREEN]-=7;
				s[j][BLUE]+=1;
			}
			SendOneFrame(s);	//显示数组中的数据
			DelayMs(80);
		}

		for(i=0;i<8;i++)	//修改数组中的数据,显示蓝色
		{
			s[i][RED]=4;
			s[i][GREEN]=1;
			s[i][BLUE]=82;
		}
		SendOneFrame(s);	//显示数组中的数据
		DelayMs(80);	

		for(i=0;i<10;i++)	//修改数组中的数据,蓝色紫色渐变
		{
			for(j=0;j<8;j++)
			{
				s[j][RED]+=7;
				s[j][BLUE]-=1;
			}
			SendOneFrame(s);	//显示数组中的数据
			DelayMs(80);
		}

		for(i=0;i<8;i++)	//修改数组中的数据，显示紫色
		{
			s[i][RED]=75;
			s[i][GREEN]=1;
			s[i][BLUE]=67;
		}
		SendOneFrame(s);	//显示数组中的数据

		DelayMs(80);	

		for(i=0;i<10;i++)	//修改数组中的数据,紫色到红色渐变
		{
			for(j=0;j<8;j++)
			{
				s[j][RED]+=1;
				s[j][BLUE]-=6;
			}
			SendOneFrame(s);	//显示数组中的数据
			DelayMs(80);
		}
	}
}




/************************结束*******************************************************/

/*------------------------------------------------------------------------------------
 * 项目名称:

     RGB LED 测试程序

 * 功能描述:

	 流水灯模式根据state变量的数值切换

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
	unsigned char oneTimeFlag=0;	//控制某些语句只在第一循环时被执行
	unsigned char key=0;			//存储‘读取按键’函数的返回值
	unsigned char j=0;
	unsigned char state=5;			//状态变量：更改此变量的值，可以改变闪烁的方式
	unsigned char s[8][3]={{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5},
	{50,5,5},{50,5,5}};	//定义一个二维，每个括号内的三个数据对应一个像素点{G,R,B}

	DelayMs(200);					//上电等待延时

	Port=0xff;						//初始化端口为高电平

	while(1)
	{
		key=GetKey();				//读取按键值
		if((key==1)||(key==2))		//如果有按键被按下
		{
			if(key==1)				//如果按键1被按下
			{
				state=state-1;		//当前状态值减1以切换到上一个流水灯模式
				if(state>5)
				{
					state=5;
				}
				if(state==5)
				{
					oneTimeFlag=0;
				}
			}
			else					//如果按键2被按下
			{
				state=state+1;		//当前状态加1以切换到下一流水灯模式
				if(state>5)
				{
					state=0;
				}
				if(state==5)
				{
					oneTimeFlag=0;
				}
			}
		}

		switch(state)
		{
			case 0:				    //红色、绿色、蓝色交替切换
			{
				SendOneFrame(s);	//显示数组中的数据
		
				for(i=0;i<8;i++)	//修改数组中的数据
				{
					s[i][0]=50;
					s[i][2]=5;
				}
				
				Delay100Ms(10);		
				SendOneFrame(s);	//显示数组中的数据
		
				for(i=0;i<8;i++)	//修改数组的数据
				{
					s[i][1]=50;
					s[i][0]=5;
				}
				
				Delay100Ms(10);
				SendOneFrame(s);	//显示数组中的数据
		
				for(i=0;i<8;i++)	//修改数组的数据
				{
					s[i][2]=50;
					s[i][1]=5;
				}
				
				Delay100Ms(10);
				break;
			}
			case 1:				   		//底色绿色光环，一个红色像素点绕圆环跑动
			{
				for(i=0;i<8;i++)		
				{
					s[i][0]=5;			//修改数组中的数据
					s[i][1]=50;
					s[i][2]=5;

	
					SendOneFrame(s);	//显示数组中的数据
					Delay100Ms(1);

					s[i][0]=50;
					s[i][1]=5;
					s[i][2]=5;

				}
				break;
			}
			case 2:				   		//三色交替覆盖
			{
				for(i=0;i<8;i++)
				{
					s[i][0]=5;		    //修改数组中的数据
					s[i][1]=50;
					s[i][2]=5;

					SendOneFrame(s);	//显示数组中的数据
					Delay100Ms(1);
				}

				for(i=0;i<8;i++)
				{
					s[i][0]=5;
					s[i][1]=5;
					s[i][2]=50;

					SendOneFrame(s);
					Delay100Ms(1);
				}
				for(i=0;i<8;i++)
				{
					s[i][0]=50;
					s[i][1]=5;
					s[i][2]=5;

					SendOneFrame(s);
					Delay100Ms(1);
				}
				break;
			}
			case 3:				   			//彩带跑动
			{
				if(oneTimeFlag==0)			//修改数组中的数据，只在第一次执行到case 3时执行
				{
					for(i=0;i<8;i++)	    
					{
						s[i][0]=128-(i<<2);
						s[i][1]=5+(i<<2);
						s[i][2]=5;
					}
					oneTimeFlag=1;
				}
				for(i=0;i<8;i++)
				{					
					SendOneFrameFrom(i,s);	//从低i个像素点显示数组的数据
					DelayMs(40);
				}

				break;
			}
			case 4:				   	//七彩切换
			{
				for(i=0;i<8;i++)	//修改数组中的数据,显示红色
				{
					s[i][RED]=85;
					s[i][GREEN]=1;
					s[i][BLUE]=1;
				}
				SendOneFrame(s);	//显示数组中的数据
				Delay100Ms(10);	
					
				for(i=0;i<8;i++)	//修改数组中的数据，显示橙色
				{
					s[i][RED]=75;
					s[i][GREEN]=23;
					s[i][BLUE]=0;
				}
				SendOneFrame(s);	//显示数组中的数据
				Delay100Ms(10);	
				
				for(i=0;i<8;i++)	//修改数组中的数据,显示黄色
				{
					s[i][RED]=74;
					s[i][GREEN]=75;
					s[i][BLUE]=1;
				}
				SendOneFrame(s);	//显示数组中的数据
				Delay100Ms(10);	

				for(i=0;i<8;i++)	//修改数组中的数据，显示绿色
				{
					s[i][RED]=0;
					s[i][GREEN]=75;
					s[i][BLUE]=9;
				}
				SendOneFrame(s);	//显示数组中的数据
				Delay100Ms(10);	

				for(i=0;i<8;i++)	//修改数组中的数据，显示浅蓝
				{
					s[i][RED]=0;
					s[i][GREEN]=75;
					s[i][BLUE]=72;
				}
				SendOneFrame(s);	//显示数组中的数据
				Delay100Ms(10);	

				for(i=0;i<8;i++)	//修改数组中的数据,显示蓝色
				{
					s[i][RED]=4;
					s[i][GREEN]=1;
					s[i][BLUE]=82;
				}
				SendOneFrame(s);	//显示数组中的数据
				Delay100Ms(10);	

				for(i=0;i<8;i++)	//修改数组中的数据，显示紫色
				{
					s[i][RED]=75;
					s[i][GREEN]=1;
					s[i][BLUE]=67;
				}
				SendOneFrame(s);	//显示数组中的数据
				Delay100Ms(10);	

				break;
			}
			case 5:				   	//七彩渐变
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

				break;
			}
		}
	}
}




/************************结束*******************************************************/

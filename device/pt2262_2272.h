#ifndef _ECBM_PT2262_2272_H_//头文件防止重加载必备，先看看有没有定义过这个，定义说明已经加载过一次了。
#define _ECBM_PT2262_2272_H_//没定义说明是首次加载，那么往下执行。并且定义这个宏定义，防止下一次被加载。
/*-------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2025 奈特

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

免责说明：
    本软件库以MIT开源协议免费向大众提供。作者只保证原始版本是由作者在维护修BUG，
其他通过网络传播的版本也许被二次修改过，由此出现的BUG与作者无关。而当您使用原始
版本出现BUG时，请联系作者解决。
                            ***************************
                            * 联系方式 ：进群778916610 *
                            * 若1群满人：进群927297508 *
                            ***************************
------------------------------------------------------------------------------------*/
//-----------------以下是图形设置界面，可在Configuration Wizard界面设置-----------------
//<<< Use Configuration Wizard in Context Menu >>>
//<h>PT2262部分（发送）
//<i>该模块目前还没实装。
//</h>
//<h>PT2272部分（接收）
//<i>该模块用于替代市面上的2272解码芯片，对于市面上的315M/433M发射器来说，只要它遵循2262编码方式，该模块就能解析。
//<o>基础信号宽度
//<i>单位：uS。对于不同的频率会有不同的宽度，请根据实际情况自行修改。默认值为315M对应的宽度。
#define PT2272_BASE_WIDTH    (359)
//<o>信号宽裕度
//<i>可输入10~50，代表10%~50%的宽裕度。
//<i>假如基础信号宽度为359uS，宽裕度为50，那么179uS~538uS的信号都可以接收。
//<i>模块的晶振会有误差，单片机的主频也有误差。中断响应优先级等等因素都会导致测量时间有误差。
//<i>如果宽裕度设置太小的话，可能正常的信号都不能通过校验，导致信号丢失。
//<i>但是宽裕度设置太大的话，也会让干扰信号通过校验，导致出现误码。所以需要根据实际情况来设置。
//<10-50>
#define PT2272_WIDTH_MARGIN  (20)
//<o>接收引脚
//<i>只能在支持上下沿中断的P32和P33里选。
//<i>该功能会占用整个外部中断函数，请确保该脚没有被其他功能占用，否则就会编译冲突！
//<i>pt2272_init会处理好初始化，不需要额外在ecbm_core.h里设置。
//<0=>P32
//<2=>P33
#define PT2272_FUNCTION_EXTI    0
//<o>计时用的定时器
//<i>该功能会占用整个定时器，请注意不要和串口之类的定时器冲突！
//<i>pt2272_init会处理好初始化，不需要额外在ecbm_core.h里设置。
//<0=>定时器0
//<1=>定时器1
//<2=>定时器2
//<3=>定时器3
//<4=>定时器4
#define PT2272_FUNCTION_TIMER   (0)
//</h>
//<<< end of configuration section >>>
//-----------------以上是图形设置界面，可在Configuration Wizard界面设置-----------------
/*-------------------------------------头文件加载-----------------------------------*/
#include "ecbm_core.h"    //ECBM库的头文件，里面已经包含了STC8的头文件。
/*---------------------------------------宏定义------------------------------------*/
#define PT2272_STATE_IDLE   (0)//空闲状态
#define PT2272_STATE_SYNC_H (1)//读取同步码高电平时间状态
#define PT2272_STATE_SYNC_L (2)//读取同步码低电平时间状态
#define PT2272_STATE_DATA_H (3)//读取数据高电平时间状态
#define PT2272_STATE_DATA_0 (4)//读取数据0低电平时间状态
#define PT2272_STATE_DATA_1 (5)//读取数据1低电平时间状态

#define PT2272_BASE_WIDTH_MIN   ((u16)(((PT2272_BASE_WIDTH-((PT2272_BASE_WIDTH*PT2272_WIDTH_MARGIN)/100))*(ECBM_SYSCLK_SETTING/12000UL))/1000UL))
#define PT2272_BASE_WIDTH_MAX   ((u16)(((PT2272_BASE_WIDTH+((PT2272_BASE_WIDTH*PT2272_WIDTH_MARGIN)/100))*(ECBM_SYSCLK_SETTING/12000UL))/1000UL))


#if (PT2272_FUNCTION_EXTI==0)
#define PT2272_IO   (P32)
#else
#define PT2272_IO   (P33)
#endif
#if   (PT2272_FUNCTION_TIMER==0)
#define PT2272_TIMER_START  {TIMER0_SET_REG_HL(0);TIMER0_POWER_ON;}
#define PT2272_TIMER_STOP   {TIMER0_POWER_OFF;}
#define PT2272_TIMER_VALUE  (TIMER0_GET_REG_HL)
#elif (PT2272_FUNCTION_TIMER==1)
#define PT2272_TIMER_START  {TIMER1_SET_REG_HL(0);TIMER1_POWER_ON;}
#define PT2272_TIMER_STOP   {TIMER1_POWER_OFF;}
#define PT2272_TIMER_VALUE  (TIMER1_GET_REG_HL)
#elif (PT2272_FUNCTION_TIMER==2)
#define PT2272_TIMER_START  {TIMER2_SET_REG_HL(0);TIMER2_POWER_ON;}
#define PT2272_TIMER_STOP   {TIMER2_POWER_OFF;}
#define PT2272_TIMER_VALUE  (TIMER2_GET_REG_HL)
#elif (PT2272_FUNCTION_TIMER==3)
#define PT2272_TIMER_START  {TIMER3_SET_REG_HL(0);TIMER3_POWER_ON;}
#define PT2272_TIMER_STOP   {TIMER3_POWER_OFF;}
#define PT2272_TIMER_VALUE  (TIMER3_GET_REG_HL)
#elif (PT2272_FUNCTION_TIMER==4)
#define PT2272_TIMER_START  {TIMER4_SET_REG_HL(0);TIMER4_POWER_ON;}
#define PT2272_TIMER_STOP   {TIMER4_POWER_OFF;}
#define PT2272_TIMER_VALUE  (TIMER4_GET_REG_HL)
#endif
/*--------------------------------------变量定义-----------------------------------*/
extern bit pt2272_flag;    //接收完成标志。
extern u32 pt2272_value;   //接收到的数据。
/*--------------------------------------程序定义-----------------------------------*/
/*-------------------------------------------------------
函数名：pt2272_init
描  述：PT2272初始化函数。
输  入：无
输  出：无
返回值：无
创建者：奈特
调用例程：无
创建日期：2025-07-04
修改记录：
-------------------------------------------------------*/
extern void pt2272_init(void);
/*-------------------------------------------------------
函数名：pt2272_value2addr
描  述：PT2272编码转地址函数。
输  入：
    dat     接收到的原始数据。
    len     地址的长度。
输  出：无
返回值：
    转换后的地址。
创建者：奈特
调用例程：无
创建日期：2025-07-04
修改记录：
-------------------------------------------------------*/
extern u16 pt2272_value2addr(u32 dat,u8 len);
/*-------------------------------------------------------
函数名：pt2272_value2dat
描  述：PT2272编码转数据函数。
输  入：
    dat     接收到的原始数据。
    len     数据的长度。
输  出：无
返回值：
    转换后的数据。
创建者：奈特
调用例程：无
创建日期：2025-07-04
修改记录：
-------------------------------------------------------*/
extern u8 pt2272_value2dat(u32 dat,u8 len);

#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。
#ifndef _ECBM_BS818A_H_//头文件防止重加载必备，先看看有没有定义过这个，定义说明已经加载过一次了。
#define _ECBM_BS818A_H_//没定义说明是首次加载，那么往下执行。并且定义这个宏定义，防止下一次被加载。
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
/*-------------------------------------头文件加载-----------------------------------*/
#include "ecbm_core.h"    //ECBM库的头文件，里面已经包含了STC8的头文件。
/*---------------------------------------宏定义------------------------------------*/
typedef struct{
    u8  clk;//时钟脚。
    u8  dat;//数据脚。
    u8  key;//按键数据。
}bs818a_def;
/*--------------------------------------程序定义-----------------------------------*/
/*-------------------------------------------------------
函数名：bs818a_init
描  述：BS818A初始化函数，要记得悬空OMS脚。
输  入：
    clk     串行通信的时钟线。
    dat     串行通信的数据线。
输  出：
    dev     BS818A结构体。
返回值：无
创建者：奈特
调用例程：无
创建日期：2025-06-15
修改记录：
-------------------------------------------------------*/
extern void bs818a_init(bs818a_def * dev,u8 clk,u8 dat);
/*-------------------------------------------------------
函数名：bs818a_run
描  述：BS818A运行函数。
输  入：
    dev         BS818A结构体。
输  出：
    dev.key     按键键值。
返回值：无
创建者：奈特
调用例程：无
创建日期：2025-06-15
修改记录：
-------------------------------------------------------*/
extern void bs818a_run(bs818a_def * dev);
#endif  //和最上面的#ifndef配合成一个程序段。
        //以一个空行为结尾。
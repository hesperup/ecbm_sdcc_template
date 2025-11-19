#include "bs818a.h"  //统一加载核心头文件
/*--------------------------------------程序定义-----------------------------------*/
/*-------------------------------------------------------
BS818A初始化函数。
-------------------------------------------------------*/
void bs818a_init(bs818a_def * dev,u8 clk,u8 dat){ 
    dev->clk=clk;           //填充结构体。
    dev->dat=dat;
    gpio_mode(clk,GPIO_OUT);//根据引脚作用设置对应的模式。
    gpio_mode(dat,GPIO_IN);
}
/*-------------------------------------------------------
BS818A运行函数。
-------------------------------------------------------*/
void bs818a_run(bs818a_def * dev){
    u16 temp,delay_30us;
    u8 i,j,count;
    u8 clk,dat,key;
    clk=dev->clk;
    dat=dev->dat;
    delay_30us=delay_set_us(30);
    gpio_out(dat,1);//初始状态。
    gpio_out(clk,1);
    temp=0;         //清零变量。
    for(i=0;i<16;i++){ 
        gpio_out(clk,0);    //时钟拉低。
        delay_us(delay_30us);
        temp>>=1;           //数据移动，同时会当成一个小延时。
        gpio_out(clk,1);    //时钟拉高。
        delay_us(delay_30us);
        if(gpio_in(dat)){//读数据。
            temp|=0x8000;//存到缓存里。
        }
    }
    dev->key=0xFF;
    if((temp&0xF000)==0xA000){  //校验停止位。
        key=(u8)(temp&0x00FF);  //取出按键状态。
        j=(u8)((temp&0x0F00)>>8);//取出按键次数。
        count=0;                //按键次数清零。
        for(i=0;i<8;i++){
            if((key&(1<<i))==0){//计算出按下的个数。
                count++;
            }
        }
        if(j==count){//二次验证。
            dev->key=key;
        }
    }
}

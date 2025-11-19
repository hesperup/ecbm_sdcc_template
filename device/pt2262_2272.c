#include "pt2262_2272.h"
/*--------------------------------------变量定义-----------------------------------*/
bit pt2272_flag;    //接收完成标志。
u32 pt2272_value;   //接收到的数据。

u16 pt2272_h_time;  //测量高电平的时间。
u16 pt2272_l_time;  //测量低电平的时间。
u8  pt2272_state;   //接收状态机变量。
u8  pt2272_bit;     //接收的位数。
/*--------------------------------------程序定义-----------------------------------*/
/*-------------------------------------------------------
PT2272初始化函数。
-------------------------------------------------------*/
void pt2272_init(void){
    pt2272_flag=0;
    pt2272_value=0;

    pt2272_h_time=0;
    pt2272_l_time=0;
    pt2272_state=PT2272_STATE_IDLE;
    pt2272_bit=0;
    #if (PT2272_FUNCTION_EXTI == 0) 
        gpio_mode(D32,GPIO_IN); //设置P32为输入状态。
        EXTI0_SET_IO_HIGH;      //置一，防止内部接地影响读取。       
        EXTI0_SET_MODE_UP_DOWN; //设置上升沿/下降沿中断。
        EXTI0_ENABLE;           //使能中断。
    #else
        gpio_mode(D33,GPIO_IN); //设置P33为输入状态。
        EXTI1_SET_IO_HIGH;      //置一，防止内部接地影响读取。   
        EXTI1_SET_MODE_UP_DOWN; //设置上升沿/下降沿中断。
        EXTI1_ENABLE;           //使能中断。
    #endif
    #if   (PT2272_FUNCTION_TIMER==0)
        TIMER0_IT_DISABLE;
        TIMER0_GATE_DISABLE;
        TIMER0_OUT_OFF;
        TIMER0_SET_MODE_TIMER;
        TIMER0_SET_MODE_AUTO16;
        TIMER0_SET_MODE_12T;
        TIMER0_SET_REG_HL(0);
    #elif (PT2272_FUNCTION_TIMER==1)
        TIMER1_IT_DISABLE;
        TIMER1_GATE_DISABLE;
        TIMER1_OUT_OFF;
        TIMER1_SET_MODE_TIMER;
        TIMER1_SET_MODE_AUTO16;
        TIMER1_SET_MODE_12T;
        TIMER1_SET_REG_HL(0);
    #elif (PT2272_FUNCTION_TIMER==2)
        TIMER2_IT_DISABLE;
        TIMER2_OUT_OFF;
        TIMER2_SET_MODE_TIMER;
        TIMER2_SET_MODE_12T;
        TIMER2_SET_REG_HL(0);
    #elif (PT2272_FUNCTION_TIMER==3)
        TIMER3_IT_DISABLE;
        TIMER3_OUT_OFF;
        TIMER3_SET_MODE_TIMER;
        TIMER3_SET_MODE_12T;
        TIMER3_SET_REG_HL(0);
    #elif (PT2272_FUNCTION_TIMER==4)
        TIMER4_IT_DISABLE;
        TIMER4_OUT_OFF;
        TIMER4_SET_MODE_TIMER;
        TIMER4_SET_MODE_12T;
        TIMER4_SET_REG_HL(0);
    #endif
}
/*-------------------------------------------------------
PT2272编码转地址函数。
-------------------------------------------------------*/
u16 pt2272_value2addr(u32 dat,u8 len){
    u32 mask;
    u16 temp;
    u8  i;
    temp=0;
    for(i=0;i<len;i++){
        //地址区是A0到Ax的排列顺序，x为不固定值，所以得从A0开始读。
        mask=(dat<<(i*2))&0x00C00000;//计算出编码值，这样下面判断的时候，就不用再计算了。
        switch(mask){
            case 0x00C00000:temp|=0x03<<(i*2);break;//1的编码。
            case 0x00400000:temp|=0x01<<(i*2);break;//悬空的编码。
        }                                           //其他编码按0处理就行了。
    }
    return temp;
}
/*-------------------------------------------------------
PT2272编码转数据函数。
-------------------------------------------------------*/
u8 pt2272_value2dat(u32 dat,u8 len){
    u8 temp,i;
    temp=0;
    for(i=0;i<len;i++){
        //数据区是Dx到D0的排列顺序，x为不固定值，所以得从D0开始读。
        if(((dat>>(i*2))&0x00000003)==0x00000003){//由于PT2262的数据输入脚自带下拉，不存在悬空。
            temp|=0x01<<i;          //所以只有编码11才是1，将1写入到缓存。
        }                           //其他编码都看作是0，不处理即可。
    }
    return temp;
}
/*-------------------------------------------------------
PT2272解码主函数。
-------------------------------------------------------*/
void pt2272_main(void)interrupt PT2272_FUNCTION_EXTI{
    switch(pt2272_state){
        case PT2272_STATE_IDLE:{    //空闲状态。
            if(PT2272_IO==1){       //上升沿触发了。
                pt2272_state=PT2272_STATE_SYNC_H;     //到读取同步码高电平时间状态。
                PT2272_TIMER_START; //打开定时器。
            }
        }break;
        case PT2272_STATE_SYNC_H:{  //读取同步码高电平时间状态
            PT2272_TIMER_STOP;      //停止计时。
            if(PT2272_IO==0){       //如果是下降沿触发，
                pt2272_h_time=PT2272_TIMER_VALUE;//拼凑出高电平时间。
                if((PT2272_BASE_WIDTH_MIN<pt2272_h_time)&&(pt2272_h_time<PT2272_BASE_WIDTH_MAX)){//当高电平时间满足标准时，
                    pt2272_state=PT2272_STATE_SYNC_L;//到读取同步码低电平时间状态
                    PT2272_TIMER_START;              //打开定时器。
                }else{//时间不合法的话，说明是干扰。
                    pt2272_state=PT2272_STATE_IDLE;  //回到空闲状态。
                }
            }else{//假如因为某些情况，漏掉了下降沿，当前还是上升沿，那么就在本状态里继续等。
                PT2272_TIMER_START;              //打开定时器。
            }
        }break;
        case PT2272_STATE_SYNC_L:{  //读取同步码低电平时间状态
            PT2272_TIMER_STOP;      //停止计时。
            if(PT2272_IO==1){       //如果是上升沿触发，
                pt2272_l_time=PT2272_TIMER_VALUE;//拼凑出低电平时间。
                if(((PT2272_BASE_WIDTH_MIN*32)<pt2272_l_time)&&(pt2272_l_time<(PT2272_BASE_WIDTH_MAX*32))){//是正确的同步码的话，
                    pt2272_value=0; //清零结果变量。 
                    pt2272_bit  =0; //清零计数变量。              
                    pt2272_state=PT2272_STATE_DATA_H;//到读取数据高电平状态。
                }else{//如果不是同步码，既然还是上升沿，
                    pt2272_state=PT2272_STATE_SYNC_H;//到读取同步码高电平时间状态
                }
                PT2272_TIMER_START;//打开定时器。
            }else{//假如因为某些情况，漏掉了上升沿，当前还是下降沿，那么就重新开始。
                pt2272_state=PT2272_STATE_IDLE;//回到空闲状态
            }
        }break;
        case PT2272_STATE_DATA_H:{  //读取数据高电平状态
            PT2272_TIMER_STOP;      //停止计时。
            if(PT2272_IO==0){       //如果是下降沿，那么高电平时间结束。
                pt2272_h_time=PT2272_TIMER_VALUE;//计算出高电平的时间。
                PT2272_TIMER_START;//打开定时器。
                //将两段电平的测量分摊到3个状态里，避免下一个状态的计算时间过长。
                if((PT2272_BASE_WIDTH_MIN<pt2272_h_time)&&(pt2272_h_time<PT2272_BASE_WIDTH_MAX)){
                    pt2272_state=PT2272_STATE_DATA_0;
                }else if(((PT2272_BASE_WIDTH_MIN*3)<pt2272_h_time)&&(pt2272_h_time<(PT2272_BASE_WIDTH_MAX*3))){
                    pt2272_state=PT2272_STATE_DATA_1;
                }else{//要是不在这两个时间范围内，说明是错误。
                    pt2272_state=PT2272_STATE_IDLE;//回到初始状态。
                }
            }else{//这个状态不能出现上升沿，否则就是错误。
                pt2272_state=PT2272_STATE_IDLE;//回到初始状态。
            }
        }break;
        case PT2272_STATE_DATA_0:{  //读取数据低电平状态
            PT2272_TIMER_STOP;      //停止计时。
            if(PT2272_IO==1){       //如果是上升沿，那么低电平时间结束。
                pt2272_l_time=PT2272_TIMER_VALUE;//计算出低电平的时间。
                PT2272_TIMER_START;//打开定时器。
                if(((PT2272_BASE_WIDTH_MIN*3)<pt2272_l_time)&&(pt2272_l_time<(PT2272_BASE_WIDTH_MAX*3))){//检查时间对不对。
                    pt2272_bit++;       //此时得到一个正确的边沿，计数加一。
                    pt2272_value<<=1;   //数据左移一位。
                                        //这个编码是0，不做额外处理。
                    pt2272_state=PT2272_STATE_DATA_H;//到读取数据高电平状态。
                }else if(((PT2272_BASE_WIDTH_MIN*32)<pt2272_l_time)&&(pt2272_l_time<(PT2272_BASE_WIDTH_MAX*32))){//如果时间和同步码符合的话，
                    pt2272_value=0; //清零结果变量。 
                    pt2272_bit  =0; //清零计数变量。              
                    pt2272_state=PT2272_STATE_DATA_H;//到读取数据高电平状态。
                }else{//时间校验不对，当前数据放弃。不过这里是上升沿，
                    pt2272_state=PT2272_STATE_SYNC_H;//可以提前到读取同步高电平状态，等待下一个同步帧。
                }
            }else{//这个状态不能出现下降沿，否则就是错误。
                pt2272_state=PT2272_STATE_IDLE;//回到初始状态。
            }
            if(pt2272_bit>=24){ //12位数据，共24位编码。
                pt2272_flag=1;  //接收数据完成。
                pt2272_state=PT2272_STATE_SYNC_H;//多半后面还有数据，到读取同步码高电平时间状态。
            }
        }break;
        case PT2272_STATE_DATA_1:{  //读取数据低电平状态
            PT2272_TIMER_STOP;      //停止计时。
            if(PT2272_IO==1){       //如果是上升沿，那么低电平时间结束。
                pt2272_l_time=PT2272_TIMER_VALUE;//计算出低电平的时间。
                PT2272_TIMER_START;//打开定时器。
                if(((PT2272_BASE_WIDTH_MIN)<pt2272_l_time)&&(pt2272_l_time<(PT2272_BASE_WIDTH_MAX))){//检查时间对不对。
                    pt2272_bit++;       //此时得到一个正确的边沿，计数加一。
                    pt2272_value<<=1;   //数据左移一位。
                    pt2272_value|=1;    //这个编码是1，结果变量或上1。
                    pt2272_state=PT2272_STATE_DATA_H;//到读取数据高电平状态。
                }else{//时间校验不对，当前数据放弃。不过这里是上升沿，
                    pt2272_state=PT2272_STATE_SYNC_H;//可以提前到读取同步高电平状态，等待下一个同步帧。
                }
            }else{//这个状态不能出现下降沿，否则就是错误。
                pt2272_state=PT2272_STATE_IDLE;//回到初始状态。
            }
            if(pt2272_bit>=24){ //12位数据，共24位编码。
                pt2272_flag=1;  //接收数据完成。
                pt2272_state=PT2272_STATE_SYNC_H;//多半后面还有数据，到读取同步码高电平时间状态。
            }
        }break;
    }
}
#include "ecbm_core.h" 

u32 count;
u16 j;


 void timer_start(u8 id);

 void timer_init(void);

 void timer_set_timer_mode(u8 id,u16 us);

void Init_Timer0(void);

/* void Timer0_isr(void) __interrupt 1;*/
void nvic_timer0_function(void) __interrupt (1);

void Init_Timer0(void)		
{
	TMOD |= 0x01;	     
	TH0=0x00;	      
	TL0=0x00;
  EA_ENABLE;
  TIMER0_IT_ENABLE;
  TIMER0_POWER_ON;
}

/*
void Timer0_isr(void) __interrupt 1
{
	TH0=0x00;		 
	TL0=0x00;
	P1= ~P1;
}
*/
void main(void){  
    count = 0;  
    system_init();
    timer_init();
    timer_set_timer_mode(0,10000);
    timer_start(0);
    P1 = 0x00;
     for( j=200;j>0;j--)
    {
      P36^=1;      
      delay_us(500);   
    }
    while(1){
        
    }
  
}


void timer0_it_callback(void){
   /* P1 = ~P1; */
  if (count-- == 0) 
  {
    count = 1000; 
    P1 = ~P1;
  }
  
}



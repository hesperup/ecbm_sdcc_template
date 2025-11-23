 #include "ecbm_core.h" 
 #include <stdio.h>

#if defined(SDCC) || defined(__SDCC)

 void nvic_timer0_function(void) __interrupt (1); 
 
 void nvic_uart1_function(void) __interrupt (4);

#endif

  u16 j;
  u16 m;
  u16 n;
  u16 t;
  u32 count;
  u16 i;
  u8 num,a;
  u8 fval ;
void main(void){  
    count = 0;  
    i=0;
    system_init();
    
    timer_init();
    timer_set_timer_mode(0,30000);
    timer_start(0);
    // P1 = 0x00; 
    uart_init();
    eeprom_init();
    for( j=100;j>0;j--)
    {
      P36^=1;      
      delay_us(500);   
    }
    uart_string(1,"Hello World");
 
    delay_ms(100);   

    uart_char(1,'7');
    uart_char(1,'8');
    uart_char(1,'9');

    eeprom_erase(0);
    eeprom_write(0,'2');

    delay_ms(500);   

    
    fval= eeprom_read(0);
    uart_char(1,fval);


     uart_string(1,"fuckyou");
    // uart_string(1,fval);
   
    // eeprom_erase(20);

    // eeprom_write(20,0x02);

    // delay_ms(1000);   

    // u8 sval=eeprom_read(20);

    // uart_char(1,sval);

    // uart_char(1,0);
    while(1){

    }
}


 void timer0_it_callback(void){
  
  if (count-- == 0) 
  {
    count = 333; 
    P1 = ~P1; 
  } 
} 

void uart1_receive_callback(void){
    P36^=1;  
    uart_char(1,SBUF);
}

void uart1_send_callback(void){
    P36^=1; 
}
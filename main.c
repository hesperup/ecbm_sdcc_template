 #include "ecbm_core.h" 

// #if defined(SDCC) || defined(__SDCC)

 void nvic_timer0_function(void) __interrupt (1); 
 
 void nvic_uart1_function(void) __interrupt (4);

// #endif

  u16 j;
  u16 m;
  u16 n;
  u16 t;
  u32 count;
  u16 i;
  u8 num,a;
//  void timer_start(u8 id);

//  void timer_init(void);

//  void timer_set_timer_mode(u8 id,u16 us);



void main(void){  
    count = 0;  
    i=0;
    system_init();
    
    timer_init();
    timer_set_timer_mode(0,30000);
    timer_start(0);
    // P1 = 0x00; 

    /* eeprom_init();
    eeprom_write(20,25);

    delay_us(500);   

    u8 fval=eeprom_read(20);
    uart_char(1,fval);
    eeprom_erase(20);

    eeprom_write(20,15);

    delay_us(500);   

    u8 sval=eeprom_read(20);

    uart_char(1,sval); */

    for( j=200;j>0;j--)
    {
      P36^=1;      
      delay_us(500);   
    }

    // uart_init();
    // unsigned int i=0;
    // uart_set_io(1,UART1_PIN_P30_P31);
    // uart_set_baud(1,9600); */
    
  
    uart_char(1,'2');
}


 void timer0_it_callback(void){
  
  if (count-- == 0) 
  {
    count = 333; 
    P1 = ~P1; 
    // P1 = 0xff;
    uart_char(1,1);
  } 
} 
void uart1_beep_callback(void){
    P36= 0x00;
}
void uart1_receive_callback(void){
     P36= 0x00;
}

void uart1_send_callback(void){
    P36= 0x00;
}
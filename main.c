 #include "ecbm_core.h" 


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

  u8 TxStr[3] = {0};
  u8 dat[2] ={'1','B'};
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
    delay_ms(200);   
    eeprom_write(1,dat[0]);
    delay_ms(200);   
    u8 fval = eeprom_read(1);     //从地址0x2001读取一个字节
    TxStr[0] = fval;  
    uart_char(1,fval);
    uart_char(1,TxStr[0]);
    delay_ms(200);   
    eeprom_write(2,dat[1]);
    delay_ms(200);   
    u8 fTval = eeprom_read(2);     //从地址0x2001读取一个字节
    TxStr[1] = fTval;

    delay_ms(200);   
    //todo need to fix 重新读取后不知为何变成B
    uart_char(1,eeprom_read(1));    //从地址0x2001读取一个字节
    uart_char(1,fval);
    uart_char(1,TxStr[0]);
    uart_char(1,fTval);
    uart_char(1,TxStr[1]);
    uart_string(1,TxStr);
    // delay_ms(500);   
    // TxStr[1] = eeprom_read(0x2002);
    // uart_char(1,TxStr[1]);
    // uart_string(1,TxStr);
    // SectorErase(0x2000);    //擦除第一扇区
    // byte_write(0x2001,dat[0]);   //在地址为0x2001的内存写入一个字节
    // byte_write(0x2002,dat[1]);   //在地址为0x2002的内存写入一个字节
    // delay_ms(200);       //延时1s
    // TxStr[0] = byte_read(0x2001);     //从地址0x2001读取一个字节
    // TxStr[1] = byte_read(0x2002);
    // uart_string(1,TxStr);

    uart_string(1,"fuckyou");
    // uart_string(1,fval);
   
    eeprom_erase(0);

    eeprom_write(1,dat[1]);

    delay_ms(200);   

    u8 sval=eeprom_read(1);

    uart_char(1,sval);

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
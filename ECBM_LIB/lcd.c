#include "ecbm_core.h"
#if (ECBM_LCD_LIB_EN)

union{
    u32 num32;
    u16 num16[2];
    u8  num8[4];
}lcd_cout;


void lcd_init(void){
	u32	value_u32,clk_u32,com_u32;
    com_u32=0;
    #if (ECBM_LCD_COMX_EN&0x01)
        gpio_mode(D50,GPIO_HZ);
        com_u32++;
    #endif
    #if (ECBM_LCD_COMX_EN&0x02)
        gpio_mode(D51,GPIO_HZ);
        com_u32++;
    #endif
    #if (ECBM_LCD_COMX_EN&0x04)
        gpio_mode(D35,GPIO_HZ);
        com_u32++;
    #endif
    #if (ECBM_LCD_COMX_EN&0x08)
        gpio_mode(D36,GPIO_HZ);
        com_u32++;
    #endif
    LCD_SET_REG_CFG(ECBM_LCD_CFG);
	LCD_SET_REG_DBLEN(ECBM_LCD_DBLEN);
    #if (ECBM_LCD_CFG&0x80)
        clk_u32=32768;
    #else
        clk_u32=ECBM_SYSCLK_SETTING;
    #endif
    value_u32=clk_u32/(2*com_u32*ECBM_LCD_FRAMERATE)-1-ECBM_LCD_DBLEN;

    lcd_cout.num32=value_u32;
    LCD_SET_REG_COMLENL(lcd_cout.num8[3]);
    LCD_SET_REG_COMLENM(lcd_cout.num8[2]);
    LCD_SET_REG_COMLENH(lcd_cout.num8[1]);


    LCD_SET_REG_BLINKRATE(ECBM_LCD_FRAMERATE/ECBM_LCD_BLANKRATE);
	LCD_SET_REG_COMON(ECBM_LCD_COMX_EN);
    LCD_SET_REG_SEGON1(ECBM_LCD_SEG0_EN|ECBM_LCD_SEG1_EN|ECBM_LCD_SEG2_EN|ECBM_LCD_SEG3_EN|ECBM_LCD_SEGON1);
    LCD_SET_REG_SEGON2(ECBM_LCD_SEGON2);
    LCD_SET_REG_SEGON3(ECBM_LCD_SEGON3);
    LCD_SET_REG_SEGON4(ECBM_LCD_SEGON4);
    LCD_SET_REG_SEGON5(ECBM_LCD_SEGON5);
    LCD_SET_REG_CFG2(ECBM_LCD_CFG2_SEG0|ECBM_LCD_CFG2_SEG1|ECBM_LCD_CFG2_SEG2|ECBM_LCD_CFG2_SEG3);
    #if (ECBM_LCD_SEG0_EN==0x01)
        #if (ECBM_LCD_CFG2_SEG0==0x00)
            gpio_mode(D15,GPIO_HZ);
        #else
            gpio_mode(D77,GPIO_HZ);
        #endif
    #endif
    #if (ECBM_LCD_SEG1_EN==0x02)
        #if (ECBM_LCD_CFG2_SEG1==0x00)
            gpio_mode(D14,GPIO_HZ);
        #else
            gpio_mode(D76,GPIO_HZ);
        #endif
    #endif
    #if (ECBM_LCD_SEG2_EN==0x04)
        #if (ECBM_LCD_CFG2_SEG2==0x00)
            gpio_mode(D13,GPIO_HZ);
        #else
            gpio_mode(D75,GPIO_HZ);
        #endif
    #endif
    #if ((ECBM_LCD_SEG3_EN==0x08)&&(ECBM_LCD_CFG2_SEG3==0x08))
        gpio_mode(D74,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON1&0x10)
        gpio_mode(D47,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON1&0x20)
        gpio_mode(D11,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON1&0x40)
        gpio_mode(D10,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON1&0x80)
        gpio_mode(D07,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON2&0x01)
        gpio_mode(D06,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON2&0x02)
        gpio_mode(D05,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON2&0x04)
        gpio_mode(D53,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON2&0x08)
        gpio_mode(D52,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON2&0x10)
        gpio_mode(D04,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON2&0x20)
        gpio_mode(D03,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON2&0x40)
        gpio_mode(D02,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON2&0x80)
        gpio_mode(D01,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON3&0x01)
        gpio_mode(D00,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON3&0x02)
        gpio_mode(D46,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON3&0x04)
        gpio_mode(D45,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON3&0x08)
        gpio_mode(D27,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON3&0x10)
        gpio_mode(D26,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON3&0x20)
        gpio_mode(D25,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON3&0x40)
        gpio_mode(D24,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON3&0x80)
        gpio_mode(D23,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON4&0x01)
        gpio_mode(D22,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON4&0x02)
        gpio_mode(D21,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON4&0x04)
        gpio_mode(D20,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON4&0x08)
        gpio_mode(D44,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON4&0x10)
        gpio_mode(D43,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON4&0x20)
        gpio_mode(D42,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON4&0x40)
        gpio_mode(D41,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON4&0x80)
        gpio_mode(D37,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON5&0x01)
        gpio_mode(D73,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON5&0x02)
        gpio_mode(D72,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON5&0x04)
        gpio_mode(D71,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON5&0x08)
        gpio_mode(D70,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON5&0x10)
        gpio_mode(D60,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON5&0x20)
        gpio_mode(D61,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON5&0x40)
        gpio_mode(D62,GPIO_HZ);
    #endif
    #if (ECBM_LCD_SEGON5&0x80)
        gpio_mode(D63,GPIO_HZ);
    #endif

    LCD_SET_REG_C0S0_7(0);
    LCD_SET_REG_C0S8_15(0);
    LCD_SET_REG_C0S16_23(0);
    LCD_SET_REG_C0S24_31(0);
    LCD_SET_REG_C0S32_39(0);
    LCD_SET_REG_C1S0_7(0);
    LCD_SET_REG_C1S8_15(0);
    LCD_SET_REG_C1S16_23(0);
    LCD_SET_REG_C1S24_31(0);
    LCD_SET_REG_C1S32_39(0);
    LCD_SET_REG_C2S0_7(0);
    LCD_SET_REG_C2S8_15(0);
    LCD_SET_REG_C2S16_23(0);
    LCD_SET_REG_C2S24_31(0);
    LCD_SET_REG_C2S32_39(0);
    LCD_SET_REG_C3S0_7(0);
    LCD_SET_REG_C3S8_15(0);
    LCD_SET_REG_C3S16_23(0);
    LCD_SET_REG_C3S24_31(0);
    LCD_SET_REG_C3S32_39(0);

    LCD_SET_REG_CR(ECBM_LCD_CR);
    LCD_POWER_ON;
}

void lcd_write(u8 com,u8 group,u8 dat){
    switch(com){
        default:break;
        case 0:{
            switch(group){
                default:break;
                case 0:{LCD_SET_REG_C0S0_7(dat);}break;
                case 1:{LCD_SET_REG_C0S8_15(dat);}break;
                case 2:{LCD_SET_REG_C0S16_23(dat);}break;
                case 3:{LCD_SET_REG_C0S24_31(dat);}break;
                case 4:{LCD_SET_REG_C0S32_39(dat);}break;
            }
        }break;
        case 1:{
            switch(group){
                default:break;
                case 0:{LCD_SET_REG_C1S0_7(dat);}break;
                case 1:{LCD_SET_REG_C1S8_15(dat);}break;
                case 2:{LCD_SET_REG_C1S16_23(dat);}break;
                case 3:{LCD_SET_REG_C1S24_31(dat);}break;
                case 4:{LCD_SET_REG_C1S32_39(dat);}break;
            }
        }break;
        case 2:{
            switch(group){
                default:break;
                case 0:{LCD_SET_REG_C2S0_7(dat);}break;
                case 1:{LCD_SET_REG_C2S8_15(dat);}break;
                case 2:{LCD_SET_REG_C2S16_23(dat);}break;
                case 3:{LCD_SET_REG_C2S24_31(dat);}break;
                case 4:{LCD_SET_REG_C2S32_39(dat);}break;
            }
        }break;
        case 3:{
            switch(group){
                default:break;
                case 0:{LCD_SET_REG_C3S0_7(dat);}break;
                case 1:{LCD_SET_REG_C3S8_15(dat);}break;
                case 2:{LCD_SET_REG_C3S16_23(dat);}break;
                case 3:{LCD_SET_REG_C3S24_31(dat);}break;
                case 4:{LCD_SET_REG_C3S32_39(dat);}break;
            }
        }break;
    }
}
#endif


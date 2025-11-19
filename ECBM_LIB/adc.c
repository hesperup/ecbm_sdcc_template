#include "ecbm_core.h"
#if (ECBM_ADC_LIB_EN)

float xdata adc_ch15_gxf;


void adc_init(void){
    ADC_SET_REG_CFG(ECBM_ADC_CFG);
    adc_ch15_gxf=(float)(REG_BGV)/1000.0f;
    #if (ECBM_ADC_IT_EN)
        ADC_IT_ENABLE;
    #endif
    #if (ECBM_ADC_PWM_EN)
        ADC_PWM_ENABLE;
    #endif
    #if (ECBM_MCU==0x2815C4)
        ADC_SET_REG_EXCFG(ECBM_ADC_EXCFG);
    #endif
    #if (ECBM_ADC_CH0_EN)
        gpio_mode(A00,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH1_EN)
        gpio_mode(A01,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH2_EN)
        gpio_mode(A02,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH3_EN)
        gpio_mode(A03,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH4_EN)
        gpio_mode(A04,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH5_EN)
        gpio_mode(A05,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH6_EN)
        gpio_mode(A06,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH7_EN)
        gpio_mode(A07,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH8_EN)
        gpio_mode(A08,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH9_EN)
        gpio_mode(A09,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH10_EN)
        gpio_mode(A10,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH11_EN)
        gpio_mode(A11,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH12_EN)
        gpio_mode(A12,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH13_EN)
        gpio_mode(A13,GPIO_HZ);
    #endif
    #if (ECBM_ADC_CH14_EN)
        gpio_mode(A14,GPIO_HZ);
    #endif
    ADC_POWER_ON;
}

u16 adc_read(u8 ch){
    u16 timeout_u16=4800;
    ADC_SET_CHANNELS(ch);
    ADC_MEASURE_ON;
    _nop_();
    _nop_();
    while((!(ADC_GET_IT_FLAG))&&(timeout_u16))timeout_u16--;
    ADC_CLS_IT_FLAG;
    #if (ECBM_ADC_8BIT)
        return (u16)(ADC_GET_REG_RES_H8);
    #else
        return (u16)(ADC_GET_REG_RES_HL);
    #endif
}

#if (ECBM_ADC_IT_EN)
    void adc_read_start(u8 ch){
        ADC_SET_CHANNELS(ch);
        ADC_MEASURE_ON;
        _nop_();
        _nop_();
    }
#endif

#if (ECBM_ADC_IT_EN)
    u16 adc_read_it(void){
        #if (ECBM_ADC_8BIT)
            return (u16)(ADC_GET_REG_RES_H8);
        #else
            return (u16)(ADC_GET_REG_RES_HL);
        #endif
    }
#endif

float adc_voltage(u8 ch,float vref){
    u16 jg_u16;
    jg_u16=adc_read(ch);
    #if (ECBM_ADC_8BIT)
        return (((float)(jg_u16)*vref)/256.0f);
    #else
        return (((float)(jg_u16)*vref)/(ECBM_MCU_ADC_MAX));
    #endif
}

#if (ECBM_ADC_IT_EN)
    void adc_it_start(void){
        ADC_IT_ENABLE;
    }
#endif

#if (ECBM_ADC_IT_EN)
    void adc_it_stop(void){
        ADC_IT_DISABLE;
    }
#endif

float adc_read_vref(void){
    u16 jg_u16;
    jg_u16=adc_read(15);
    if(jg_u16==0)return 0.0f;
    #if (ECBM_ADC_8BIT)
        return (adc_ch15_gxf*256.0f)/((float)jg_u16);
    #else
        return (adc_ch15_gxf)*(ECBM_MCU_ADC_MAX)/((float)jg_u16);
    #endif
}
#endif



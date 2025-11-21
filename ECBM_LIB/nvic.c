#include "ecbm_core.h"


#if (ECBM_NVIC_FUNCTION_EN)
    void nvic_set_priority(void){
        #if ((ECBM_EXTI0_EN)&&(ECBM_EXTI_LIB_EN))
            #if     (ECBM_NVIC_EXTI0_PRIORITY==0)
                EXTI0_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_EXTI0_PRIORITY==1)
                EXTI0_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_EXTI0_PRIORITY==2)
                EXTI0_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_EXTI0_PRIORITY==3)
                EXTI0_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if ((ECBM_TIMER0_IT_EN)&&(ECBM_TIMER_LIB_EN))
            #if     (ECBM_NVIC_TIMER0_PRIORITY==0)
                TIMER0_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_TIMER0_PRIORITY==1)
                TIMER0_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_TIMER0_PRIORITY==2)
                TIMER0_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_TIMER0_PRIORITY==3)
                TIMER0_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if ((ECBM_EXTI1_EN)&&(ECBM_EXTI_LIB_EN))
            #if      (ECBM_NVIC_EXTI1_PRIORITY==0)
                EXTI1_SET_IT_PRIORITY_0;
            #elif    (ECBM_NVIC_EXTI1_PRIORITY==1)
                EXTI1_SET_IT_PRIORITY_1;
            #elif    (ECBM_NVIC_EXTI1_PRIORITY==2)
                EXTI1_SET_IT_PRIORITY_2;
            #elif    (ECBM_NVIC_EXTI1_PRIORITY==3)
                EXTI1_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if ((ECBM_TIMER1_IT_EN)&&(ECBM_TIMER_LIB_EN))
            #if     (ECBM_NVIC_TIMER1_PRIORITY==0)
                TIMER1_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_TIMER1_PRIORITY==1)
                TIMER1_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_TIMER1_PRIORITY==2)
                TIMER1_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_TIMER1_PRIORITY==3)
                TIMER1_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if ((ECBM_UART1_EN)&&(ECBM_UART_LIB_EN))
            #if     (ECBM_NVIC_UART1_PRIORITY==0)
                UART1_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_UART1_PRIORITY==1)
                UART1_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_UART1_PRIORITY==2)
                UART1_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_UART1_PRIORITY==3)
                UART1_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if ((ECBM_ADC_IT_EN)&&(ECBM_ADC_LIB_EN))
            #if     (ECBM_NVIC_ADC_PRIORITY==0)
                ADC_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_ADC_PRIORITY==1)
                ADC_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_ADC_PRIORITY==2)
                ADC_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_ADC_PRIORITY==3)
                ADC_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if ((ECBM_POWER_RST_CFG_EN)&&(ECBM_POWER_LIB_EN))
            #if     (ECBM_NVIC_LVD_PRIORITY==0)
                LVD_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_LVD_PRIORITY==1)
                LVD_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_LVD_PRIORITY==2)
                LVD_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_LVD_PRIORITY==3)
                LVD_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if (ECBM_PCA_LIB_EN)
            #if     (ECBM_NVIC_PCA_PRIORITY==0)

            #elif   (ECBM_NVIC_PCA_PRIORITY==1)

            #elif   (ECBM_NVIC_PCA_PRIORITY==2)

            #elif   (ECBM_NVIC_PCA_PRIORITY==3)

            #endif
        #endif

        #if ((ECBM_UART2_EN)&&(ECBM_UART_LIB_EN))
            #if     (ECBM_NVIC_UART2_PRIORITY==0)
                UART2_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_UART2_PRIORITY==1)
                UART2_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_UART2_PRIORITY==2)
                UART2_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_UART2_PRIORITY==3)
                UART2_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if ((ECBM_SPI_IT_EN)&&(ECBM_SPI_LIB_EN))
            #if     (ECBM_NVIC_SPI_PRIORITY==0)
                SPI_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_SPI_PRIORITY==1)
                SPI_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_SPI_PRIORITY==2)
                SPI_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_SPI_PRIORITY==3)
                SPI_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if ((ECBM_EXTI4_EN)&&(ECBM_EXTI_LIB_EN))
            #if     (ECBM_NVIC_EXTI4_PRIORITY==0)
                EXTI4_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_EXTI4_PRIORITY==1)
                EXTI4_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_EXTI4_PRIORITY==2)
                EXTI4_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_EXTI4_PRIORITY==3)
                EXTI4_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if ((ECBM_UART3_EN)&&(ECBM_UART_LIB_EN))
            #if     (ECBM_NVIC_UART3_PRIORITY==0)
                UART3_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_UART3_PRIORITY==1)
                UART3_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_UART3_PRIORITY==2)
                UART3_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_UART3_PRIORITY==3)
                UART3_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if ((ECBM_UART4_EN)&&(ECBM_UART_LIB_EN))
            #if     (ECBM_NVIC_UART4_PRIORITY==0)
                UART4_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_UART4_PRIORITY==1)
                UART4_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_UART4_PRIORITY==2)
                UART4_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_UART4_PRIORITY==3)
                UART4_SET_IT_PRIORITY_3;
            #endif
        #endif

        #if ((ECBM_CMP_CMPCR1&0x30)&&(ECBM_CMP_LIB_EN))
            #if     (ECBM_NVIC_CMP_PRIORITY==0)
                CMP_SET_IT_PRIORITY_0;
            #elif   (ECBM_NVIC_CMP_PRIORITY==1)
                CMP_SET_IT_PRIORITY_1;
            #elif   (ECBM_NVIC_CMP_PRIORITY==2)
                CMP_SET_IT_PRIORITY_2;
            #elif   (ECBM_NVIC_CMP_PRIORITY==3)
                CMP_SET_IT_PRIORITY_3;
            #endif
        #endif
    }
#endif

#if (ECBM_EXTI_LIB_EN)
    #if (ECBM_EXTI0_EN)
        void nvic_exti0_function(void) interrupt (0) {
            exti0_it_callback();
        }
    #endif
    #if (ECBM_EXTI1_EN)
        void nvic_exti1_function(void) interrupt (2) {
            exti1_it_callback();
        }
    #endif
    #if (ECBM_EXTI2_EN)
        void nvic_exti2_function(void) interrupt (10) {
            exti2_it_callback();
        }
    #endif
    #if (ECBM_EXTI3_EN)
        void nvic_exti3_function(void) interrupt (11) {
            exti3_it_callback();
        }
    #endif
    #if (ECBM_EXTI4_EN)
        void nvic_exti4_function(void) interrupt (16) {
            exti4_it_callback();
        }
    #endif
#endif

extern void beep_run(void);
#if ((ECBM_TIMER_LIB_EN)||(ECBM_10MS_EN))
    #if (((ECBM_TIMER0_EN)&&(ECBM_TIMER0_IT_EN))||(ECBM_10MS_TIMER==0))
        void nvic_timer0_function(void) interrupt (1) {
            #if ((ECBM_TIMER0_EN)&&(ECBM_TIMER0_IT_EN))
                timer0_it_callback();
            #endif
            #if ((ECBM_10MS_EN)&&(ECBM_10MS_TIMER==0)&&(ECBM_STREAM_LIB_EN))
                ecbm_stream_timer_run();
            #endif
            #if ((ECBM_10MS_EN)&&(ECBM_10MS_TIMER==0)&&(ECBM_BEEP_EN))
                beep_run();
            #endif
        }
    #endif
    #if (((ECBM_TIMER1_EN)&&(ECBM_TIMER1_IT_EN))||(ECBM_10MS_TIMER==1))
        void nvic_timer1_function(void) interrupt (3) {
            #if ((ECBM_TIMER1_EN)&&(ECBM_TIMER1_IT_EN))
                timer1_it_callback();
            #endif
            #if ((ECBM_10MS_EN)&&(ECBM_10MS_TIMER==1)&&(ECBM_STREAM_LIB_EN))
                ecbm_stream_timer_run();
            #endif
            #if ((ECBM_10MS_EN)&&(ECBM_10MS_TIMER==1)&&(ECBM_BEEP_EN))
                beep_run();
            #endif
        }
    #endif
    #if (((ECBM_TIMER2_EN)&&(ECBM_TIMER2_IT_EN))||(ECBM_10MS_TIMER==2))
        void nvic_timer2_function(void) interrupt (12) {
            #if ((ECBM_TIMER2_EN)&&(ECBM_TIMER2_IT_EN))
                timer2_it_callback();
            #endif
            #if ((ECBM_10MS_EN)&&(ECBM_10MS_TIMER==2)&&(ECBM_STREAM_LIB_EN))
                ecbm_stream_timer_run();
            #endif
            #if ((ECBM_10MS_EN)&&(ECBM_10MS_TIMER==2)&&(ECBM_BEEP_EN))
                beep_run();
            #endif
        }
    #endif
    #if (((ECBM_TIMER3_EN)&&(ECBM_TIMER3_IT_EN))||(ECBM_10MS_TIMER==3))
        void nvic_timer3_function(void) interrupt (19) {
            #if ((ECBM_TIMER3_EN)&&(ECBM_TIMER3_IT_EN))
                timer3_it_callback();
            #endif
            #if ((ECBM_10MS_EN)&&(ECBM_10MS_TIMER==3)&&(ECBM_STREAM_LIB_EN))
                ecbm_stream_timer_run();
            #endif
            #if ((ECBM_10MS_EN)&&(ECBM_10MS_TIMER==3)&&(ECBM_BEEP_EN))
                beep_run();
            #endif
        }
    #endif
    #if (((ECBM_TIMER4_EN)&&(ECBM_TIMER4_IT_EN))||(ECBM_10MS_TIMER==4))
        void nvic_timer4_function(void) interrupt (20) {
            #if ((ECBM_TIMER4_EN)&&(ECBM_TIMER4_IT_EN))
                timer4_it_callback();
            #endif
            #if ((ECBM_10MS_EN)&&(ECBM_10MS_TIMER==4)&&(ECBM_STREAM_LIB_EN))
                ecbm_stream_timer_run();
            #endif
            #if ((ECBM_10MS_EN)&&(ECBM_10MS_TIMER==4)&&(ECBM_BEEP_EN))
                beep_run();
            #endif
        }
    #endif
#endif

#if (ECBM_UART_LIB_EN)
    #if (ECBM_UART1_EN)
        extern bit uart1_busy_gb;
        extern void uart1_tx_trig(void);
        extern void uart1_tx_end(void);
        void nvic_uart1_function(void) interrupt (4) {
            if(UART1_GET_RI_FLAG){
                UART1_CLR_RI_FLAG;
                #if (ECBM_UART1_RECEIVE_CALLBACK_EN)
                    uart1_receive_callback();
                #endif
                #if (ECBM_AUTO_DOWNLOAD_EN)
                    system_uart_reset();
                #endif
                #if ((ECBM_10MS_EN)&&(ECBM_STREAM_LIB_EN)&&(ECBM_STREAM_CH1_EN))
                    ecbm_stream_ch1_time_gu8=0;
                    ecbm_stream_ch1_status_gu8=ECBM_STREAM_TIME_EN;
                    ecbm_stream_ch1_buf_gxu8a[ecbm_stream_ch1_point_gu8]=UART1_GET_REG_SBUF;
                    ecbm_stream_ch1_count_gu8++;
                    ecbm_stream_ch1_point_gu8++;
                    if(ecbm_stream_ch1_point_gu8>=ECBM_STREAM_CH1_SZIE){
                        ecbm_stream_ch1_point_gu8=0;
                    }
                #endif
            }
            if(UART1_GET_TI_FLAG){
                UART1_CLR_TI_FLAG;
                #if (ECBM_UART_TX_MODE)
                    if(uart1_tx_buf_read_point!=uart1_tx_buf_write_point){
                        uart1_tx_trig();
                    }else{
                        uart1_tx_end();
                    }
                #else
                    uart1_busy_gb=0;
                #endif
                #if (ECBM_UART1_SEND_CALLBACK_EN)
                    uart1_send_callback();
                #endif
            }
        }
    #endif
    #if (ECBM_UART2_EN)
        extern bit uart2_busy_gb;
        extern void uart2_tx_trig(void);
        extern void uart2_tx_end(void);
        void nvic_uart2_function(void) interrupt (8) {
            if(UART2_GET_RI_FLAG){
                UART2_CLR_RI_FLAG;
                #if (ECBM_UART2_RECEIVE_CALLBACK_EN)
                    uart2_receive_callback();
                #endif
                #if ((ECBM_10MS_EN)&&(ECBM_STREAM_LIB_EN)&&(ECBM_STREAM_CH2_EN))
                    ecbm_stream_ch2_time_gu8=0;
                    ecbm_stream_ch2_status_gu8=ECBM_STREAM_TIME_EN;
                    ecbm_stream_ch2_buf_gxu8a[ecbm_stream_ch2_point_gu8]=UART2_GET_REG_S2BUF;
                    ecbm_stream_ch2_count_gu8++;
                    ecbm_stream_ch2_point_gu8++;
                    if(ecbm_stream_ch2_point_gu8>=ECBM_STREAM_CH2_SZIE){
                        ecbm_stream_ch2_point_gu8=0;
                    }
                #endif
            }
            if(UART2_GET_TI_FLAG){
                UART2_CLR_TI_FLAG;
                #if (ECBM_UART_TX_MODE)
                    if(uart2_tx_buf_read_point!=uart2_tx_buf_write_point){
                        uart2_tx_trig();
                    }else{
                        uart2_tx_end();
                    }
                #else
                    uart2_busy_gb=0;
                #endif
                #if (ECBM_UART2_SEND_CALLBACK_EN)
                    uart2_send_callback();
                #endif
            }
        }
    #endif
    #if (ECBM_UART3_EN)
        extern bit uart3_busy_gb;
        extern void uart3_tx_trig(void);
        extern void uart3_tx_end(void);
        void nvic_uart3_function(void) interrupt (17) {
            if(UART3_GET_RI_FLAG){
                UART3_CLR_RI_FLAG;
                #if (ECBM_UART3_RECEIVE_CALLBACK_EN)
                    uart3_receive_callback();
                #endif
                #if ((ECBM_10MS_EN)&&(ECBM_STREAM_LIB_EN)&&(ECBM_STREAM_CH3_EN))
                    ecbm_stream_ch3_time_gu8=0;
                    ecbm_stream_ch3_status_gu8=ECBM_STREAM_TIME_EN;
                    ecbm_stream_ch3_buf_gxu8a[ecbm_stream_ch3_point_gu8]=UART3_GET_REG_S3BUF;
                    ecbm_stream_ch3_count_gu8++;
                    ecbm_stream_ch3_point_gu8++;
                    if(ecbm_stream_ch3_point_gu8>=ECBM_STREAM_CH3_SZIE){
                        ecbm_stream_ch3_point_gu8=0;
                    }
                #endif
            }
            if(UART3_GET_TI_FLAG){
                UART3_CLR_TI_FLAG;
                #if (ECBM_UART_TX_MODE)
                    if(uart3_tx_buf_read_point!=uart3_tx_buf_write_point){
                        uart3_tx_trig();
                    }else{
                        uart3_tx_end();
                    }
                #else
                    uart3_busy_gb=0;
                #endif
                #if (ECBM_UART3_SEND_CALLBACK_EN)
                    uart3_send_callback();
                #endif
            }
        }
    #endif
    #if (ECBM_UART4_EN)
        extern bit uart4_busy_gb;
        extern void uart4_tx_trig(void);
        extern void uart4_tx_end(void);
        void nvic_uart4_function(void) interrupt (18) {
            if(UART4_GET_RI_FLAG){
                UART4_CLR_RI_FLAG;
                #if (ECBM_UART4_RECEIVE_CALLBACK_EN)
                uart4_receive_callback();
                #endif
                #if ((ECBM_10MS_EN)&&(ECBM_STREAM_LIB_EN)&&(ECBM_STREAM_CH4_EN))
                    ecbm_stream_ch4_time_gu8=0;
                    ecbm_stream_ch4_status_gu8=ECBM_STREAM_TIME_EN;
                    ecbm_stream_ch4_buf_gxu8a[ecbm_stream_ch4_point_gu8]=UART4_GET_REG_S4BUF;
                    ecbm_stream_ch4_count_gu8++;
                    ecbm_stream_ch4_point_gu8++;
                    if(ecbm_stream_ch4_point_gu8>=ECBM_STREAM_CH4_SZIE){
                        ecbm_stream_ch4_point_gu8=0;
                    }
                #endif
            }
            if(UART4_GET_TI_FLAG){
                UART4_CLR_TI_FLAG;
                #if (ECBM_UART_TX_MODE)
                    if(uart4_tx_buf_read_point!=uart4_tx_buf_write_point){
                        uart4_tx_trig();
                    }else{
                        uart4_tx_end();
                    }
                #else
                    uart4_busy_gb=0;
                #endif
                #if (ECBM_UART4_SEND_CALLBACK_EN)
                    uart4_send_callback();
                #endif
            }
        }
    #endif
#endif

#if ((ECBM_ADC_LIB_EN)&&(ECBM_ADC_IT_EN))
    void nvic_adc_function(void) interrupt (5) {
        ADC_CLS_IT_FLAG;
        adc_it_callback();
    }
#endif

#if ((ECBM_POWER_LIB_EN)&&(ECBM_POWER_RST_CFG_EN))
    void nvic_lvd_function(void) interrupt (6) {
        LVD_CLS_IT_FLAG;
        lvd_it_callback();
    }
#endif

#if (ECBM_PCA_LIB_EN)
    void nvic_pca_function(void) interrupt (7) {
        if(PCA_GET_IT_FLAG){
            PCA_CLS_IT_FLAG;
            #if (ECBM_PCA_CALLBACK_EN)
                pca_timer_callback();
            #endif
        }
        #if (ECBM_PCA0_EN)
            if(PCA0_GET_IT_FLAG){
                PCA0_CLS_IT_FLAG;
                #if (ECBM_PCA0_TIMER_AUTO_EN)
                    if(pca_mode_0>=6){
                        PCA_SET_REG_CCAP0HL(pca_timer_count_0);
                        pca_timer_count_0+=pca_timer_add_0;
                    }
                #endif
                #if (ECBM_PCA0_CALLBACK_EN)
                    pca0_callback();
                #endif
            }
        #endif
        #if (ECBM_PCA1_EN)
            if(PCA1_GET_IT_FLAG){
                PCA1_CLS_IT_FLAG;
                #if (ECBM_PCA1_TIMER_AUTO_EN)
                    if(pca_mode_1>=6){
                        PCA_SET_REG_CCAP1HL(pca_timer_count_1);
                        pca_timer_count_1+=pca_timer_add_1;
                    }
                #endif
                #if (ECBM_PCA1_CALLBACK_EN)
                    pca1_callback();
                #endif
            }
        #endif
        #if (ECBM_PCA2_EN)
            if(PCA2_GET_IT_FLAG){
                PCA2_CLS_IT_FLAG;
                #if (ECBM_PCA2_TIMER_AUTO_EN)
                    if(pca_mode_2>=6){
                        PCA_SET_REG_CCAP2HL(pca_timer_count_2);
                        pca_timer_count_2+=pca_timer_add_2;
                    }
                #endif
                #if (ECBM_PCA2_CALLBACK_EN)
                    pca2_callback();
                #endif
            }
        #endif
        #if (ECBM_PCA3_EN)
            if(PCA3_GET_IT_FLAG){
                PCA3_CLS_IT_FLAG;
                #if (ECBM_PCA3_TIMER_AUTO_EN)
                    if(pca_mode_3>=6){
                        PCA_SET_REG_CCAP3HL(pca_timer_count_3);
                        pca_timer_count_3+=pca_timer_add_3;
                    }
                #endif
                #if (ECBM_PCA3_CALLBACK_EN)
                    pca3_callback();
                #endif
            }
        #endif
    }
#endif

#if ((ECBM_SPI_LIB_EN)&&(ECBM_SPI_IT_EN))
    void nvic_spi_function(void) interrupt (9) {
        spi_it_callback();
    }
#endif

#if ((ECBM_CMP_LIB_EN)&&(ECBM_CMP_CMPCR1&0x30))
    void nvic_cmp_function(void) interrupt (21) {

    }
#endif

#if (ECBM_IIC_LIB_EN)
    extern bit iic_master_busy_gb;
    extern bit eiicp_trig_gb;
    extern u8  eiicp_data_count_gu8;
    extern u8  eiicp_data_buf_gu8a[ECBM_IIC_BUF_MAX];
    void nvic_iic_function(void) interrupt (24) {
    if(IIC_GET_M_IT_FLAG){
        IIC_CLS_M_IT_FLAG;
        iic_master_busy_gb=0;
    }
    if(IIC_GET_S_STA_FLAG){
        IIC_CLS_S_STA_FLAG;
        eiicp_data_count_gu8=0;
        eiicp_trig_gb=0;
    }
    if(IIC_GET_S_RX_FLAG){
        IIC_CLS_S_RX_FLAG;
        eiicp_data_buf_gu8a[eiicp_data_count_gu8++]=IIC_GET_REG_DATA;
    }
    if(IIC_GET_S_STO_FLAG){
        IIC_CLS_S_STO_FLAG;
        eiicp_trig_gb=1;
    }
}
#endif







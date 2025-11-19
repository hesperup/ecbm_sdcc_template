#include "ecbm_core.h"
#if (ECBM_EDS_LIB_EN)


u8 eds_check(u16 addr){
    u8 dat_u8,_dat_u8;
    dat_u8=eeprom_read(addr+0);
    if(dat_u8!='E')return EDS_ERR_NULL;
    dat_u8=eeprom_read(addr+1);
    if(dat_u8!='D')return EDS_ERR_NULL;
    dat_u8=eeprom_read(addr+2);
    if(dat_u8!='S')return EDS_ERR_NULL;
    dat_u8 =eeprom_read(addr+3);
    _dat_u8=eeprom_read(addr+4);
    if((dat_u8==(~_dat_u8))&&(dat_u8==(u8)(addr/512))){
        return EDS_OK;
    }
    return EDS_ERR_ID;
}

void eds_erase(u8 sector_start,u8 sector_szie){
    u8 i_u8;
    for(i_u8=0;i_u8<sector_szie;i_u8++){
        eeprom_erase((u16)(sector_start+i_u8)*512);
    }
}

u8 eds_init(u8 sector_start,u8 sector_szie,u16 pack_len){
    u16 addr_u16;
    if(sector_start>128)return EDS_ERR_SECTOR;
    if(sector_szie >128)return EDS_ERR_SECTOR;
    if(sector_szie ==0 )return EDS_ERR_SECTOR;
    addr_u16=sector_start*512;
    if(eds_check(addr_u16)!=EDS_OK){
        eds_erase(sector_start,sector_szie);
        eeprom_write(addr_u16+0,'E');
        eeprom_write(addr_u16+1,'D');
        eeprom_write(addr_u16+2,'S');
        eeprom_write(addr_u16+3, sector_start);
        eeprom_write(addr_u16+4,~sector_start);
        eeprom_write(addr_u16+5,sector_szie);
        eeprom_write(addr_u16+6,(u8)(pack_len>>8));
        eeprom_write(addr_u16+7,(u8)(pack_len   ));
        return EDS_DATA_VOID;
    }
    return EDS_OK;
}

u8 eds_compare(u16 addr,u8 * buf,u16 len){
    u16 i_u16,data_sum_u16,read_addr_u16,data_sum_check_u16;
    u8  res_u8,err_count_u8;
    data_sum_u16=0;
    err_count_u8=0;
    read_addr_u16=addr;
    for(i_u16=0;i_u16<len;i_u16++){
        res_u8=eeprom_read(read_addr_u16++);
        if(buf[i_u16]!=res_u8){
            err_count_u8++;
        }
        data_sum_u16+=res_u8;
    }
    data_sum_check_u16 =(u16)(eeprom_read(read_addr_u16++));
    data_sum_check_u16|=(u16)(eeprom_read(read_addr_u16)<<8);
    if(err_count_u8){
        return EDS_ERR_DATA;
    }else{
        if(data_sum_u16!=data_sum_check_u16){
            return EDS_ERR_SUM;
        }else{
            return EDS_OK;
        }
    }
}

u16 eds_mark_find(u16 addr){
    u8 i_u8,j_u8,k_u8,res_u8;
    u16 i_u16,count_u16;
    i_u16=addr+8;
    count_u16=0;
    for(i_u8=0;i_u8<56;i_u8++){
        res_u8=eeprom_read(i_u16++);
        k_u8=res_u8;
        for(j_u8=0;j_u8<8;j_u8++){
            if((k_u8&0x80)==0)count_u16++;
            k_u8<<=1;
        }
        if(res_u8!=0x00)break;
    }
    return count_u16;
}

u8 eds_write(u8 sector_start,u8 * buf){
    u16 start_addr_u16;
    u16 limit_addr_u16;
    u16 data_len_u16;
    u16 count_u16;
    u16 write_addr_u16;
    u16 mark_addr_u16;
    u16 data_sum_u16;
    u8  read_buf_u8a[8];
    u8  res_u8,i_u8;
    u8  mark_data_u8;
    u8 code list2list[8]={0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00};
    start_addr_u16=(u16)(sector_start)*512;
    res_u8=eds_check(start_addr_u16);
    if(res_u8!=EDS_OK){
        return res_u8;
    }
    for(i_u8=0;i_u8<8;i_u8++){
        read_buf_u8a[i_u8]=eeprom_read(start_addr_u16+(u16)(i_u8));
    }
    limit_addr_u16=start_addr_u16+(u16)(read_buf_u8a[5])*512;
    data_len_u16=(u16)(read_buf_u8a[6])*256+(u16)(read_buf_u8a[7]);

    count_u16    =eds_mark_find(start_addr_u16);
    mark_addr_u16=start_addr_u16+8+(count_u16/8);
    mark_data_u8 =list2list[count_u16%8];

    if(count_u16){
        if(eds_compare(start_addr_u16+64+(count_u16-1)*(data_len_u16+2),buf,data_len_u16)==EDS_OK){
            return EDS_DATA_EXISTS;
        }
    }
    write_addr_u16=start_addr_u16+64+count_u16*(data_len_u16+2);
    if((write_addr_u16>=limit_addr_u16)||((limit_addr_u16-write_addr_u16)<data_len_u16)){

        eds_erase(read_buf_u8a[3],read_buf_u8a[5]);
        for(i_u8=0;i_u8<8;i_u8++){
            eeprom_write(start_addr_u16+(u16)(i_u8),read_buf_u8a[i_u8]);
        }
        eeprom_write(start_addr_u16+8,0x7F);
        write_addr_u16=start_addr_u16+64;
    }else{
        eeprom_write(mark_addr_u16,mark_data_u8);
    }

    data_sum_u16=0;
    for(count_u16=0;count_u16<data_len_u16;count_u16++){
        eeprom_write(write_addr_u16+count_u16,buf[count_u16]);
        data_sum_u16+=buf[count_u16];
    }
    eeprom_write(write_addr_u16+count_u16+0,(u8)(data_sum_u16));
    eeprom_write(write_addr_u16+count_u16+1,(u8)(data_sum_u16>>8));

    return eds_compare(write_addr_u16,buf,data_len_u16);
}

u8 eds_read(u8 sector_start,u8 * buf){
    u16 start_addr_u16;
    u16 limit_addr_u16;
    u16 data_len_u16;
    u16 count_u16;
    u16 read_addr_u16;
    u16 data_sum_u16;
    u16 data_sum_check_u16;
    u16 i_u16;
    u8  read_buf_u8a[8];
    u8  res_u8,i_u8;
    start_addr_u16=(u16)(sector_start)*512;
    res_u8=eds_check(start_addr_u16);
    if(res_u8!=EDS_OK){
        return res_u8;
    }
    for(i_u8=0;i_u8<8;i_u8++){
        read_buf_u8a[i_u8]=eeprom_read(start_addr_u16+(u16)(i_u8));
    }
    limit_addr_u16=start_addr_u16+(u16)(read_buf_u8a[5])*512;
    data_len_u16  =(u16)(read_buf_u8a[6])*256+(u16)(read_buf_u8a[7]);
    count_u16     =eds_mark_find(start_addr_u16);
    for(i_u8=0;i_u8<EDS_ERROR_SUM_HANDLING;i_u8++){
        if(count_u16==0)return EDS_DATA_VOID;
        read_addr_u16=start_addr_u16+64+(count_u16-1)*(data_len_u16+2);
        data_sum_u16=0;
        for(i_u16=0;i_u16<data_len_u16;i_u16++){
            buf[i_u16]=eeprom_read(read_addr_u16++);
            data_sum_u16+=buf[i_u16];
        }
        data_sum_check_u16 =(u16)(eeprom_read(read_addr_u16++));
        data_sum_check_u16|=(u16)(eeprom_read(read_addr_u16)<<8);
        if(data_sum_u16==data_sum_check_u16){
            if(i_u8==0){
                return EDS_OK;
            }else{
                return EDS_WAR_DATA;
            }
        }
        count_u16--;
    }
    return EDS_ERR_SUM;
}
#endif


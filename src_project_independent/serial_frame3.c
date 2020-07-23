/**
  ******************************************************************************
  * @file    serial_frame3.h
  * @author  Милованов Александр
  * @version V3
  * @date    26 матра 2018
  * @brief   кодирование и декодирование блока двоичных данный в текстовую форму
  ******************************************************************************
  */
#include "crc_16.h"
#include "serial_frame3.h"
/*===========================================================================*/
uint8_t sf3_error;
uint8_t sf3_encode_add_nl = 1;
/*======================================================================================*/
void sf3_decode( uint8_t * destination_data , uint8_t * source_string ,int source_string_size )
{
    uint8_t value_hi;
    uint8_t value_lo;
    
    sf3_error=0;
    if(source_string_size&0x01)sf3_error|=0x1;
    source_string_size>>=1;
    
    while(source_string_size){
        source_string_size--;

        value_hi= *source_string-'0';
        if(value_hi>9)value_hi-=7;
        if(value_hi>0xf)sf3_error|=0x2;
        source_string++;
        
        value_lo= *source_string-'0';
        if(value_lo>9)value_lo-=7;
        if(value_lo>0xf)sf3_error|=0x4;
        source_string++;

        *destination_data= (value_hi<<4) + value_lo;
        destination_data++;
    }
}
/*======================================================================================*/
//Возврящает индекс маркера конца строки
static int sf3_find_frame_end( uint8_t * source_string ,int source_string_size )
{
    int i=0;
    for(i=0;i<source_string_size;i++)if(source_string[i]==sf3_end_symbol)return i;
    return -1;
}
/*======================================================================================*/
void sf3_decode_packet( uint8_t * destination_data , uint8_t * source_string ,int source_string_size )
{
    uint16_t crc;
    int string_packet_len;
    int data_size;
    
    sf3_error=0;
    if(source_string[0]!=sf3_start_symbol){
        sf3_error=1;
        return;
    }
    string_packet_len=sf3_find_frame_end(source_string,source_string_size);
    if(string_packet_len<5){
        sf3_error=2;
        return;
    }
    source_string++;
    
    data_size=(string_packet_len-5)/2;
    sf3_decode(destination_data,source_string,string_packet_len-5);
    source_string+=string_packet_len-5;

    sf3_decode((uint8_t*)&crc,source_string,4);
    if(crc!=CRC16Update(CRC16Start,destination_data,data_size))sf3_error=4;
}
/*======================================================================================*/

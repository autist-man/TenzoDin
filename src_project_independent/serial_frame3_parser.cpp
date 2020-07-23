#include "serial_frame3_parser.h"
/*==================================================================================*/
TSerialFrame3Parser::TSerialFrame3Parser(QObject *parent)
    :QObject(parent)
{

    rcv_timeout = 1;

    readDeviceTimer = new QTimer(this);
    connect(readDeviceTimer,SIGNAL(timeout()),this,SLOT(slSerialDevicePolling()));

    statusTimeoutTimer = new QTimer(this);
    connect(statusTimeoutTimer,SIGNAL(timeout()),this,SLOT(slSerialDeviceTimeout()));

    rc_frame_last_write_position = 0;

    num_frames_received = 0;
    num_frames_received_valid = 0;
    num_frames_received_dropped = 0;

    setNewDevice(0);
}
/*==================================================================================*/
TSerialFrame3Parser::~TSerialFrame3Parser()
{
}
/*==================================================================================*/
void TSerialFrame3Parser::setNewDevice(QIODevice *device)
{
    if(device){
        readDeviceTimer->start(SF3P_io_period);
        statusTimeoutTimer->start(SF3P_timeout);
    }else{
        readDeviceTimer->stop();
        statusTimeoutTimer->stop();
    }
    deviceConnection = device;
    emit connectionUpdated();
}
/*==================================================================================*/
void TSerialFrame3Parser::processReceivedFrame(void *frame)
{
    (void)frame;
}
/*==================================================================================*/
void TSerialFrame3Parser::slSerialDevicePolling()
{
    char rc_char;
    if(!deviceConnection){
        return;
    }
    if(!deviceConnection->isOpen()){
        return;
    }
    //Получаем данные из порта
    int readed = deviceConnection->read(rc_read_device_buffer, SF3P_buffer_size);
    //Обработка полученных данных
    if (readed < 1)return;
    for(int i = 0; i<readed; i++){
        rc_char=rc_read_device_buffer[i];

        if(rc_char==sf3_start_symbol)rc_frame_last_write_position=0;
        if(rc_frame_last_write_position>=SF3P_max_string_size)rc_frame_last_write_position=SF3P_max_string_size-1;
        rc_serial_frame[rc_frame_last_write_position]=rc_char;
        rc_frame_last_write_position++;

        if(rc_char == sf3_end_symbol){
            num_frames_received++;
            rc_serial_frame[rc_frame_last_write_position]=0;
            sf3_decode_packet((u_int8_t*)&rc_data,(u_int8_t*)rc_serial_frame,rc_frame_last_write_position);
            if(sf3_error==0){
                num_frames_received_valid++;
                if(rcv_timeout){
                    rcv_timeout=0;
                    emit  connectionUpdated();
                }
                statusTimeoutTimer->start(SF3P_timeout);
                processReceivedFrame(&rc_data);
            }else{
                num_frames_received_dropped++;
            }
        }
    }
}
/*==================================================================================*/
void TSerialFrame3Parser::slSerialDeviceTimeout()
{
    rcv_timeout = 1;
    statusTimeoutTimer->stop();
    emit connectionUpdated();
}
/*==================================================================================*/

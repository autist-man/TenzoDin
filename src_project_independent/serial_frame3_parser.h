#ifndef __SERIAL_FRAME3_PARSER_H_
#define __SERIAL_FRAME3_PARSER_H_

#include <QtGui>
#include <QFile>
#include <QTimer>
/*=======================================================================*/
//Объект-считывает данные с порта, отправляет
//на декодирование и проверку контрольной суммы
//данных
/*=======================================================================*/
#include "crc_16.h"
#include "serial_frame3.h"

#define SF3P_buffer_size 10000 // Размер буфера на 10000 символов
#define SF3P_timeout 1000 // мс
#define SF3P_io_period 100 // мс
#define SF3P_max_structure_size 200
#define SF3P_max_string_size sf3_calc_packet_size(SF3P_max_structure_size)

class TSerialFrame3Parser : public QObject
{
    Q_OBJECT
public:

    TSerialFrame3Parser(QObject *parent = 0);
    ~TSerialFrame3Parser();
    //Назначить устройство(порт) откуда считывать данные
    //или удалить уствройство
    void setNewDevice(QIODevice *device);
    //Функция принимающая пакет данных
    //переопределена в контроллере
    virtual void processReceivedFrame(void *frame);

    //Принимаемая информация
    //если не ноль - то информация неактуальна
    int rcv_timeout;

signals:
    //При изменении состояния подключения
    void connectionUpdated();
public slots:
    //Вызывается по таймеру - обмен данными с контроллером
    void slSerialDevicePolling();
    //Вызывается таймером при истечении времени ожидания.
    void slSerialDeviceTimeout();
public:
    //Таймер чтения из потока = 0,3 с
    QTimer *readDeviceTimer;
    //Таймер таймаута
    QTimer *statusTimeoutTimer;
    QPointer<QIODevice> deviceConnection; // указатель на объект устройства связи с машиной. уничтожается не в этом классе.

// буферы приёма информации из машины и посылки инфы в машину
    char rc_read_device_buffer[SF3P_buffer_size];
    int rc_frame_last_write_position;
    char rc_serial_frame[SF3P_max_string_size];
    char rc_data[SF3P_max_structure_size];

    char tx_serial_frame[SF3P_max_string_size];

    unsigned int num_frames_received;
    unsigned int num_frames_received_valid;
    unsigned int num_frames_received_dropped;
};
/*=======================================================================*/
#endif

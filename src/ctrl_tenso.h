#ifndef CTRL_TENSO_H
#define CTRL_TENSO_H

#include "data_storage.h"
#include "serial_frame3_parser.h"
#include "calibration_structure.h"
#include "tenso_sensor_structure.h"
#include "fir_filter.h"
/*=======================================================================*/
/*
Объект контроллер - представляет, собирает и обрабатывает данные,
отправляет их в хранилище данных.
*/
/*=======================================================================*/
class TControlTenso : public TSerialFrame3Parser
{
    Q_OBJECT
public:
    //Перечисление всех данных в хранилище данных
    enum SENSOR_STORAGE_INDEX{
        SSI_time_tick_ms=0,

        SSI_tenso_sensor_channel_0,
        SSI_tenso_sensor_channel_1,
        SSI_tenso_sensor_channel_2,
        SSI_tenso_sensor_channel_3,

        SSI_tenso_sensor_filter_channel_0,
        SSI_tenso_sensor_filter_channel_1,
        SSI_tenso_sensor_filter_channel_2,
        SSI_tenso_sensor_filter_channel_3,

        SSI_converted_tenso_sensor_channel_0,
        SSI_converted_tenso_sensor_channel_1,
        SSI_converted_tenso_sensor_channel_2,
        SSI_converted_tenso_sensor_channel_3,

        SSI_converted_tenso_sensor_filter_channel_0,
        SSI_converted_tenso_sensor_filter_channel_1,
        SSI_converted_tenso_sensor_filter_channel_2,
        SSI_converted_tenso_sensor_filter_channel_3,

        SSI_NUM_INDEXES
    };

    //Перечисление каналов АЦП
    TControlTenso(QObject *parent = 0);
    ~TControlTenso();

    //Назначить файл сохранения настроек
    void assignSettings(QSettings *s,const QString &group_name );
    //Функция принимающая пакет данных
    virtual void processReceivedFrame(void *frame);

    //Флаг активности записи данных в хранилище
    int dataStorageActive;

    //Массив для временногохранения значений
    //из пакет данных со значениями АЦП
    double dataStorageLastDataFrame[SSI_NUM_INDEXES];

    //Хранилище данных
    TDataStorage *dataStorage;

    //Объекты для калибровки значений АЦП
    TCalibrationForLinearConverter *calibration_tenso;
    FirFilter *firFilter;

private:
    //Структура данных приходящих с АЦП
    TTensoSensorStateSendToMachine_V3 *m_frame;

    //Указательна файл настроек
    QPointer<QSettings> settings;
    //Название группы настроек в фале
    QString iniGroupName;

signals:
    //Сигнал прихода новых данных
    void sgNewDiagramData();

public slots:
    //Очистка хранилища данных
    void slClearDiagramData();
    //Сохранение настроек
    void slSaveSettings();
    //Загрузка настроек
    void slLoadSettings();
    //Загрузка данных из файла
    void slLoadTextData();
    //Сохранение данных в файл
    void slSaveTextData();
};
#endif // TSENSORCONTROL_H

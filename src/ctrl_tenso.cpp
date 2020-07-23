#include "ctrl_tenso.h"
/*==================================================================================*/
TControlTenso::TControlTenso(QObject *parent) :
    TSerialFrame3Parser(parent)
{
    calibration_tenso = new TCalibrationForLinearConverter[NUMBER_CHANNELS_ADC];
    firFilter = new FirFilter[NUMBER_CHANNELS_ADC];

    dataStorage = new TDataStorage(SSI_NUM_INDEXES ,200000000, this);

    dataStorage->setArrayName(SSI_time_tick_ms,"time_tick_ms");

    dataStorage->setArrayName(SSI_tenso_sensor_channel_0,"Pz_ADC_ch_1");
    dataStorage->setArrayName(SSI_tenso_sensor_channel_1,"Py_ADC_ch_2");
    dataStorage->setArrayName(SSI_tenso_sensor_channel_2,"Px_ADC_ch_3");
    dataStorage->setArrayName(SSI_tenso_sensor_channel_3,"M_ADC_ch_4");

    dataStorage->setArrayName(SSI_converted_tenso_sensor_channel_0,"Pz_force_ch_1");
    dataStorage->setArrayName(SSI_converted_tenso_sensor_channel_1,"Py_force_ch_2");
    dataStorage->setArrayName(SSI_converted_tenso_sensor_channel_2,"Px_force_ch_3");
    dataStorage->setArrayName(SSI_converted_tenso_sensor_channel_3,"M_force_ch_4");

    dataStorage->setArrayName(SSI_tenso_sensor_filter_channel_0,"Pz_ADC_filter_ch_1");
    dataStorage->setArrayName(SSI_tenso_sensor_filter_channel_1,"Py_ADC_filter_ch_2");
    dataStorage->setArrayName(SSI_tenso_sensor_filter_channel_2,"Px_ADC_filter_ch_3");
    dataStorage->setArrayName(SSI_tenso_sensor_filter_channel_3,"M_ADC_filter_ch_4");

    dataStorage->setArrayName(SSI_converted_tenso_sensor_filter_channel_0,
                                                                    "Pz_force_filter_ch_1");
    dataStorage->setArrayName(SSI_converted_tenso_sensor_filter_channel_1,
                                                                    "Py_force_filter_ch_2");
    dataStorage->setArrayName(SSI_converted_tenso_sensor_filter_channel_2,
                                                                    "Px_force_filter_ch_3");
    dataStorage->setArrayName(SSI_converted_tenso_sensor_filter_channel_3,
                                                                    "M_force_filter_ch_4");

    dataStorageActive = 1;
}
/*==================================================================================*/
TControlTenso::~TControlTenso()
{
    delete[] firFilter;
    delete[] calibration_tenso;
}
/*==================================================================================*/
void TControlTenso::assignSettings(QSettings *s,const QString &group_name)
{
    settings = s;
    iniGroupName = group_name;
}
/*==================================================================================*/
void TControlTenso::processReceivedFrame(void *frame)
{
    m_frame = (TTensoSensorStateSendToMachine_V3*)frame;
    //Проверка правильности пришедшего пакета
    //верные ли пришли данные
    if(m_frame->magic!=TENSO_SENSOR_TO_MACHINE_V3_magic){
        return;
    }
    // Получаем значения из последнего пакета данных
    dataStorageLastDataFrame[SSI_time_tick_ms]=m_frame->time_tick_ms/1000.0;

    dataStorageLastDataFrame[SSI_tenso_sensor_channel_0] = m_frame->tenso_sensor_channel_0;
    dataStorageLastDataFrame[SSI_tenso_sensor_channel_1] = m_frame->tenso_sensor_channel_1;
    dataStorageLastDataFrame[SSI_tenso_sensor_channel_2] = m_frame->tenso_sensor_channel_2;
    dataStorageLastDataFrame[SSI_tenso_sensor_channel_3] = m_frame->tenso_sensor_channel_3;

    //Фильтруем значения из последнего пакета данных
    dataStorageLastDataFrame[SSI_tenso_sensor_filter_channel_0]=
            firFilter[ADC_CHANNEL_0].fir_filter_get_value(dataStorageLastDataFrame[SSI_tenso_sensor_channel_0]);
    dataStorageLastDataFrame[SSI_tenso_sensor_filter_channel_1]=
            firFilter[ADC_CHANNEL_1].fir_filter_get_value(dataStorageLastDataFrame[SSI_tenso_sensor_channel_1]);
    dataStorageLastDataFrame[SSI_tenso_sensor_filter_channel_2]=
            firFilter[ADC_CHANNEL_2].fir_filter_get_value(dataStorageLastDataFrame[SSI_tenso_sensor_channel_2]);
    dataStorageLastDataFrame[SSI_tenso_sensor_filter_channel_3]=
            firFilter[ADC_CHANNEL_3].fir_filter_get_value(dataStorageLastDataFrame[SSI_tenso_sensor_channel_3]);

    //Калибруем последние прещедшие значения
    dataStorageLastDataFrame[SSI_converted_tenso_sensor_channel_0]=
            calibration_tenso[ADC_CHANNEL_0].getValueFromADC(dataStorageLastDataFrame[SSI_tenso_sensor_channel_0]);
    dataStorageLastDataFrame[SSI_converted_tenso_sensor_channel_1]=
            calibration_tenso[ADC_CHANNEL_1].getValueFromADC(dataStorageLastDataFrame[SSI_tenso_sensor_channel_1]);
    dataStorageLastDataFrame[SSI_converted_tenso_sensor_channel_2]=
            calibration_tenso[ADC_CHANNEL_2].getValueFromADC(dataStorageLastDataFrame[SSI_tenso_sensor_channel_2]);
    dataStorageLastDataFrame[SSI_converted_tenso_sensor_channel_3]=
            calibration_tenso[ADC_CHANNEL_3].getValueFromADC(dataStorageLastDataFrame[SSI_tenso_sensor_channel_3]);

    //Калибруем отфильтрованные последние  пришедшие значения
    dataStorageLastDataFrame[SSI_converted_tenso_sensor_filter_channel_0]=
            calibration_tenso[ADC_CHANNEL_0].getValueFromADC(dataStorageLastDataFrame[SSI_tenso_sensor_filter_channel_0]);
    dataStorageLastDataFrame[SSI_converted_tenso_sensor_filter_channel_1]=
            calibration_tenso[ADC_CHANNEL_1].getValueFromADC(dataStorageLastDataFrame[SSI_tenso_sensor_filter_channel_1]);
    dataStorageLastDataFrame[SSI_converted_tenso_sensor_filter_channel_2]=
            calibration_tenso[ADC_CHANNEL_2].getValueFromADC(dataStorageLastDataFrame[SSI_tenso_sensor_filter_channel_2]);
    dataStorageLastDataFrame[SSI_converted_tenso_sensor_filter_channel_3]=
            calibration_tenso[ADC_CHANNEL_3].getValueFromADC(dataStorageLastDataFrame[SSI_tenso_sensor_filter_channel_3]);

    //Записываем все последние данные в хранилище
    if(dataStorageActive){
        dataStorage->addDoubleDataFrame(dataStorageLastDataFrame);
        emit sgNewDiagramData();
    }

}
/*==================================================================================*/
void TControlTenso::slClearDiagramData()
{
    dataStorage->clear();
    emit sgNewDiagramData();
}
/*==================================================================================*/
void TControlTenso::slSaveSettings()
{
    for(int i = 0; i < NUMBER_CHANNELS_ADC; ++i)
    {
        calibration_tenso[i].saveSettings(settings, iniGroupName + "calib_tenso_channel_" + i);
        firFilter[i].saveSettings(settings,iniGroupName + "fir_filter_" + i);

    }
}
/*==================================================================================*/
void TControlTenso::slLoadSettings()
{
    for(int i = 0; i < NUMBER_CHANNELS_ADC; ++i)
    {
        calibration_tenso[i].loadSettings(settings, iniGroupName + "calib_tenso_channel_" + i);
        firFilter[i].loadSettings(settings,iniGroupName + "fir_filter_" + i);
    }
}
/*==================================================================================*/
void TControlTenso::slLoadTextData()
{
    dataStorage->loadFile();
    emit sgNewDiagramData();
}
/*==================================================================================*/
void TControlTenso::slSaveTextData()
{
    dataStorage->saveFile();
}
/*==================================================================================*/

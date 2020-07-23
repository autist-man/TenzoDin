#include "view_calibration_machine.h"
/*================================================================*/
TViewCalibrationMachine::TViewCalibrationMachine(TControlTenso *m,QWidget *parent )
    :QWidget(parent)
{
    //Контроллер
    ctrl = m;

    calibrationGroupBoxLayout = new QGridLayout(this);
    setLayout(calibrationGroupBoxLayout);

    //Массив виджетов для подсказки текущих значений
    qle_cur_values = new QLabel[NUMBER_CHANNELS_ADC];

    //Объекты калибровки по каждому каналу
        calibStructControl_force[ADC_CHANNEL_0] = new TViewCalibrationStructureControl("Pz(Канал 1)",
                                                                          &ctrl->calibration_tenso[ADC_CHANNEL_0], this);
        calibStructControl_force[ADC_CHANNEL_1] = new TViewCalibrationStructureControl("Py(Канал 2)",
                                                                          &ctrl->calibration_tenso[ADC_CHANNEL_1], this);
        calibStructControl_force[ADC_CHANNEL_2] = new TViewCalibrationStructureControl("Px(Канал 3)",
                                                                          &ctrl->calibration_tenso[ADC_CHANNEL_2], this);
        calibStructControl_force[ADC_CHANNEL_3] = new TViewCalibrationStructureControl("Mкр(Канал 4)",
                                                                          &ctrl->calibration_tenso[ADC_CHANNEL_3], this);

    //Переменные для облегчения компоновки
    //y - строка, x - столбец
    int y = 0, x = 0;
    for(int i = ADC_CHANNEL_0; i < NUMBER_CHANNELS_ADC; i++)
    {
        calibrationGroupBoxLayout->addWidget(&qle_cur_values[i], y ,x);
        calibrationGroupBoxLayout->addWidget(calibStructControl_force[i], y+1, x++);
        y = 0;
    }
    calibrationGroupBoxLayout->setRowStretch(8,100);
    calibrationGroupBoxLayout->setColumnStretch(8,100);

    //Обновление текущих значений с приходом нового пакета данных
    connect(ctrl,SIGNAL(sgNewDiagramData()),this,SLOT(updateVisualValues()));
    updateVisualValues();
}
/*================================================================*/
TViewCalibrationMachine::~TViewCalibrationMachine()
{
}
/*================================================================*/
void TViewCalibrationMachine::updateVisualValues()
{
    QString s;
    QTextStream st(&s);
    st.setRealNumberPrecision(1);
    st.setRealNumberNotation(QTextStream::FixedNotation);

    for(int i = 0; i < NUMBER_CHANNELS_ADC;  i++)
    {
        st<<tr("Значение АЦП = ") << ctrl->dataStorageLastDataFrame[TControlTenso::SSI_tenso_sensor_channel_0 + i] <<"\n";
        st<<tr("Значение силы = ")<<ctrl->dataStorageLastDataFrame[TControlTenso::SSI_converted_tenso_sensor_channel_0 + i];
        qle_cur_values[i].setText(s);
        s.clear();
    }
}
/*================================================================*/



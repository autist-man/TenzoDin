#ifndef __CALIBRATION_FOR_LINEAR_CONVERTER_H_
#define __CALIBRATION_FOR_LINEAR_CONVERTER_H_
/*======================================================================================*/
/*
    Объект - структура для преобразования значений
    (калибровка точек)
*/
/*======================================================================================*/
#include <QtGui>
#include "linear_converter_f.h"
/*======================================================================================*/

//Максимально кол-во точек для калибровки
#define TCalibrationForLinearConverter_max_points 50

class TCalibrationForLinearConverter : public QObject
{
    Q_OBJECT
public:

    TCalibrationForLinearConverter( QObject * parent = 0 );
    ~TCalibrationForLinearConverter();

    //Загрузка и сохранение настроек
    void saveSettings(QSettings *s, const QString &name);
    void loadSettings(QSettings *s, const QString &name);

    // Преобразовать значения АЦП в силу
    float getValueFromADC(const float &adc);

    //Количество точек калибровки
    int32_t num_points;
    //Значения точек калибровки АЦП
    float adc_values[TCalibrationForLinearConverter_max_points];
    //Значения точек силы
    float normal_values[TCalibrationForLinearConverter_max_points];
    //Смещение нуля
    float value_zero_offset;

    //Отколиброванное последнее значение
    float last_value_direct;
    //Последнее прибывшее значение, которое уже откалибровано
    float last_value;
    //Флаг, показывает нужно ли инвертировать значения
    int invertADC;
    //Последнее прибывшее значение АЦП
    float last_adc;

signals:
    //Сигнал, который говорит, что настройки загружены
    void sgValuesUpdated();
};
/*=======================================================================*/
#endif

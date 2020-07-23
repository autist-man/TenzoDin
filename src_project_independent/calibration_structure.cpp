#include "calibration_structure.h"
/*==================================================================================*/
TCalibrationForLinearConverter::TCalibrationForLinearConverter(QObject *parent) :
    QObject(parent)
{
    num_points = 2;
    for(int i = 0; i < TCalibrationForLinearConverter_max_points; i++){
        adc_values[i] = i;
        normal_values[i] = i;
    }
    value_zero_offset = 0;
}
/*==================================================================================*/
TCalibrationForLinearConverter::~TCalibrationForLinearConverter()
{
}
/*==================================================================================*/
void TCalibrationForLinearConverter::saveSettings(QSettings *s, const QString &name)
{
    if(!s){
        return;
    }
    s->beginGroup(name);
    s->setValue("num_points", num_points);
    for(int i = 0; i < num_points; i++){
        s->setValue(QString("adc_values_%1").arg(i), (double) adc_values[i]);
        s->setValue(QString("normal_values_%1").arg(i), (double)normal_values[i]);
    }
    s->setValue("value_zero_offset", (double)value_zero_offset);
    s->setValue("invert_adc", invertADC);
    s->endGroup();
}
/*==================================================================================*/
void TCalibrationForLinearConverter::loadSettings(QSettings *s, const QString &name)
{
    if(!s){
        return;
    }
    s->beginGroup(name);
    num_points = s->value("num_points", 10).toInt();
    if(num_points < 2) num_points = 2;
    if(num_points >= TCalibrationForLinearConverter_max_points)
        num_points = TCalibrationForLinearConverter_max_points - 1;
    for(int i = 0; i < num_points; i++){
        adc_values[i] = s->value(QString("adc_values_%1").arg(i), i).toFloat();
        normal_values[i] = s->value(QString("normal_values_%1").arg(i), i).toFloat();
    }
    value_zero_offset = s->value("value_zero_offset", 0).toFloat();
    invertADC = s->value("invert_adc", 0).toInt();
    s->endGroup();
    emit  sgValuesUpdated();
}
/*==================================================================================*/
float TCalibrationForLinearConverter::getValueFromADC(const float &adc)
{
    last_adc = adc;
    if(invertADC) last_adc =- adc;
    last_value_direct = lc_convert_adc_to_value(&last_adc, adc_values, normal_values, &num_points);
    last_value = last_value_direct - value_zero_offset;
    return last_value;
}


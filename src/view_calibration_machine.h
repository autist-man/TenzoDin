#ifndef VIEW_CALIBRATION_MACHINE_H
#define VIEW_CALIBRATION_MACHINE_H

/*
 Объект - содержит виджеты калиборовки по каждому каналу,
 и виджет для подсказки текущих значений по каждому каналу.
 */
/*================================================================*/

#include "ctrl_tenso.h"
#include "view_calibration_structure.h"

/*================================================================*/
class TViewCalibrationMachine : public QWidget
{
Q_OBJECT
public:
    TViewCalibrationMachine(TControlTenso *m, QWidget *parent );
    ~TViewCalibrationMachine();

public slots:
    //Обновляет данные для подсказки текущих значений
    void updateVisualValues();

private:
    //Указатель на контроллер
    QPointer<TControlTenso> ctrl;

    //Объекты для калибровки по каждому каналу
    TViewCalibrationStructureControl *calibStructControl_force[NUMBER_CHANNELS_ADC];

    //Массив виджетов отображает текущие
    // значения АЦП для удобства калибровки
    QLabel* qle_cur_values;

    //Слой для компоновки объектов
    QGridLayout *calibrationGroupBoxLayout;
};
/*================================================================*/
#endif // VIEW_CALIBRATION_H

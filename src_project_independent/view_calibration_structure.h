#ifndef VIEW_CALIBRATION_STRUCTURE_H
#define VIEW_CALIBRATION_STRUCTURE_H
/*
Объект - виджет калибровки, имеет элементы ввода точек калибровки
смещение нуля. инвертирование значений АЦП(силы)
*/
/*================================================================*/

#include "calibration_structure.h"

/*================================================================*/
class TViewCalibrationStructureControl : public QGroupBox
{
Q_OBJECT
public:
    TViewCalibrationStructureControl(const QString &group_box_name,
                                     TCalibrationForLinearConverter *cal_struct, QWidget *parent = 0);
    ~TViewCalibrationStructureControl();
    
public slots:
    void slUpdateVisualFromData();

    //Назначает значения калибровки с вви
    void slUpdateDataFromVisual();

    //Удаляет и добавляет точки калибровки
    //после удаления вызывает перересовку виджетов
    void slAddNewPoint();
    void slDelLastPoint();

private:
    //Указатель на структуру калибровки
    QPointer<TCalibrationForLinearConverter> cal;

    //Смещение нуля
    QLineEdit *qle_zero_value;
    //Флаговая кнопка "Инвентировать силу"
    QCheckBox *qcb_invert_adc;
    //Кнопка "Добавить"
    QPushButton *qpb_add_point;
    //Кнопка "Удалить"
    QPushButton *qpb_del_point;

    //Номер точки калибровки
    int calibration_lines_start_y;
    //Виджеты для отображения и ввода точек калибровки
    //Виджеты для отображения номера точки
    QLabel *lines_label[TCalibrationForLinearConverter_max_points];
    //Виджеты ввода-редактироваия значения АЦП точки калибровки
    QLineEdit *lines_adc[TCalibrationForLinearConverter_max_points];
    //Виджеты ввода-редактирования значений силы точки калибровки
    QLineEdit *lines_value[TCalibrationForLinearConverter_max_points];

    //Слой для компоновки виджетов точек калибровки
    QGridLayout *gb_points_layout;
    //Раставляет виджеты ввода-редактирования
    //точек калибровки, при добавлении или удалении
    //назначает значения каждому полю из загрузок
    void setNumElements(int newNumLines);
};
/*================================================================*/
#endif // VIEW_CALIBRATION_H

#include "view_calibration_structure.h"
/*================================================================*/
TViewCalibrationStructureControl::TViewCalibrationStructureControl(const QString &group_box_name,
                                                                   TCalibrationForLinearConverter *cal_struct,
                                                                   QWidget *parent)
                                                                   : QGroupBox(group_box_name, parent)
{
    cal = cal_struct;

    qle_zero_value = new QLineEdit();
    qcb_invert_adc = new QCheckBox("Инвертировать значение АЦП");
    qpb_add_point = new QPushButton("Добавить");
    qpb_del_point = new QPushButton("Удалить");

    for(int i = 0; i < TCalibrationForLinearConverter_max_points; i++){
        lines_label[i] = 0;
        lines_adc[i] = 0;
        lines_value[i] = 0;
    }

    //Группа виджетов "Начальные данные" и слой для компоновки
    QGroupBox *gb_inputs = new QGroupBox(tr("Начальные данные"));
    QVBoxLayout *gb_inputs_layout = new QVBoxLayout;

    //Слой для горизонтальной компоновки виджетов
    QHBoxLayout *gb_zero_value = new QHBoxLayout;
    gb_zero_value->addWidget(new QLabel("Смещение нуля (сила):"));
    gb_zero_value->addWidget(qle_zero_value);
    gb_inputs_layout->addLayout(gb_zero_value);
    gb_inputs_layout->addWidget(qcb_invert_adc);
    gb_inputs->setLayout(gb_inputs_layout);

    //Группа виджетов "Управление" и слой для компоновки
    QGroupBox *gb_controls = new QGroupBox(tr("Управление"));
    QHBoxLayout *gb_controls_layout = new QHBoxLayout;
    gb_controls_layout->addWidget(qpb_add_point);
    gb_controls_layout->addWidget(qpb_del_point);
    gb_controls->setLayout(gb_controls_layout);

    //Группа виджетов "Калибровочные точки" и слой для  компоновки
    QGroupBox *gb_points = new QGroupBox(tr("Калибровочные точки"));
    gb_points_layout= new QGridLayout();

    //Строка 0. Компоновка структуры ввода точек калибровки
    int y = 0;
    gb_points_layout->addWidget(new QLabel(tr("Точка")),y,0);
    gb_points_layout->addWidget(new QLabel(tr("АЦП")),y,1);
    gb_points_layout->addWidget(new QLabel(tr("Сила")),y,2);
    calibration_lines_start_y = y+1;
    gb_points->setLayout(gb_points_layout);

    //Компоновка всех трех групп виджетов в один слой.
    QGridLayout *view_layout = new QGridLayout;
    view_layout->addWidget(gb_inputs,0,0);
    view_layout->addWidget(gb_controls,1,0);
    view_layout->addWidget(gb_points,2,0);
    view_layout->setRowStretch(3,100);
    view_layout->setColumnStretch(2,100);
    setLayout(view_layout);

    //Связь между элементами ввода и структурой калибровки
    connect(qle_zero_value,SIGNAL(editingFinished()),this,SLOT(slUpdateDataFromVisual()));
    connect(qcb_invert_adc,SIGNAL(stateChanged(int)),this,SLOT(slUpdateDataFromVisual()));
    connect(qpb_add_point,SIGNAL(clicked()),this,SLOT(slAddNewPoint()));
    connect(qpb_del_point,SIGNAL(clicked()),this,SLOT(slDelLastPoint()));

    connect(cal,SIGNAL(sgValuesUpdated()),this,SLOT(slUpdateVisualFromData()));

    setNumElements(cal->num_points);
}
/*================================================================*/
TViewCalibrationStructureControl::~TViewCalibrationStructureControl()
{

}
/*================================================================*/
void TViewCalibrationStructureControl::setNumElements(int newNumLines)
{
    if(!cal){
        return;
    }
    if(newNumLines < 3) newNumLines = 2;
    if(newNumLines > TCalibrationForLinearConverter_max_points)
        newNumLines = TCalibrationForLinearConverter_max_points;
    if(newNumLines >= cal->num_points){
        for(int i = 0; i < newNumLines; i++){
            if(lines_label[i] == 0){
                lines_label[i] = new QLabel();
                gb_points_layout->addWidget(lines_label[i], i + calibration_lines_start_y, 0);
            }
            lines_label[i]->setText(QString("%1").arg(i));
            if(lines_adc[i] == 0){
                lines_adc[i] = new QLineEdit();
                gb_points_layout->addWidget(lines_adc[i], i+calibration_lines_start_y, 1);
                connect(lines_adc[i],SIGNAL(editingFinished()),this,SLOT(slUpdateDataFromVisual()));
            }
            lines_adc[i]->setText(QString("%1").arg((double)cal->adc_values[i], 0, 'f', 0));
            if(lines_value[i] == 0){
                lines_value[i] = new QLineEdit();
                gb_points_layout->addWidget(lines_value[i], i + calibration_lines_start_y, 2);
                connect(lines_value[i],SIGNAL(editingFinished()),this,SLOT(slUpdateDataFromVisual()));
            }
            lines_value[i]->setText(QString("%1").arg((double)cal->normal_values[i], 0, 'f', 0));
        }
    }else if(newNumLines < cal->num_points){
        for(int i = cal->num_points-1; i >= newNumLines; i--){
            gb_points_layout->removeWidget(lines_label[i]); delete lines_label[i]; lines_label[i] = 0;
            gb_points_layout->removeWidget(lines_adc[i]); delete lines_adc[i]; lines_adc[i] = 0;
            gb_points_layout->removeWidget(lines_value[i]); delete lines_value[i]; lines_value[i] = 0;
        }
    }
    cal->num_points = newNumLines;
    qle_zero_value->setText(QString("%1").arg((double)cal->value_zero_offset));
    if(cal->invertADC) qcb_invert_adc->setCheckState(Qt::Checked);
    else qcb_invert_adc->setCheckState(Qt::Unchecked);
}
/*================================================================*/
void TViewCalibrationStructureControl::slUpdateVisualFromData()
{
    if(!cal){
        return;
    }
    setNumElements(cal->num_points);
}
/*================================================================*/
void TViewCalibrationStructureControl::slAddNewPoint()
{
    if(!cal){
        return;
    }
    setNumElements(cal->num_points+1);
}
/*================================================================*/
void TViewCalibrationStructureControl::slDelLastPoint()
{
    if(!cal){
        return;
    }
    setNumElements(cal->num_points-1);
}
/*================================================================*/
void TViewCalibrationStructureControl::slUpdateDataFromVisual()
{
    if(cal->num_points > TCalibrationForLinearConverter_max_points)
        cal->num_points = TCalibrationForLinearConverter_max_points - 1;
    for(int i = 0; i < cal->num_points; i++){
        cal->adc_values[i] = lines_adc[i]->text().toFloat();
        cal->normal_values[i] = lines_value[i]->text().toFloat();
    }
    cal->value_zero_offset = qle_zero_value->text().toFloat();
    cal->invertADC = qcb_invert_adc->isChecked();
}
/*================================================================*/


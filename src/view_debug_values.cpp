#include "view_debug_values.h"
#undef qDebug
#define qDebug(c)
/*================================================================*/
TViewDebugValues::TViewDebugValues(TControlMachine * m,QWidget * parent)
: QGroupBox(parent)
{
    int j;
    qDebug("TViewDebugValues::TViewDebugValues\n");
    ctrl = m;

    ql_sensor_text = new QLabel(this);
    ql_machine_machine_setup1_text = new QLabel(this);
    ql_machine_control_text = new QLabel(this);

    QGridLayout* subViewDebugValuesGroupBoxLayout = new QGridLayout(this);

    j=0;
    QLabel * ldvv_t1 = new QLabel(tr("Basic status data:"));
    ldvv_t1->setStyleSheet("QLabel { color : red; }");
    subViewDebugValuesGroupBoxLayout->addWidget(ldvv_t1,j++,0);
    subViewDebugValuesGroupBoxLayout->addWidget(ql_sensor_text,j++,0);

    j=0;
    QLabel * ldvv_t2 = new QLabel(tr("Machine setup 1 data:"));
    ldvv_t2->setStyleSheet("QLabel { color : red; }");
    subViewDebugValuesGroupBoxLayout->addWidget(ldvv_t2,j++,1);
    subViewDebugValuesGroupBoxLayout->addWidget(ql_machine_machine_setup1_text,j++,1);

    j=0;
    QLabel * ldvv_t3 = new QLabel(tr("Machine control data:"));
    ldvv_t3->setStyleSheet("QLabel { color : red; }");
    subViewDebugValuesGroupBoxLayout->addWidget(ldvv_t3,j++,2);
    subViewDebugValuesGroupBoxLayout->addWidget(ql_machine_control_text,j++,2);

    subViewDebugValuesGroupBoxLayout->setRowStretch(50,100);
    subViewDebugValuesGroupBoxLayout->setColumnStretch(50,100);
    setLayout(subViewDebugValuesGroupBoxLayout);


    connect(ctrl,SIGNAL(sgNewBasicStatusData()),this,SLOT(updateInfo()));

    updateInfo();
}
/*================================================================*/
void TViewDebugValues::updateInfo( void )
{
    QString s;
    QTextStream st(&s);
// базовое состояние машины
    s="Received info (BasicStatusData):\n";
    st.setRealNumberNotation(QTextStream::FixedNotation);
    st.setRealNumberPrecision(0);
    st<<"\t\t\t\t\t\n";
    st<<"time_tick_ms = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_time_tick_ms] <<"\n";
    st<<"force_dyn_max = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_force_dyn_max] <<"\n";
    st<<"force_measure_filter_static = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_force_measure_filter_static] <<"\n";
    st<<"force_control_filter_or_dyn_min = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_force_control_filter_or_dyn_min] <<"\n";
    st<<"\n";
    st<<"travel_dyn_max = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_travel_dyn_max] <<"\n";
    st<<"travel_static_or_dyn_min = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_travel_or_dyn_min] <<"\n";
    st<<"\n";
    st<<"dyn_cur_cycle = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_dyn_cur_cycle] <<"\n";
    st<<"\n";
    st<<"tenso_sensor_min = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_tenso_sensor_min] <<"\n";
    st<<"tenso_sensor_max = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_tenso_sensor_max] <<"\n";
    st<<"\n";
    st<<"TR_force_dyn_max = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_TR_force_dyn_max] <<"\n";
    st<<"TR_force_static = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_TR_force_static] <<"\n";
    st<<"TR_force_dyn_min = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_TR_force_dyn_min] <<"\n";
    st<<"\n";
    st.setRealNumberPrecision(6);
    st<<"TR_travel_dyn_min = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_TR_travel_dyn_min] <<"\n";
    st<<"TR_travel_dyn_max = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_TR_travel_dyn_max] <<"\n";
    st<<"\n";
    st<<"TR_tenso_min = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_TR_tenso_min] <<"\n";
    st<<"TR_tenso_max = "<<ctrl->dataStorageLastDataFrame[TControlMachine::SSI_TR_tenso_max] <<"\n";
    ql_sensor_text->setText(s);
// настройки 1
    s="Statistics :\n";
    st<<"\t\t\t\t\t\n";
    st<<"Num elements in data storage = "<<ctrl->dataStorage->getDataCount() <<"\n";
    ql_machine_machine_setup1_text->setText(s);
// состояние переменных управления
    s="Control data:\n";
    ql_machine_control_text->setText(s);
}
/*================================================================*/

#ifndef _TViewDebugValues_H_
#define _TViewDebugValues_H_

#include <QtGui>
#include "ctrl_tenso.h"
/*================================================================*/
class TViewDebugValues : public QGroupBox
{
    Q_OBJECT
public:
    TViewDebugValues(TControlTenso * m,QWidget * parent );

public slots:
    void updateInfo( void );
private:
    QPointer<TControlTenso> ctrl;
// состояние сенсора
    QLabel * ql_sensor_text;
// принятый advanced пакет
    QLabel *ql_machine_machine_setup1_text;
// остальные состояния
    QLabel *ql_machine_control_text;
};
/*================================================================*/
#endif // _TViewDebugValues_H_

#include "view_connect.h"
/*================================================================*/
TViewMachineConnect::TViewMachineConnect(TControlTenso * m,QWidget * parent )
        : QWidget(parent)
{
    controller = m;
    //Компоновка двух частей виджетов
    viewConfigSerialConnect = new TViewConfigSerialConnect("Последовательный порт",this);
    qpbSaveSettings = new QPushButton("Сохранить настройки",this);

    int y = 0;
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(viewConfigSerialConnect,y++,0);
    mainLayout->addWidget(qpbSaveSettings,y++,0);
    mainLayout->addWidget(new QLabel(),y++,0);
    mainLayout->addItem(new QSpacerItem (10,10,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding),0,1,1,1);
    mainLayout->addItem(new QSpacerItem (10,10,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding),y,0,3,4);
    mainLayout->setRowStretch(y,100);
    mainLayout->setColumnStretch(2,100);
    setLayout(mainLayout);

    //Подключение и сохранение настроек по кнопке "Сохранить настройки"
    connect(qpbSaveSettings,SIGNAL(clicked()),this,SLOT(slSaveSettings()));
    connect(viewConfigSerialConnect,SIGNAL(sgConnect()),this,SLOT(slSerialPortOpened()));
    connect(viewConfigSerialConnect,SIGNAL(sgDisconnect()),this,SLOT(slSerialPortClosed()));

}
/*================================================================*/
TViewMachineConnect::~TViewMachineConnect()
{
}
/*================================================================*/
void TViewMachineConnect::assignSettings(QSettings *s)
{
    settings = s;
    viewConfigSerialConnect->assignSettings(settings, "serial_connection");
}
/*================================================================*/
void TViewMachineConnect::assignPort(QextSerialPort *s)
{
    port = s;
    viewConfigSerialConnect->assignSerialPort(port);
}
/*================================================================*/
void TViewMachineConnect::slLoadSettings()
{
    viewConfigSerialConnect->slLoadSettings();
}
/*================================================================*/
void TViewMachineConnect::slSaveSettings()
{
    viewConfigSerialConnect->slSaveSettings();
    controller->slSaveSettings();
}
/*================================================================*/
void TViewMachineConnect::slSerialPortOpened()
{
    controller->setNewDevice(port);
}
/*================================================================*/
void TViewMachineConnect::slSerialPortClosed()
{
    controller->setNewDevice(NULL);
}
/*================================================================*/

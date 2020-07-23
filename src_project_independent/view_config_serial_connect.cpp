#include "view_config_serial_connect.h"
/*================================================================*/
TViewConfigSerialConnect::TViewConfigSerialConnect(const QString &group_box_name, QWidget *parent)
        : QGroupBox(group_box_name, parent)
{
    //Установка начальных значений флагов
    {
    autoReconnectActive = 0;
    serial_port = 0;
    }

    //Создаем визуальные элементы (виджеты)
    {
    portsList = new QComboBox();
    portsList->setMinimumContentsLength(60);
    portsList->setEditable(true);

    baudRateList = new QComboBox();
    baudRateList->setMinimumContentsLength(10);
    baudRateList->setEditable(true);

    statusLabel = new QLabel();
    statusLabel->setWordWrap(true);

    connectButton= new QPushButton(tr("Подключиться"));
    disconnectButton= new QPushButton(tr("Отключиться"));
    rescanButton= new QPushButton(tr("Просканировать порты"));
    }

    //Компоновка виджетов по сетке
    //начальные значения y(строка) и x(столбец)
    {
    int y = 0, x = 0;
    connectionGroupBoxLayout = new QGridLayout();
    //Строка 1.
    connectionGroupBoxLayout->addWidget(new QLabel(tr("Устройство:")),y,x++);
    connectionGroupBoxLayout->addWidget(portsList,y,x++,1,5);
    connectionGroupBoxLayout->addWidget(connectButton,y,x+5);

    //Строка 2.
    ++y;
    x = 0;
    connectionGroupBoxLayout->addWidget(new QLabel(tr("Скорость передачи:")),y,x++);
    connectionGroupBoxLayout->addWidget(baudRateList,y,x++,1,5);
    connectionGroupBoxLayout->addWidget(disconnectButton,y,x+5);

    //Строка 3.
    ++y;
    x = 0;
    connectionGroupBoxLayout->addWidget(statusLabel,y,x++,1,4);
    connectionGroupBoxLayout->addWidget(rescanButton,y,x+6);
    setLayout(connectionGroupBoxLayout);
    }

    //Подключаемся к порту по кнопке "Подключиться"
    connect(connectButton,SIGNAL(clicked()),this,SLOT(slConnect()));
    //Отключаемся от порта по кнопке "Отключиться"
    connect(disconnectButton,SIGNAL(clicked()),this,SLOT(slDisconnect()));
    //Сканируем порты на ПК по кнопке "Просканировать порты"
    connect(rescanButton,SIGNAL(clicked()),this,SLOT(slRescanPortsList()));
    //Отображение статуса подключения
    connect(this,SIGNAL(sgDisconnect()),this,SLOT(slSetVisualState()));
    connect(this,SIGNAL(sgConnect()),this,SLOT(slSetVisualState()));

    slRescanPortsList();
    slSetVisualState();

    //Таймер для обслуживания -  проверка, что USB
    //уствройство еще подключено
    portCheckTimer = new QTimer(this);
    connect(portCheckTimer,SIGNAL(timeout()),this,SLOT(slPortChecker()));
    portCheckTimer->start(1000);

}
/*================================================================*/
TViewConfigSerialConnect::~TViewConfigSerialConnect()
{
    delete portCheckTimer;
}
/*================================================================*/
void TViewConfigSerialConnect::assignSerialPort(QextSerialPort *s_port)
{
    serial_port = s_port;
    if(s_port){
        if(s_port->isOpen()){
            portsList->setEditText(s_port->portName());
            slSetVisualState();
            return;
        }
    }
}
/*================================================================*/
void TViewConfigSerialConnect::assignSettings(QSettings *s, const QString &name)
{
    settings = s;
    iniGroupName = name;
}
/*================================================================*/
QList<QextPortInfo> TViewConfigSerialConnect::getUniquePortsNames()
{
    QList<QextPortInfo> infoList;
#ifdef Q_OS_LINUX
    QStringList portNamePrefixes, portNameList;
    QextPortInfo inf;
    QDir dir("/dev/serial/by-id/");
    portNameList = dir.entryList(portNamePrefixes, (QDir::System | QDir::Files), QDir::Name);
    foreach (QString str , portNameList) {
        inf.physName = "/dev/serial/by-id/"+str;
        inf.portName = str;
        infoList.append(inf);
    }
#endif
    return infoList;
}
/*================================================================*/
void TViewConfigSerialConnect::slConnect()
{
    doConnect();
    if(serial_port->isOpen()){
        autoReconnectActive = 1;
        emit sgConnect();
    }else{
        autoReconnectActive = 0;
    }
}
/*================================================================*/
void TViewConfigSerialConnect::slDisconnect()
{
    serial_port->close();
    autoReconnectActive = 0;
    emit sgDisconnect();
}
/*================================================================*/
void TViewConfigSerialConnect::slRescanPortsList()
{
    QextPortInfo portInfo;
    portsList->clear();

    foreach(portInfo, getUniquePortsNames()) {
        portsList->addItem(portInfo.portName, portInfo.physName);
    }
    foreach(portInfo, QextSerialEnumerator::getPorts()) {
        portsList->addItem(portInfo.portName, portInfo.physName);
    }

    baudRateList->clear();
    baudRateList->addItem("115200");
    baudRateList->addItem("57600");
    baudRateList->addItem("38400");
    baudRateList->addItem("19200");
    baudRateList->addItem("9600");
}
/*================================================================*/
void TViewConfigSerialConnect::slSetVisualState()
{
    int connected = 0;
    if(serial_port){
        if(serial_port->isOpen()) connected = 1;
    }
    if(connected){
        connectButton->setDisabled(true);
        portsList->setDisabled(true);
        baudRateList->setDisabled(true);
        disconnectButton->setDisabled(false);
        statusLabel->setText("Поключено к  "+serial_port->portName());
    }else{
        connectButton->setDisabled(false);
        portsList->setDisabled(false);
        baudRateList->setDisabled(false);
        disconnectButton->setDisabled(true);
        statusLabel->setText("Отключено");
    }
}
/*================================================================*/
void TViewConfigSerialConnect::slLoadSettings()
{
    if(!settings){
        return;
    }
    settings->beginGroup(iniGroupName);
    portsList->setEditText(settings->value("port_name", portsList->itemText(0)).toString());
    baudRateList->setEditText(settings->value("baudRate","115200").toString());
    settings->endGroup();
}
/*================================================================*/
void TViewConfigSerialConnect::slSaveSettings( void )
{
    if(!settings){
        return;
    }
    settings->beginGroup(iniGroupName);
    settings->setValue("port_name", portsList->currentText());
    settings->setValue("baudRate", baudRateList->currentText());
    settings->endGroup();
}
/*================================================================*/
void TViewConfigSerialConnect::slPortChecker()
{    
    if(!serial_port){
        return;
    }
    if(portsList->currentText().isEmpty()){
        return;
    }
    if(serial_port->isOpen() && serial_port->bytesAvailable() < 0){
        serial_port->close();
    }
    if(!serial_port->isOpen() && autoReconnectActive) doConnect();
}
/*================================================================*/
void TViewConfigSerialConnect::doConnect()
{
    if(serial_port)
    {
        if(!serial_port->isOpen())
        {
            int indexInList = portsList->findText(portsList->currentText());
            QString portName = "";
            if(indexInList >= 0)
            {
                portName = portsList->itemData(indexInList).toString();
            }
            else
            {
                portName = portsList->currentText();
            }
            statusLabel->setText("Открытие: "+ portName);

            int baudRateFromList = baudRateList->currentText().toInt();
            BaudRateType baudRate;

            switch(baudRateFromList){
                case 9600: baudRate = BAUD9600;break;
                case 19200: baudRate = BAUD19200;break;
                case 57600: baudRate = BAUD57600;break;
                case 38400: baudRate = BAUD38400;break;
                case 115200: baudRate = BAUD115200;break;
                default:
                                baudRate = BAUD115200;
                                baudRateList->setEditText("115200");
                break;
            }
            serial_port->setPortName(portName);
            serial_port->setBaudRate(baudRate);
            serial_port->setDataBits(DATA_8);
            serial_port->setParity(PAR_NONE);
            serial_port->setStopBits(STOP_1);
            serial_port->setFlowControl(FLOW_OFF);
            serial_port->setQueryMode(QextSerialPort::Polling);
//            if(qcbUsePolling->checkState()!=Qt::Unchecked)
//            {
//                serial_port->setQueryMode(QextSerialPort::Polling);
//            }
//            else
//            {
//                serial_port->setQueryMode(QextSerialPort::EventDriven);
//            }
            serial_port->setTimeout(5);
            serial_port->open(QIODevice::ReadWrite);
            if(serial_port->isOpen())
            {
                statusLabel->setText("Подключен к "+serial_port->portName());
            } else
            {
                statusLabel->setText("Покдлючение к : "+serial_port->portName());
                serial_port->close();
            }
        }
        else
        {
            statusLabel->setText("Ошибка подключения: устройство уже подключено");
            return;
        }
    }
    else
    {
        statusLabel->setText("Ошибка подключения: устройство не назначено");
    }
}
/*================================================================*/

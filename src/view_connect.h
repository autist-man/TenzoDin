#ifndef VIEW_Connect_H
#define VIEW_Connect_H
/*================================================================*/
#include "ctrl_tenso.h"
#include "view_config_serial_connect.h"
#include "qextserialport.h"
/*================================================================*/
//Объект для настройки подключения
/*================================================================*/
class TViewMachineConnect : public QWidget
{
Q_OBJECT
public:
    TViewMachineConnect(TControlTenso *m, QWidget *parent);
    ~TViewMachineConnect();

    //Назначить файл настроек
    void assignSettings(QSettings *s);
    //Назвачить порт
    void assignPort(QextSerialPort *s);

public slots:
    //Вызывают функции загрузки и сохранения настроек
    //для всех объектов
    void slSaveSettings();
    void slLoadSettings();

    //Когда порт открыли - передать указатель его в контроллер
    void slSerialPortOpened();
    //Когда порт закрыли - передать в контроллер, что порта больше нет
    void slSerialPortClosed();
public:
    //Указатель на контроллер
    QPointer<TControlTenso> controller;
    //Указатель на файл настроек
    QPointer<QSettings> settings;
    //Указатель на порт
    QPointer<QextSerialPort> port;

    //Объект управления последовательным портом
    TViewConfigSerialConnect *viewConfigSerialConnect;
    //Кнопка "Сохранить настройки"
    QPushButton *qpbSaveSettings;
};
/*================================================================*/
#endif // VIEW_Connect_H

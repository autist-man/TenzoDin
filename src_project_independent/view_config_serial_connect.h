#ifndef VIEW_SERIAL_CONNECT_H
#define VIEW_SERIAL_CONNECT_H
/*
  Объект для управления последовательным портом - делает только базовые операции.
  Ему назначается порт и он им управляет. Подсоединиться, отсоединиться,
  проверка, что порт исчез, в случае чего переподсоединиться.
*/
#include <QtGui>
#include <QtGlobal>
#include "qextserialenumerator.h"
#include "qextserialport.h"
/*================================================================*/
class TViewConfigSerialConnect : public QGroupBox
{
Q_OBJECT
public:
    TViewConfigSerialConnect(const QString & group_box_name, QWidget * parent=0);
    ~TViewConfigSerialConnect();
    //Назначить каким портом управлять
    void assignSerialPort(QextSerialPort *s_port);
    //Назначить настройки
    void assignSettings(QSettings  *s, const QString &name);

    //Получить уникальные имена портов
    //(для Linux)
    QList<QextPortInfo> getUniquePortsNames();

private:
    //Подключение к порту
    void doConnect();

    //Указатель на последовательный порт
    QPointer<QextSerialPort> serial_port;

    //Флаг-показывает отключились мы сами,
    //или порт случайно отключился, если отключились сами, то
    //то он автоматически не будет переподсоединяться
    int autoReconnectActive;

    //Кнопки
    //"Подключиться"
    QPushButton *connectButton;
    //"Отключиться"
    QPushButton *disconnectButton;
    //"Просканировать порты"
    QPushButton *rescanButton;

    //Выпадающий список
    //Имена портов
    QComboBox *portsList;
    //Скорость подключения
    QComboBox *baudRateList;

    //Виджет для отображения статуса подключения
    QLabel *statusLabel;

    //Таймер для проверки на случайное
    //подключение порта, раз в секунду
    QTimer *portCheckTimer;

    //Указатель на настройки
    QPointer<QSettings> settings;
    //Имя группы настроек
    QString iniGroupName;

    //Слой для компановки всех виджетов
    QGridLayout *connectionGroupBoxLayout;

private slots:
    //Обработчики события нажатия клавиш
    //"Подключиться"
    void slConnect();
    //"Отключиться"
    void slDisconnect();
    //"Просканировать порты"
    void slRescanPortsList();

    //Показывает и обновляет
    //статус подключения
    void slSetVisualState();

    //Проверка на случайное отключение порта
    //раз в секунду, если порт отключился,
    //подключаем автоматически
    void slPortChecker();

public slots:
    //Загрузка настроек подключения
    void slLoadSettings();
    //Сохранение настроек подключения
    void slSaveSettings();

signals:
    //Сигналы подключения и отключения портов
    void sgDisconnect();
    void sgConnect();
};
/*================================================================*/
#endif // VIEW_SERIAL_CONNECT_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*
Главное окно приложения, содержит все виджеты
для работы и управления пограммой
*/
/*================================================================*/
#include <QMainWindow>

#include "qextserialport.h"
#include "ctrl_tenso.h"
#include "view_connect.h"
#include "view_diagram.h"
#include "view_calibration_machine.h"
/*================================================================*/
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //Справка о программе
    void about();
    //Отображения статуса подключения
    //и работы программы
    void displayControllerConnectionState();
    //Функция определяет какой фильтр выбран
   //и генерирует сигнал
    void changedAct(QAction* act);

    void slCloseApp();

private:
    //Настройка виджетов и меню главного окна
    void setupQActionFirFilter(int8_t numberFilter);
    void setupActions();
    void setupMenus();
    void setupWidgets();

    //Файл настроек
    QSettings *settings;

    //Объект для работы с портами
    //на компьютере
    QextSerialPort *serialPort;

    //Меню и его вкладки
    QMenu *helpMenu;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu *settingsMenu;
    QMenu *settingsFilter;
    QMenu *subSettingsFilter;
    //Группа фильтров для их
    //исключительного выбора
    QActionGroup *actGroupFilter;
    QAction *act_fir_filter_o6;
    QAction *act_fir_filter_o36;
    QAction *act_fir_filter_o196;


    //Контроллер получения и управления данными
    TControlTenso *ctrl_tenso;

    //Объект для подключения компьютера к
    //установке через порт "Подключение"
    TViewMachineConnect *view_connect;

    //Объект для отображения данных
    //"Результат"
    TViewDiagram *view_diagram;

    //Объект для калибровки значений
    //"Калибровка"
    TViewCalibrationMachine *view_calibration_machine;

    //Виджет для отображения статуса подключения
    //статуc бар
    QLabel *qle_connection_state;

    //Виджет для объединения трех виджетов
    //для возможности переключения между ними
    QTabWidget *tabWidget;

    //Растягивающийся виджет для
    //отображения виждета "Калибровка"
    QScrollArea *view_force_calibration_scroll_area;

signals:
    //Сигнал испускается когда меняем в настройках
    //номер фильтра, передает индекс фильтра в объект
    //фильтра
    void choosedAct(int8_t number);
    void sgCloseApp();
};
/*================================================================*/
#endif // MAINWINDOW_H

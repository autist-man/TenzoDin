#include "mainwindow.h"

/*================================================================*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Настройка цвета заднего фона всего главного окна
    setPalette(QPalette(QColor("#dddcde")));
    setWindowTitle(tr("TenzoDin"));

    //Назначения директории файла настроек
    QSettings::setPath (QSettings::IniFormat ,QSettings::UserScope,".");

    //Создание всех объектов, назначение файла настроек, загрузка
    //настроек из файла, назначение объекта для работы с портами
    {
        settings = new QSettings("settings.ini",QSettings::IniFormat,this);

        serialPort = new QextSerialPort(QextSerialPort::Polling);

        ctrl_tenso = new TControlTenso(this);
        ctrl_tenso->assignSettings(settings,"machine_tenso_");

        view_connect = new TViewMachineConnect(ctrl_tenso, this);
        view_connect->assignSettings(settings);
        view_connect->assignPort(serialPort);

        view_calibration_machine = new TViewCalibrationMachine(ctrl_tenso,this);
        view_diagram = new TViewDiagram(ctrl_tenso, this);

        view_connect->slLoadSettings();

        setupActions();
        setupMenus();
        setupWidgets();

        ctrl_tenso->setNewDevice(NULL);
        ctrl_tenso->slLoadSettings();
        setupQActionFirFilter(ctrl_tenso->firFilter[ADC_CHANNEL_0].getNumberFilter());

        setWindowState(windowState() | Qt::WindowMaximized | Qt::WindowActive);
    }

    connect(actGroupFilter,SIGNAL(selected(QAction*)),this,SLOT(changedAct(QAction*)));
    connect(this,SIGNAL(choosedAct(int8_t)),&ctrl_tenso->firFilter[ADC_CHANNEL_0],SLOT(changed(int8_t)));
    connect(this,SIGNAL(choosedAct(int8_t)),&ctrl_tenso->firFilter[ADC_CHANNEL_1],SLOT(changed(int8_t)));
    connect(this,SIGNAL(choosedAct(int8_t)),&ctrl_tenso->firFilter[ADC_CHANNEL_2],SLOT(changed(int8_t)));
    connect(this,SIGNAL(choosedAct(int8_t)),&ctrl_tenso->firFilter[ADC_CHANNEL_3],SLOT(changed(int8_t)));

    connect(&ctrl_tenso->firFilter[ADC_CHANNEL_0],SIGNAL(closeApp()),this,SLOT(slCloseApp()));
}
/*================================================================*/
MainWindow::~MainWindow()
{
}
/*================================================================*/
void MainWindow::setupActions()
{
     helpMenu  = new QMenu;
     settingsMenu = new QMenu;


    aboutAct = new QAction(tr("О программе"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("О Qt Creator"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    settingsFilter = new QMenu(tr("Разряд КИХ-фильтра"), this);

    actGroupFilter = new QActionGroup(settingsFilter);
    act_fir_filter_o6 = new QAction(tr("Фильтр 1"),this);
    act_fir_filter_o6->setCheckable(true);

    act_fir_filter_o36 = new QAction(tr("Фильтр 2"),this);
    act_fir_filter_o36->setCheckable(true);

    act_fir_filter_o196 = new QAction(tr("Фильтр 3"),this);
    act_fir_filter_o196->setCheckable(true);

    actGroupFilter->addAction(act_fir_filter_o6);
    actGroupFilter->addAction(act_fir_filter_o36);
    actGroupFilter->addAction(act_fir_filter_o196);

}
/*================================================================*/
void MainWindow::setupMenus()
{
    helpMenu = menuBar()->addMenu(tr("Помощь"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    settingsMenu = menuBar()->addMenu(tr("Настройки"));
    settingsMenu->addMenu(settingsFilter);
    settingsFilter->addAction(act_fir_filter_o6);
    settingsFilter->addAction(act_fir_filter_o36);
    settingsFilter->addAction(act_fir_filter_o196);

}
/*================================================================*/
void MainWindow::setupWidgets()
{
    tabWidget = new QTabWidget;

    view_force_calibration_scroll_area = new QScrollArea;
    view_force_calibration_scroll_area->setWidget(view_calibration_machine);
    view_force_calibration_scroll_area->setWidgetResizable(true);

    tabWidget->addTab(view_connect, tr("Подключение"));
    tabWidget->addTab(view_force_calibration_scroll_area, tr("Калибровка"));
    tabWidget->addTab(view_diagram, tr("Результат"));
    tabWidget->setCurrentWidget(view_diagram);
    setCentralWidget(tabWidget);

    qle_connection_state = new QLabel();
    statusBar()->insertPermanentWidget(0,qle_connection_state);

    connect(ctrl_tenso,SIGNAL(connectionUpdated()),
            this,SLOT(displayControllerConnectionState()));
}

void MainWindow::slCloseApp()
{
    emit sgCloseApp();
}
/*================================================================*/
void MainWindow::about()
{
    QMessageBox::about(this, tr("О программе"),tr("Программа создана для работы с УДМ-600. Но данный софт"
                                                  " и измерительная система может использоваться и для других измерений."));
}
/*================================================================*/
void MainWindow::displayControllerConnectionState()
{
    if(!(ctrl_tenso->deviceConnection)){
        qle_connection_state->setText(tr("Нет подключения с устройством"));
        qle_connection_state->setStyleSheet("QLabel { color : red;  background-color: yellow ;}");
        return;
    }
    if(ctrl_tenso->rcv_timeout){
        qle_connection_state->setText(tr("Состояние подключения : нет данных с машины"));
        qle_connection_state->setStyleSheet("QLabel { color : red;  background-color: yellow ;}");
        return;
    }
    qle_connection_state->setText(tr("Состояние подключения : нормальная операция"));
    qle_connection_state->setStyleSheet("QLabel { color : black;  background-color: none ;}");
}
/*================================================================*/
void MainWindow::changedAct(QAction *act)
{
    if(act->text()==act_fir_filter_o6->text())
    {
            emit choosedAct(FirFilter::FILTER_O6);
    } else if(act->text()==act_fir_filter_o36->text())
    {
            emit choosedAct(FirFilter::FILTER_O36);
    } else if(act->text()==act_fir_filter_o196->text())
    {
        emit choosedAct(FirFilter::FILTER_O196);
    }
}
/*================================================================*/
void MainWindow::setupQActionFirFilter(int8_t numberFilter)
{
    switch (numberFilter)
    {
            case FirFilter::FILTER_O6:
                   act_fir_filter_o6->setChecked(true);
                break;

            case FirFilter::FILTER_O36:
                   act_fir_filter_o36->setChecked(true);
                break;

            case FirFilter::FILTER_O196:
                   act_fir_filter_o196->setChecked(true);
                break;
    }
}
/*================================================================*/

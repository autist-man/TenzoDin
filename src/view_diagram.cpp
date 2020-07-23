#include "view_diagram.h"

/*================================================================*/
TViewDiagram::TViewDiagram( TControlTenso * m,QWidget * parent )
    : QWidget(parent)
{
    //Прием указателя на контроллер
    machine = m;

    //Главный слой виджета для внутренней компоновки виджета
    mainLayout = new QHBoxLayout;
    setLayout(mainLayout);

    //Потоки
     thr_0 = new QThread;
     thr_1 = new QThread;
     thr_2 = new QThread;
     thr_3 = new QThread;

        //Диаграммы для отображения значений
        diagram_plot_channel_0 = new QwtPlotDiagram("diagram_tenso_sensor_chained_0", Qt::black, TControlTenso::SSI_tenso_sensor_channel_0,
                                                                                                                  "diagram_tenso_sensor_filter_chained_0", Qt::darkRed, TControlTenso::SSI_tenso_sensor_filter_channel_0,
                                                                                                                  machine, "Pz (Канал 1)");
        diagram_plot_channel_1 = new QwtPlotDiagram("diagram_tenso_sensor_chained_1", Qt::blue, TControlTenso::SSI_tenso_sensor_channel_1,
                                                                                                                  "diagram_tenso_sensor_filter_chained_1", Qt::darkGreen, TControlTenso::SSI_tenso_sensor_filter_channel_1,
                                                                                                                  machine, "Py(Канал 2)");
        diagram_plot_channel_2 = new QwtPlotDiagram("diagram_tenso_sensor_chained_2", Qt::magenta, TControlTenso::SSI_tenso_sensor_channel_2,
                                                                                                                  "diagram_tenso_sensor_filter_chained_2", Qt::darkYellow, TControlTenso::SSI_tenso_sensor_filter_channel_2,
                                                                                                                  machine, "Px(Канал 3)");
        diagram_plot_channel_3 = new QwtPlotDiagram("diagram_tenso_sensor_chained_3", Qt::red, TControlTenso::SSI_tenso_sensor_channel_3,
                                                                                                                  "diagram_tenso_sensor_filter_chained_3", Qt::green, TControlTenso::SSI_tenso_sensor_filter_channel_3,
                                                                                                                  machine, "Mкр(Канал 4)");
        //Отправляем диаграммы в поток
        diagram_plot_channel_0->moveToThread(thr_0);
        diagram_plot_channel_1->moveToThread(thr_1);
        diagram_plot_channel_2->moveToThread(thr_2);
        diagram_plot_channel_3->moveToThread(thr_3);

        //Виджет соединяющий четыре диаграммы в одну область
        diagram_plot = new QWidget;
        mask_diagram_plot = new QGridLayout;
        mask_diagram_plot->addWidget(diagram_plot_channel_0->diagram,0,0);
        mask_diagram_plot->addWidget(diagram_plot_channel_1->diagram,0,1);
        mask_diagram_plot->addWidget(diagram_plot_channel_2->diagram,1,0);
        mask_diagram_plot->addWidget(diagram_plot_channel_3->diagram,1,1);
        diagram_plot->setLayout(mask_diagram_plot);
        mainLayout->addWidget(diagram_plot);

        // Область органов управления
        controlsGroupBox = new QGroupBox(tr("Управление"));
        controlsGroupBoxLayout = new QGridLayout;
        controlsGroupBox->setLayout(controlsGroupBoxLayout);

        //Переменная для удобства счета строк в слое компановке controlsGroupBoxLayout
        int y;
        // Стока 1. Кнопки "Очистить", "Сохранить"
        y=0;
        qpbClearDataButton= new QPushButton(tr("Очистить"));
        controlsGroupBoxLayout->addWidget(qpbClearDataButton,y,0,1,1);
        qpbSaveDataButton= new QPushButton(tr("Сохранить"));
        controlsGroupBoxLayout->addWidget(qpbSaveDataButton,y,1,1,1);

        // Строка 2. Кнопка "Загрузить"
        y++;
        qpbLoadDataButton= new QPushButton(tr("Загрузить"));
        controlsGroupBoxLayout->addWidget(qpbLoadDataButton,y,1,1,1);

        // Строка 3. Область выбора данных для отображения  на диаграммах
        y++;
            // Радио кнопки переключения значпений АЦП или Силы
            graphViewModeGroupBox = new QGroupBox(tr("АЦП/Сила"));
            graphViewModeGroupBoxLayout = new QVBoxLayout;
            graphViewModeGroupBox->setLayout(graphViewModeGroupBoxLayout);
            rbvADC = new QRadioButton(tr("АЦП"));
            graphViewModeGroupBoxLayout->addWidget(rbvADC);
            rbvTransformed = new QRadioButton(tr("Сила"));
            rbvADC->setChecked(true);
            graphViewModeGroupBoxLayout->addWidget(rbvTransformed);
            controlsGroupBoxLayout->addWidget(graphViewModeGroupBox,y,0,1,1);

            //Выбор показываемых кривых
            graphViewYAxis = new QGroupBox(tr("Данные :"));
            graphViewYAxisLayout = new QVBoxLayout;
            graphViewYAxis->setLayout(graphViewYAxisLayout);

            qcbShow_channel_0 = new QCheckBox(tr("Канал 1"));
            qcbShow_channel_0->setChecked(true);
            graphViewYAxisLayout->addWidget(qcbShow_channel_0);

            qcbShow_filter_channel_0 = new QCheckBox(tr("Фильтр. канал 1"));
            qcbShow_filter_channel_0->setChecked(true);
            graphViewYAxisLayout->addWidget(qcbShow_filter_channel_0);

            qcbShow_channel_1 = new QCheckBox(tr("Канал 2"));
            qcbShow_channel_1->setChecked(true);
            graphViewYAxisLayout->addWidget(qcbShow_channel_1);

            qcbShow_filter_channel_1 = new QCheckBox(tr("Фильтр. канал 2"));
            qcbShow_filter_channel_1->setChecked(true);
            graphViewYAxisLayout->addWidget(qcbShow_filter_channel_1);

            qcbShow_channel_2 = new QCheckBox(tr("Канал 3"));
            qcbShow_channel_2->setChecked(true);
            graphViewYAxisLayout->addWidget(qcbShow_channel_2);

            qcbShow_filter_channel_2 = new QCheckBox(tr("Фильтр. канал 3"));
            qcbShow_filter_channel_2->setChecked(true);
            graphViewYAxisLayout->addWidget(qcbShow_filter_channel_2);

            qcbShow_channel_3 = new QCheckBox(tr("Канал 4"));
            qcbShow_channel_3->setChecked(true);
            graphViewYAxisLayout->addWidget(qcbShow_channel_3);

            qcbShow_filter_channel_3 = new QCheckBox(tr("Фильтр. канал 4"));
            qcbShow_filter_channel_3->setChecked(true);
            graphViewYAxisLayout->addWidget(qcbShow_filter_channel_3);

            controlsGroupBoxLayout->addWidget(graphViewYAxis,y,1,1,1);

         //Строка 4. Флаговая кнопка "Возобновить/Остановить"
        y++;
        qcbStorageActive=new QCheckBox(tr("Возобновить/Остановить"));
        qcbStorageActive->setChecked(true);
        controlsGroupBoxLayout->addWidget(qcbStorageActive,y,0,1,2);

        //Строка 5. Строка для заполнения пространстваслоя
        //компоновки виджета "Управления" для коректного
        //отображения геометрии всех виджетов
        y++;
        controlsGroupBoxLayout->setRowStretch(y,1);
        controlsGroupBoxLayout->setColumnStretch(2,100);

        //Добавление виджета управление на главный слой компановки
    mainLayout->addWidget(controlsGroupBox);

     //Растяжение виджета диаграмм
    mainLayout->setStretchFactor(diagram_plot,100);
    //Задание отображения кривых
    slUpdateViewMode();

    //Очистка хранилища данных
    connect(qpbClearDataButton,SIGNAL(clicked()),machine,SLOT(slClearDiagramData()));
    //Сохранение данных в файл
    connect(qpbSaveDataButton,SIGNAL(clicked()),machine,SLOT(slSaveTextData()));
    //Загрузка данных из файла
    connect(qpbLoadDataButton,SIGNAL(clicked()),machine,SLOT(slLoadTextData()));
    //Меняем режим отображения данных "АЦП/Сила"
    connect(rbvADC, SIGNAL(toggled (bool)),this,SLOT(slUpdateViewMode()));
    connect(rbvTransformed, SIGNAL(toggled(bool)),this,SLOT(slUpdateViewMode()));
    //Выбор отображения кривых скрыть/показать
    connect(qcbShow_channel_0, SIGNAL( stateChanged(int) ),this, SLOT(slUpdateViewMode()));
    connect(qcbShow_channel_1, SIGNAL( stateChanged(int) ),this, SLOT(slUpdateViewMode()));
    connect(qcbShow_channel_2, SIGNAL( stateChanged(int) ),this, SLOT(slUpdateViewMode()));
    connect(qcbShow_channel_3, SIGNAL( stateChanged(int) ),this, SLOT(slUpdateViewMode()));
    connect(qcbShow_filter_channel_0, SIGNAL( stateChanged(int) ),this, SLOT(slUpdateViewMode()));
    connect(qcbShow_filter_channel_1, SIGNAL( stateChanged(int) ),this, SLOT(slUpdateViewMode()));
    connect(qcbShow_filter_channel_2, SIGNAL( stateChanged(int) ),this, SLOT(slUpdateViewMode()));
    connect(qcbShow_filter_channel_3, SIGNAL( stateChanged(int) ),this, SLOT(slUpdateViewMode()));
    connect(qcbStorageActive, SIGNAL( stateChanged(int) ), this, SLOT(slUpdateViewMode()));

    //Перерисовка графиков с приходом нового пакета данных и записью его в хранилище данных
    //каждая диаграмма приостанавливает главный поток, и возобновляет его, пока не выполнится
    //перерисовка каждой диаграммы
    connect(machine,SIGNAL(sgNewDiagramData()),diagram_plot_channel_0,
            SLOT(diagramReplot()), Qt::BlockingQueuedConnection);
    connect(machine,SIGNAL(sgNewDiagramData()),diagram_plot_channel_1,
            SLOT(diagramReplot()), Qt::BlockingQueuedConnection);
    connect(machine,SIGNAL(sgNewDiagramData()),diagram_plot_channel_2,
            SLOT(diagramReplot()), Qt::BlockingQueuedConnection);
    connect(machine,SIGNAL(sgNewDiagramData()),diagram_plot_channel_3,
            SLOT(diagramReplot()), Qt::BlockingQueuedConnection);

    //Запускаем все потоки
    thr_0->start();
    thr_1->start();
    thr_2->start();
    thr_3->start();
}
/*================================================================*/
TViewDiagram::~TViewDiagram()
{
    //Удаляем все потоки
    thr_0->quit();
    thr_0->wait();
    thr_1->quit();
    thr_1->wait();
    thr_2->quit();
    thr_2->wait();
    thr_3->quit();
    thr_3->wait();
}
/*================================================================*/

void TViewDiagram::slUpdateViewMode()
{
    if(rbvADC->isChecked())
    {
        diagram_plot_channel_0->m_channel = TControlTenso::SSI_tenso_sensor_channel_0;
        diagram_plot_channel_0->m_channelFilter = TControlTenso::SSI_tenso_sensor_filter_channel_0;

        diagram_plot_channel_1->m_channel = TControlTenso::SSI_tenso_sensor_channel_1;
        diagram_plot_channel_1->m_channelFilter = TControlTenso::SSI_tenso_sensor_filter_channel_1;

        diagram_plot_channel_2->m_channel = TControlTenso::SSI_tenso_sensor_channel_2;
        diagram_plot_channel_2->m_channelFilter = TControlTenso::SSI_tenso_sensor_filter_channel_2;

        diagram_plot_channel_3->m_channel = TControlTenso::SSI_tenso_sensor_channel_3;
        diagram_plot_channel_3->m_channelFilter = TControlTenso::SSI_tenso_sensor_filter_channel_3;
    } else
    {
        diagram_plot_channel_0->m_channel = TControlTenso::SSI_converted_tenso_sensor_channel_0;
        diagram_plot_channel_0->m_channelFilter = TControlTenso::SSI_converted_tenso_sensor_filter_channel_0;

        diagram_plot_channel_1->m_channel = TControlTenso::SSI_converted_tenso_sensor_channel_1;
        diagram_plot_channel_1->m_channelFilter = TControlTenso::SSI_converted_tenso_sensor_filter_channel_1;

        diagram_plot_channel_2->m_channel = TControlTenso::SSI_converted_tenso_sensor_channel_2;
        diagram_plot_channel_2->m_channelFilter = TControlTenso::SSI_converted_tenso_sensor_filter_channel_2;

        diagram_plot_channel_3->m_channel = TControlTenso::SSI_converted_tenso_sensor_channel_3;
        diagram_plot_channel_3->m_channelFilter = TControlTenso::SSI_converted_tenso_sensor_filter_channel_3;
    }

    diagram_plot_channel_0->curve->setVisible(qcbShow_channel_0->isChecked());
    diagram_plot_channel_1->curve->setVisible(qcbShow_channel_1->isChecked());
    diagram_plot_channel_2->curve->setVisible(qcbShow_channel_2->isChecked());
    diagram_plot_channel_3->curve->setVisible(qcbShow_channel_3->isChecked());

    diagram_plot_channel_0->curveFilter->setVisible(qcbShow_filter_channel_0->isChecked());
    diagram_plot_channel_1->curveFilter->setVisible(qcbShow_filter_channel_1->isChecked());
    diagram_plot_channel_2->curveFilter->setVisible(qcbShow_filter_channel_2->isChecked());
    diagram_plot_channel_3->curveFilter->setVisible(qcbShow_filter_channel_3->isChecked());

    //Разрешение на записть в хранилище данных
    machine->dataStorageActive = qcbStorageActive->isChecked();
}
/*================================================================*/


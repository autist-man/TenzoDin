#ifndef TViewDiagram_H
#define TViewDiagram_H

#include <QThread>
#include "ctrl_tenso.h"
#include "qwt_plot_diagram.h"

/*================================================================*/
/*
 Объект, который отображает данные испытаний в режиме реального времени,
 имеет возможность очищать хранилище данных, сохранять значения в файл и
 значения обратно из файла. Имеет четыре потока для лучшей производительности
 (в каждом потоке одна диаграмма отрисовывает свои кривые)
 */
/*================================================================*/
class TViewDiagram : public QWidget
{
    Q_OBJECT
public:
    TViewDiagram(TControlTenso *m,QWidget *parent);
    ~TViewDiagram();
private slots:
    void slUpdateViewMode();                                          // Изменение режима отображения кривых
private:
    QHBoxLayout *mainLayout;                                   //Главный слой компоновки виджетов

    QwtPlotDiagram *diagram_plot_channel_0;//Диаграмма первого канала
    QwtPlotDiagram *diagram_plot_channel_1;//Диаграмма воторого канала
    QwtPlotDiagram *diagram_plot_channel_2;//Диаграмма третьего канала
    QwtPlotDiagram *diagram_plot_channel_3;//Диаграмма четвертого канала

    QThread *thr_0;                                                             //Поток для первого канала
    QThread *thr_1 ;                                                            //Поток для второго канала
    QThread *thr_2;                                                             //Поток для третьего канала
    QThread *thr_3;                                                             //Поток для четвертого канала

    QWidget * diagram_plot;                                         //Виджет объединяет диаграммы
    QGridLayout *mask_diagram_plot;                   //Слой маска виджета для копоновки диаграмм

    QPointer<TControlTenso> machine;                   //Указатель на объект контроллер

    QGroupBox *controlsGroupBox;                         //Область органов управления
    QGridLayout *controlsGroupBoxLayout;       //Слой компоновки элементов управления
    QPushButton *qpbClearDataButton;               //Кнопка "Очистить"
    QPushButton *qpbSaveDataButton;                //Кнопка "Сохранить"
    QPushButton *qpbLoadDataButton;                //Кнопка "Загрузить"

    QGroupBox *graphViewModeGroupBox;      //Область выбора данных для отображения
    QVBoxLayout *graphViewModeGroupBoxLayout; //Слой компоновки для "АЦП/Сила"
    QRadioButton *rbvADC;                                            //Радиокнопка "АЦП"
    QRadioButton *rbvTransformed;                        //Радиокнопка "Сила"

    QGroupBox *graphViewYAxis;                             //Область выбора кривых "Данные"
    QVBoxLayout *graphViewYAxisLayout;         //Слой компановки "Данные"
    QCheckBox *qcbShow_channel_0;                   //Флаговая кнопка "Канал 1"
    QCheckBox *qcbShow_filter_channel_0;      //Флаговая кнопка "Фальтр. канал 1"
    QCheckBox *qcbShow_channel_1;                   //Флаговая кнопка "Канал 2"
    QCheckBox *qcbShow_filter_channel_1;      //Флаговая кнопка "Фальтр. канал 2"
    QCheckBox *qcbShow_channel_2;                   //Флаговая кнопка "Канал 3"
    QCheckBox *qcbShow_filter_channel_2;      //Флаговая кнопка "Фальтр. канал 3"
    QCheckBox *qcbShow_channel_3;                   //Флаговая кнопка "Канал 4"
    QCheckBox *qcbShow_filter_channel_3;      //Флаговая кнопка "Фальтр. канал 3"


    QCheckBox *qcbStorageActive;                        //Флаговая кнопка "Возобновить/Остановить"
};
/*================================================================*/
#endif // TViewDiagram_H

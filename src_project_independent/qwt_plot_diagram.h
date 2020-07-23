#ifndef QWTPLOTDIAGRAM_H
#define QWTPLOTDIAGRAM_H

#include <QObject>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include "src/ctrl_tenso.h"

/*================================================================*/
/*
    Диаграмма для каждого канала, принимает имя графика и его цвет.
 */
/*================================================================*/

class QwtPlotDiagram : public QObject
{
    Q_OBJECT
public:
    QwtPlotDiagram(const QString &nameCurve, const QColor &colorCurve, int channel,
                                       const QString &nameFilterCurve, const QColor &colorCurveFilter,  int channelFilter,
                                        TControlTenso *m, const QString &nameChannel);
    ~QwtPlotDiagram();

    //Диаграмма для графика
    QwtPlot *diagram;
    //Линия графика
    QwtPlotCurve *curve;
    QwtPlotCurve *curveFilter;
    //Данные АЦП или калиброванные
    int m_channel;
    int m_channelFilter;

    QPointer<TControlTenso> machine;
private:
    //Сетка на диаграмму
    QwtPlotGrid *gridDiagram;
    //Выбор области на диаграмме
    QwtPlotPicker * d_picker;

public slots:
    void diagramReplot();
};
#endif // QWTPLOTDIAGRAM_H

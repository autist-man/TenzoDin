#ifndef QWTPLOTDIAGRAM_H
#define QWTPLOTDIAGRAM_H

#include <QObject>
#include <QColor>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>

class QwtPlotDiagram : public QObject
{
    Q_OBJECT
public:
    QwtPlotDiagram(const QString &nameCurve, const QColor &colorCurve);
    ~QwtPlotDiagram();


    QwtPlot *diagram;
    QwtPlotCurve *curve;
private:
    QwtPlotGrid *gridDiagram;
    QwtPlotPicker * d_picker;


signals:

public slots:
};

#endif // QWTPLOTDIAGRAM_H

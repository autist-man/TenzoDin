#include "qwtplotdiagram.h"

QwtPlotDiagram::QwtPlotDiagram(const QString &nameCurve, const QColor &colorCurve)
{
    diagram = new QwtPlot;
    curve = new QwtPlotCurve(nameCurve);

    curve->attach(diagram);
    curve->setPen(QPen(colorCurve));
    curve->setXAxis(QwtPlot::xBottom);
    curve->setYAxis(QwtPlot::yLeft);

    gridDiagram = new QwtPlotGrid;
    gridDiagram->setMajPen(QPen(Qt::darkGreen, 2, Qt::DotLine));
    gridDiagram->setMinPen(QPen(Qt::darkCyan, 2, Qt::DotLine));
    gridDiagram->attach(diagram);

    // выбор области на графике
    d_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,QwtPlotPicker::RectRubberBand, QwtPicker::AlwaysOn, diagram->canvas());
    d_picker->setStateMachine(new QwtPickerDragRectMachine());
    d_picker->setRubberBandPen(QColor(Qt::magenta));
    d_picker->setTrackerPen(QColor(Qt::blue));


    diagram->setAxisTitle(QwtPlot::xBottom, "Время-->");
    diagram->setAxisTitle(QwtPlot::yLeft, "АЦП/Значения -->");

}

QwtPlotDiagram::~QwtPlotDiagram()
{

}


#include "qwt_plot_diagram.h"

QwtPlotDiagram::QwtPlotDiagram(const QString &nameCurve, const QColor &colorCurve, int channel,
                                                                        const QString &nameFilterCurve, const QColor &colorCurveFilter,  int   channelFilter,
                                                                        TControlTenso *m, const QString &nameChannel)
{
    machine = m;
    m_channel = channel;
    m_channelFilter = channelFilter;

    //Диаграмма для отображения графика
    diagram = new QwtPlot;
    diagram->setTitle(nameChannel);
    curve = new QwtPlotCurve(nameCurve);
    curveFilter = new QwtPlotCurve(nameFilterCurve);

    //Кривая для построения графика
    curve->attach(diagram);
    curve->setPen(QPen(colorCurve));
    curve->setXAxis(QwtPlot::xBottom);
    curve->setYAxis(QwtPlot::yLeft);

    curveFilter->attach(diagram);
    curveFilter->setPen(QPen(colorCurveFilter));
    curveFilter->setXAxis(QwtPlot::xBottom);
    curveFilter->setYAxis(QwtPlot::yLeft);

    //Сетка на диаграмме
    gridDiagram = new QwtPlotGrid;
    gridDiagram->setMajPen(QPen(Qt::darkGreen, 2, Qt::DotLine));
    gridDiagram->setMinPen(QPen(Qt::darkCyan, 2, Qt::DotLine));
    gridDiagram->attach(diagram);

    //Выбор области на графике
    d_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,QwtPlotPicker::RectRubberBand, QwtPicker::AlwaysOn, diagram->canvas());
    d_picker->setStateMachine(new QwtPickerDragRectMachine());
    d_picker->setRubberBandPen(QColor(Qt::magenta));
    d_picker->setTrackerPen(QColor(Qt::blue));

    //Название осей
    diagram->setAxisTitle(QwtPlot::xBottom, "Время-->");
    diagram->setAxisTitle(QwtPlot::yLeft, "АЦП/Сила -->");
    diagram->setAxisScale(QwtPlot::xBottom,machine->dataStorage->dataMin[TControlTenso::SSI_time_tick_ms],
                machine->dataStorage->dataMax[TControlTenso::SSI_time_tick_ms]);
}

QwtPlotDiagram::~QwtPlotDiagram()
{

}

void QwtPlotDiagram::diagramReplot()
{

    curve->setRawSamples(machine->dataStorage->dataPointer(TControlTenso::SSI_time_tick_ms),
                                                     machine->dataStorage->dataPointer(m_channel),
                                                     machine->dataStorage->getDataCount());

    curveFilter->setRawSamples(machine->dataStorage->dataPointer(TControlTenso::SSI_time_tick_ms),
                                                                    machine->dataStorage->dataPointer(m_channelFilter),
                                                                    machine->dataStorage->getDataCount());

    diagram->setAxisScale(QwtPlot::xBottom,machine->dataStorage->dataMin[TControlTenso::SSI_time_tick_ms],
                    machine->dataStorage->dataMax[TControlTenso::SSI_time_tick_ms]);
    diagram->replot();

}


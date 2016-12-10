#include "qwt.h"

qwt::qwt()
{
    myPlot = new QwtPlot();
    myPlot->setCanvasBackground( Qt::black );
    myPlot->setAxisScale( QwtPlot::yLeft, 0, 300 ); //Scale the y-axis
    myPlot->setAxisScale(QwtPlot::xBottom,0,32); //Scale the x-axis
    myPlot->enableAxis(QwtPlot::xBottom, false);
    myPlot->enableAxis(QwtPlot::yLeft, false);
    myPlot->setMaximumHeight(30);
    myPlot->setMaximumWidth(150);
    //create curve
    curve1 = new QwtPlotCurve;
    curve1->setPen(QPen(Qt::red, 2));
    //curve1->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curve1->setStyle(QwtPlotCurve::Steps);
    //curve1->attach(myPlot);
    //create histogram
    histogram = new QwtPlotHistogram;
    histogram->setPen(QPen(Qt::darkRed));
    histogram->setBrush(QBrush(Qt::red));
    histogram->attach(myPlot);
}

#ifndef QWT_H
#define QWT_H

#include <QWidget>
#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_histogram.h>
#include <qwt_samples.h>
class qwt
{
public:
    qwt();
    QwtPlot *myPlot;
    QwtPlotCurve *curve1;
    QwtPlotHistogram *histogram;
};

#endif // QWT_H

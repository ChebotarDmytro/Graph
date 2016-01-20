#ifndef GRAF
#define GRAF

#include <QWidget>
//QWT
#include <qwt_plot.h>



class QwtPlotCurve;
class QwtPlotCanvas;
class QwtPlotGrid;
class Settings;

class Graf : public QwtPlot
{
public:
    Graf(QWidget *parent = 0);
    ~Graf();

public Q_SLOTS:
    void applySettings( const Settings & );


private:
    QwtPlotCurve *curve;
    QwtPlotCanvas *canvas;
    QwtPlotGrid *grid;
    //Settings d_settings;

public:
    bool setGrafData(const QString &fileName);

};

#endif // GRAF


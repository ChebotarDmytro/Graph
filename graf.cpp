#include "graf.h"
#include "settings.h"
//FILE
#include <QVector>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <cmath>
//QWT
#include <qwt_plot_curve.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
//QT
#include <QMessageBox>

Graf::Graf(QWidget *parent): QwtPlot(parent)
{

    canvas = new QwtPlotCanvas();
    canvas->setFocusIndicator( QwtPlotCanvas::CanvasFocusIndicator );
    canvas->setFocusPolicy( Qt::StrongFocus );
    canvas->setPalette( Qt::black );
    setCanvas( canvas );

    grid = new QwtPlotGrid;
    grid->enableXMin( true );
    grid->setMajorPen( Qt::gray, 0, Qt::DotLine );
    grid->setMinorPen( Qt::darkGray, 0, Qt::DotLine );
    grid->attach(this );

    curve = new QwtPlotCurve();
    curve->setStyle(QwtPlotCurve::Lines);
    curve->setPen(QPen(Qt::blue));
    curve->attach(this);


}

Graf::~Graf(){

}


bool Graf::setGrafData(const QString &fileName)
{
setAutoReplot(true);

    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Graph"),
                                     tr("Cannot read file %1:\n%2.")
                                     .arg(file.fileName())
                                     .arg(file.errorString()));
                return false;

    }

    QTextStream in(&file);
     QString line_size = in.readAll();
      QStringList aStringList = line_size.split("\n");
       size_t j = aStringList.size(); //кількість ліній

       QString str = "", str1 = " ";
     for(int i = 0; i < j; ++i){
        QString line = line_size.split("\n").at(i);
         if(line.contains(QRegExp("[A-Za-zА-Яа-я]"))){

         } else{

              str += line;
              str += str1;
         }

     }
    QStringList linesize  =  str.split(" ");
    size_t size = linesize.size() - 1;
    double x[size];
    double y[size];
     int number = 0;
    QVector<QPointF> vector;
     for(int i = 0; i < size; ++i){
         y[i] = linesize.at(i).toDouble();
         x[i] = 1 * number++;
      vector += QPointF(x[i],y[i]);
    }

    curve->setSamples(vector);

setAutoReplot(false);

    return true;
  }

void Graf::applySettings( const Settings &settings )
{

    setAutoReplot( true );


    setAxisScale(QwtPlot::xBottom, settings.s_plot.Xfrom,
                       settings.s_plot.Xto);
    setAxisScale(QwtPlot::yLeft, settings.s_plot.Yfrom,
                       settings.s_plot.Yto);

    setTitle(settings.s_plot.name_graf);

    setAxisTitle(QwtPlot::xBottom, settings.s_plot.x_name);
    setAxisTitle(QwtPlot::yLeft, settings.s_plot.y_name);



    switch (settings.s_canvas.indexPanel) {
    case 0:
       canvas->setPalette(Qt::black);
        break;
    case 1:
        canvas->setPalette(Qt::white);
        break;
    case 2:
        canvas->setPalette(Qt::green);
        break;
    case 3:
       canvas->setPalette(Qt::blue);
        break;
    case 4:
        canvas->setPalette(Qt::cyan);
        break;
    case 5:
        canvas->setPalette(Qt::magenta);
        break;
    case 6:
        canvas->setPalette(Qt::yellow);
        break;
    }

    switch (settings.s_canvas.indexGrid) {
    case 0:
       grid->setMajorPen( Qt::gray, 0, Qt::DotLine );
       grid->setMinorPen( Qt::darkGray, 0, Qt::DotLine );
        break;
    case 1:
       grid->setMajorPen( Qt::gray, 0, Qt::NoPen );
       grid->setMinorPen( Qt::darkGray, 0, Qt::NoPen );
        break;
    case 2:
      grid->setMajorPen( Qt::gray, 0, Qt::SolidLine );
       grid->setMinorPen( Qt::darkGray, 0, Qt::SolidLine );
      break;
    case 3:
       grid->setMajorPen( Qt::gray, 0, Qt::DashLine );
       grid->setMinorPen( Qt::darkGray, 0, Qt::DashLine );
      break;
    }

    switch (settings.s_curve.indexCurve) {
    case 0:
       curve->setStyle(QwtPlotCurve::Lines);
       curve->setSymbol( NULL );
        break;
    case 1:
       curve->setStyle(QwtPlotCurve::Dots);
       curve->setSymbol( NULL );
       break;
    case 2:
        curve->setStyle(QwtPlotCurve::Sticks);
        curve->setSymbol( NULL );
        break;
    case 3:
        curve->setStyle( QwtPlotCurve::NoCurve );
        curve->setSymbol( new QwtSymbol( QwtSymbol::XCross,
            Qt::NoBrush, QPen( Qt::white ), QSize( 4, 4 ) ) );
        break;

    }


    switch (settings.s_curve.colorCurve) {
    case 0:
       curve->setPen(QPen(Qt::blue));
        break;
    case 1:
       curve->setPen(QPen(Qt::black));
        break;
    case 2:
       curve->setPen(QPen(Qt::red));
        break;
    case 3:
       curve->setPen(QPen(Qt::cyan));
        break;
    case 4:
       curve->setPen(QPen(Qt::magenta));
        break;
    case 5:
       curve->setPen(QPen(Qt::yellow));
        break;
    case 6:
       curve->setPen(QPen(Qt::green));
        break;
    }


 setAutoReplot( false );
}




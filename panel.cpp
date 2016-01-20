#include "panel.h"
#include <qlabel.h>
#include <qspinbox.h>
#include <qgridlayout.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlineedit.h>

class SpinBox: public QSpinBox
{
public:
    SpinBox( int min, int max, int step, QWidget *parent ):
        QSpinBox( parent )
    {
        setRange( min, max );
        setSingleStep( step );
    }
};


Panel::Panel(QWidget *parent):QTabWidget(parent){

    setTabPosition( QTabWidget::West );

    addTab( createPlotTab( this ), "Plot" );
    addTab( createCanvasTab( this ), "Canvas" );
    addTab( createCurveTab( this ), "Curve" );

     connect( Xfrom, SIGNAL( valueChanged( int ) ), SIGNAL( edited() ) );
     connect( Xto, SIGNAL( valueChanged( int ) ), SIGNAL( edited() ) );
     connect( Yfrom, SIGNAL( valueChanged( int ) ), SIGNAL( edited() ) );
     connect( Yto, SIGNAL( valueChanged( int ) ), SIGNAL( edited() ) );
     connect(x_lineEdit, SIGNAL(textChanged(QString) ), SIGNAL( edited() ) );
     connect(y_lineEdit, SIGNAL(textChanged(QString) ), SIGNAL( edited() ) );
     connect(title, SIGNAL(textChanged(QString) ), SIGNAL( edited() ) );
     connect(colorPanel, SIGNAL(currentIndexChanged(QString) ), SIGNAL( edited() ) );
     connect(grid, SIGNAL(currentIndexChanged(QString) ), SIGNAL( edited() ) );
     connect(curveStyle, SIGNAL(currentIndexChanged(QString) ), SIGNAL( edited() ) );
     connect(colorCurve, SIGNAL(currentIndexChanged(QString) ), SIGNAL( edited() ) );
   //  connect( d_curveWidth, SIGNAL( valueChanged( int ) ), SIGNAL( edited() ) );
}

QWidget *Panel::createPlotTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );
    Xfrom = new SpinBox( -9999, 9999, 10, page );
    Xto = new SpinBox( -9999, 9999, 10, page );
    Yfrom = new SpinBox( -9999, 9999, 10, page );
    Yto = new SpinBox( -9999, 9999, 10, page );

    x_lineEdit = new QLineEdit( page );
    y_lineEdit = new QLineEdit( page );
    title = new QLineEdit( page );

    int row = 0;

    QGridLayout *layout = new QGridLayout( page );

    layout->addWidget( new QLabel( "X(interval)", page ), row, 0 );
    layout->addWidget( Xfrom, row, 1 );
    layout->addWidget( Xto, row++, 2 );


    layout->addWidget( new QLabel( "Y(interval)", page ), row, 0 );
    layout->addWidget( Yfrom, row, 1 );
    layout->addWidget( Yto, row++, 2 );

    layout->addWidget( new QLabel( "X(name)", page ), row, 0 );
    layout->addWidget( x_lineEdit, row++, 1 );

    layout->addWidget( new QLabel( "Y(name)", page ), row, 0 );
    layout->addWidget( y_lineEdit, row++, 1 );

    layout->addWidget( new QLabel( "Title", page ), row, 0 );
    layout->addWidget( title, row++, 1 );

    layout->addLayout( new QHBoxLayout(), row++, 0 );

    layout->setColumnStretch( 1, 10 );
    layout->setRowStretch( row, 10 );

    return page;
}

QWidget *Panel::createCanvasTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );

colorPanel = new QComboBox( page );
colorPanel->addItem("black");
colorPanel->addItem("white");
colorPanel->addItem("green");
colorPanel->addItem("blue");
colorPanel->addItem("cyan");
colorPanel->addItem("magenta");
colorPanel->addItem("yellow");

grid = new QComboBox( page );
grid->addItem("Dote");
grid->addItem("None");
grid->addItem("Solid");
grid->addItem("Dashes");


int row = 0;

QGridLayout *layout = new QGridLayout( page );

layout->addWidget( new QLabel( "Panel", page ), row, 0 );
layout->addWidget( colorPanel, row++, 1 );

layout->addWidget( new QLabel( "Grid", page ), row, 0 );
layout->addWidget( grid, row++, 1 );

layout->addLayout( new QHBoxLayout(), row++, 0 );

layout->setColumnStretch( 1, 10 );
layout->setRowStretch( row, 10 );

    return page;
}

QWidget *Panel::createCurveTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );

    curveStyle = new QComboBox( page );
    curveStyle->addItem( "Lines" );
    curveStyle->addItem( "Dotted" );
    curveStyle->addItem( "Sticks" );
    curveStyle->addItem( "XCross" );


    colorCurve = new QComboBox( page );
    colorCurve->addItem("blue");
    colorCurve->addItem("black");
    colorCurve->addItem("red");
    colorCurve->addItem("cyan");
    colorCurve->addItem("magenta");
    colorCurve->addItem("yellow");
    colorCurve->addItem("green");

    //d_curveWidth = new SpinBox( 0, 10, 1, page );

    int row = 0;

    QGridLayout *layout = new QGridLayout( page );

    layout->addWidget( new QLabel( "Curve", page ), row, 0 );
    layout->addWidget( curveStyle, row++, 1 );

    layout->addWidget( new QLabel( "Color", page ), row, 0 );
    layout->addWidget( colorCurve, row++, 1 );

    //layout->addWidget( new QLabel( "Width", page ), row, 0 );
   // layout->addWidget( d_curveWidth, row++, 1 );

    layout->addLayout( new QHBoxLayout(), row++, 0 );

    layout->setColumnStretch( 1, 10 );
    layout->setRowStretch( row, 10 );

    return page;
}



void Panel::setSettings( const Settings &settings)
{
    blockSignals( true );


    Xfrom->setValue(settings.s_plot.Xfrom );
    Xto->setValue( settings.s_plot.Xto );
    Yfrom->setValue( settings.s_plot.Yfrom );
    Yto->setValue( settings.s_plot.Yto );

    x_lineEdit->setText(settings.s_plot.x_name);
    y_lineEdit->setText(settings.s_plot.y_name);

    title->setText(settings.s_plot.name_graf);

   // d_curveWidth->setValue( settings.s_curve.pen.width() );

    blockSignals( false );
}

Settings Panel::settings() const
{
    Settings s;

    s.s_plot.Xfrom = Xfrom->value();
    s.s_plot.Xto = Xto->value();
    s.s_plot.Yfrom = Yfrom->value();
    s.s_plot.Yto = Yto->value();

    s.s_plot.x_name = x_lineEdit->text();
    s.s_plot.y_name = y_lineEdit->text();

    s.s_plot.name_graf = title->text();

    s.s_canvas.indexPanel = colorPanel->currentIndex();

    s.s_canvas.indexGrid = grid->currentIndex();

    s.s_curve.indexCurve = curveStyle->currentIndex();

    s.s_curve.colorCurve = colorCurve->currentIndex();

   // s.s_curve.pen.setWidth( d_curveWidth->value() );

    return s;
}

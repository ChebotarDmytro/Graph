#ifndef PANEL
#define PANEL

#include <qtabwidget.h>
#include "settings.h"

class SpinBox;
class QComboBox;
class CheckBox;
class Settings;
class QLineEdit;
class QComboBox;

class Panel : public QTabWidget{
    Q_OBJECT
public:
    Panel(QWidget * = NULL);

    void setSettings( const Settings &);
    Settings settings() const;

Q_SIGNALS:
    void edited();

private:
    QWidget *createPlotTab( QWidget * );
    QWidget *createCanvasTab( QWidget * );
    QWidget *createCurveTab( QWidget * );


    SpinBox *Xfrom;
    SpinBox *Xto;
    SpinBox *Yfrom;
    SpinBox *Yto;
   // SpinBox  *d_curveWidth;

    QComboBox *colorPanel;
    QComboBox *grid;
    QComboBox *curveStyle;
    QComboBox *colorCurve;

    QLineEdit *x_lineEdit;
    QLineEdit *y_lineEdit;
    QLineEdit *title;

};

#endif // PANEL


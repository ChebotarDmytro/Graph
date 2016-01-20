#ifndef SETTINGS
#define SETTINGS

#include <qstring.h>
#include <qpen.h>

class Settings{
public:
    enum UpdateType
    {
        RepaintCanvas,
        Replot
    };

    Settings(){
        s_plot.Xfrom = 0;
        s_plot.Xto = 0;
        s_plot.Yfrom = 0;
        s_plot.Yto = 0;
        s_plot.x_name = "X";
        s_plot.y_name = "Y";
        s_plot.name_graf = "GRAPH";
        updateInterval = 20;
        s_curve.numPoints = 1000;
        updateType = RepaintCanvas;

    }


    struct{
        int Xfrom;
        int Xto;
        int Yfrom;
        int Yto;

        QString x_name;
        QString y_name;
        QString name_graf;

    }s_plot;

    struct{

        int indexPanel;
        int indexGrid;

    }s_canvas;

    struct{

        int indexCurve;
        int colorCurve;
        uint numPoints;
       // QPen pen;

    }s_curve;

    UpdateType updateType;
    int updateInterval;
};

#endif // SETTINGS


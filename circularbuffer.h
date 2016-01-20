#ifndef CIRCULARBUFFER
#define CIRCULARBUFFER
#include <qwt_series_data.h>
#include <qvector.h>

class CircularBuffer: public QwtSeriesData<QPointF>
{
public:
    CircularBuffer( double interval = 10.0, size_t numPoints = 1000 );
    void fill( double interval, size_t numPoints );

    void setReferenceTime( double );
    double referenceTime() const;

    virtual size_t size() const;
    virtual QPointF sample( size_t i ) const;

    virtual QRectF boundingRect() const;

    QVector<QPointF> d_values;

private:

    double d_referenceTime;
    double d_interval;

    double d_step;
    int d_startIndex;
    double d_offset;
};
#endif // CIRCULARBUFFER


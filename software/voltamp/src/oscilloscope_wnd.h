
#ifndef __OSCILLOSCOPE_WND_H_
#define __OSCILLOSCOPE_WND_H_

#include <QtGui>
#include "voltamp_io.h"
#include "ui_oscilloscope_wnd.h"
#include "curve.h"


class OscilloscopeWnd: public QMainWindow
{
    Q_OBJECT
public:
    OscilloscopeWnd( QWidget * parent = 0 );
    ~OscilloscopeWnd();

    bool isRunning() const;
    void setIo( VoltampIo * io );

signals:
    void sigReplot();
private slots:
    void slotTimeout();
    void slotF_t();
    void slotI_v();
    void slotReplot();
private:

    void measure();
    void reopen();
    void curveSizeChanged();
    void curvesCntChanged();
    void copyData( const QVector<quint16> & src, QVector<qreal> & dest );

    enum CurveType { EAUX_T, EREF_T, IAUX_T, I_EAUX, I_EREF };

    Ui_OscilloscopeWnd ui;
    VoltampIo * io;
    QTimer    * timer;
    QMutex      mutex;
    QFuture<void> future;

    CurveType curveType;
    QVector<quint16>  data;
    QVector<quint16>  eaux,   eref,   iaux;
    QVector<quint16>  eaux_m, eref_m, iaux_m;
    QVector<qreal>    paintData;

    QVector<Curve>   curves;
    static const int CURVES_CNT;
    static const int PTS_CNT;
};

#endif





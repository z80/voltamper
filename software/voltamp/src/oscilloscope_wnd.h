
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
    void slotCurveType();
    void slotPeriod();
    void slotReplot();
private:

    void measure();
    void reopen();
    void curveSizeChanged();
    void curvesCntChanged();
    void copyData( QQueue<quint16> & src, QQueue<qreal> & dest, int cnt );

    enum CurveType { EAUX_T=0, EREF_T, IAUX_T, I_EAUX, I_EREF };
    enum Period    { T_1s=0, T_10s, T_1m, T_10m };

    Ui_OscilloscopeWnd ui;
    VoltampIo * io;
    QTimer    * timer;
    QMutex      mutex;
    QFuture<void> future;

    CurveType curveType;
    Period    period;
    qreal     timeScale;
    QVector<quint16>  data;
    QVector<quint16>  eaux_m, eref_m, iaux_m;
    QQueue<quint16>   eaux,   eref,   iaux;
    QQueue<qreal>     paintDataX, paintDataY;

    QVector<Curve>   curves;
    static const int CURVES_CNT;
    static const int PTS_CNT;
};

#endif





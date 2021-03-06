
#ifndef __OSCILLOSCOPE_WND_H_
#define __OSCILLOSCOPE_WND_H_

#include <QtGui>
#include <QFuture>
#include "voltamp_io.h"
#include "ui_oscilloscope_wnd.h"
#include "curve.h"

class MainWnd;

class OscilloscopeWnd: public QMainWindow
{
    Q_OBJECT
public:
    OscilloscopeWnd( QWidget * parent = 0 );
    ~OscilloscopeWnd();

    bool isRunning() const;
    void setIo( VoltampIo * io, MainWnd * mainWnd );
    void mostRecentVals( qreal & eaux, qreal & eref, qreal & iaux );
    void mostRecentValsRaw( int & eaux, int & eref, int & iaux );
    void clearCharge();
    qreal charge();

    void clear();
    void reopen();

    void stop();

    // Update oscilloscope parameters in hardware.
    void updateHdwOsc( bool continuous = true, qreal sweepT = -1.0 );
signals:
    void sigReplot();
    void sigStartNewCurve();
private slots:
    void slotTimeout();
    void slotCurveType();
    void slotPeriod();
    void slotReplot();
    void slotStartNewCurve();
private:

    void measure();
    void curveSizeChanged();
    void curvesCntChanged();
    void copyData( QQueue<qreal> & src, QQueue<qreal> & dest, int cnt );

    void measureContinuous(VoltampIo * io);
    void measurePeriodic(VoltampIo * io);
    void replotContinuous();
    void replotPeriodic();

    enum CurveType { EAUX_T=0, EREF_T, IAUX_T, I_EAUX, I_EREF };
    enum Period    { T_1s=0, T_10s, T_1m, T_10m };

    Ui_OscilloscopeWnd ui;
    VoltampIo * io;
    MainWnd   * mainWnd;
    QTimer    * timer;
    QMutex      mutex;
    QFuture<void> future;

    CurveType curveType;
    Period    period;
    qreal     timeScale;
    qreal     lastPeriod;
    int       lastPtsCnt;
    bool      continuousOsc, startNewCurve, startOscilloscope;
    QSemaphore periodicSem;

    QVector<quint16>  data;
    QVector<quint16>  eaux_m, eref_m, iaux_m;
    QQueue<qreal>     eaux,    eref,    iaux;
    QVector<qreal>    luaEaux, luaEref, luaIaux;
    QQueue<qreal>     paintDataX, paintDataY;

    // Buffer related stuff.
    QVector<quint16> bufferData;
    //QQueue<qreal>    bufferX, bufferY;
    bool bufferEaux, bufferEref, bufferIaux;

    QVector<Curve>   curves;

    qreal lastEaux, lastEref, lastIaux, integralCharge;
    int   lastEauxRaw, lastErefRaw, lastIauxRaw;
    bool  terminate;

    static const int CURVES_CNT;
    static const int PTS_CNT;

    int queueSz;
};

#endif





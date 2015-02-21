
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
    void sigNewData();
private slots:
    void slotTimeout();
    void slotF_t();
    void slotI_v();
    void slotNewData();
private:

    void measure();
    void reopen();
    Ui_OscilloscopeWnd ui;
    VoltampIo * io;
    QTimer    * timer;
    QFuture     future;

    QVector<quint16>  data;
    QVector<quint16>  eaux,   eref,   iaux;
    QVector<quint16>  eaux_m, eref_m, iaux_m;

    QVector<Curve> m_curves;
    static const int CURVES_CNT;
};

#endif





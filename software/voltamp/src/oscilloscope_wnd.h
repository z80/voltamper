
#ifndef __OSCILLOSCOPE_WND_H_
#define __OSCILLOSCOPE_WND_H_

#include <QtGui>
#include "voltamp_io.h"

class OscilloscopeWnd: public QMainWindow
{
    Q_OBJECT
public:
    OscilloscopeWnd( VoltampIo * io, QWidget * parent = 0 );
    ~OscilloscopeWnd();

    bool isRunning() const;

signals:
    void sigNewData();
private slots:
    void slotRun();
    void slotF_t();
    void slotI_v();
    void slotNewData();
private:
    VoltampIo * io;
};

#endif





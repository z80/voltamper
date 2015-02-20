
#ifndef __OSCILLOSCOPE_WND_H_
#define __OSCILLOSCOPE_WND_H_

#include <QtGui>
#include "voltamp_io.h"
#include "ui_oscilloscope_wnd.h"

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
    void slotRun();
    void slotF_t();
    void slotI_v();
    void slotNewData();
private:
    Ui_OscilloscopeWnd ui;
    VoltampIo * io;
};

#endif






#ifndef __DC_CURRENT_WND_H_
#define __DC_CURRENT_WND_H_

#include <QtGui>
#include "ui_dc_current_wnd.h"
#include "voltamp_io.h"

class MainWnd;

class DcCurrentWnd: public QWidget
{
    Q_OBJECT
public:
    DcCurrentWnd( QWidget * parent = 0 );
    ~DcCurrentWnd();

    void setIo( VoltampIo * io, MainWnd * mainWnd );

private slots:
    void slotChange();
    void slotApply();

private:
    Ui_CurrentWnd ui;
    VoltampIo * io;
    MainWnd * mainWnd;
};



#endif




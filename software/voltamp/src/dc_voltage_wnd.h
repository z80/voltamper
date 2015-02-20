
#ifndef __DC_VOLTAGE_WND_H_
#define __DC_VOLTAGE_WND_H_

#include <QtGui>
#include "ui_dc_voltage_wnd.h"
#include "voltamp_io.h"

class DcVoltageWnd: public QWidget
{
    Q_OBJECT
public:
    DcVoltageWnd( QWidget * parent = 0 );
    ~DcVoltageWnd();

    void setIo( VoltampIo * io );

private slots:
    void slotChange();
    void slotApply();

private:
    Ui_DcVoltageWnd ui;
    VoltampIo * io;
};



#endif





#ifndef __CALIBRATION_WND_H_
#define __CALIBRATION_WND_H_

#include <QtGui>
#include "ui_calibration_wnd.h"
#include "voltamp_io.h"

class MainWnd;


class CalibrationWnd: public QWidget
{
    Q_OBJECT
public:
    CalibrationWnd( QWidget * parent = 0 );
    ~CalibrationWnd();

    void setIo( VoltampIo * io, MainWnd * mainWnd );

private slots:
    void slotEnable();
    void slotAddVolt();
    void slotAddCurr();
private:
    void setRandomVolt();
    void calc();

    Ui_CalibrationWnd ui;
    MainWnd * mainWnd;
    VoltampIo * io;

    QVector<qreal> x;
    QVecror<qreal> y;
};


#endif



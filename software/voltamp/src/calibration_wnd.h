
#ifndef __CALIBRATION_WND_H_
#define __CALIBRATION_WND_H_

#include <QtGui>
#include "ui_calibration_wnd.h"
#include "voltamp_io.h"

class MainWnd;
class OscilloscopeWnd;

class CalibrationWnd: public QWidget
{
    Q_OBJECT
public:
    CalibrationWnd( QWidget * parent = 0 );
    ~CalibrationWnd();

    void setIo( VoltampIo * io, MainWnd * mainWnd, OscilloscopeWnd * osc );

private slots:
    void slotEnable();
    void slotAddVolt();
    void slotAddCurr();
private:
    void setRandomVolt();
    void calcVolt();
    void calcCurr();

    Ui_CalibrationWnd ui;
    MainWnd * mainWnd;
    OscilloscopeWnd * osc;
    VoltampIo * io;

    int dacLow,
        dacHigh;

    QList<int> dacLowV,
               dacHighV,
               adcAux,
               adcRef,

               dacLowI,
               dacHighI,
               adcI;

    QVector<qreal> volt,
                   curr;
};


#endif






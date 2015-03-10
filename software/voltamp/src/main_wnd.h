
#ifndef __MAIN_WND_H_
#define __MAIN_WND_H_

#include <QtGui>
#include "ui_main_wnd.h"
#include "voltamp_io.h"
#include "oscilloscope_wnd.h"
#include "dc_voltage_wnd.h"
#include "single_pulse_wnd.h"
#include "meandr_wnd.h"
#include "sweep_wnd.h"
#include "calibration_wnd.h"

class MainWnd: public QMainWindow
{
    Q_OBJECT
public:
    MainWnd( QWidget * parent = 0 );
    ~MainWnd();

    qreal vAux( quint16 adc );
    qreal vRef( quint16 adc );
    qreal iAux( quint16 adc );
    void  dac( qreal v, int & dacLow, int & dacHigh );
    int   timeToTicks( qreal time );

    void setStatus( quint16 eaux, quint16 eref, quint16 iaux );

    void setRelays( bool shortRelay, bool outRelay );

    void setCalibrationDac( qreal aLow, qreal aHigh, qreal b );
    void setCalibrationAdcVolt( qreal aAux, qreal bAux, qreal aRef, qreal bRef );
    void setCalibrationAdcCurr( qreal aI, qreal bI );

    void loadSettings();
    void saveSettings();

    const QString & deviceName() const;
public slots:
    void slotQuit();
    void slotReopen();
    void slotAbout();

    void slotDc();
    void slotSinglePulse();
    void slotMeandr();
    void slotSweep();

    void slotShortRelay();
    void slotOutRelay();

    void slotCalibration();
private:
    void setTitle( const QString & stri );

    QString devName;

    Ui_MainWnd ui;
    VoltampIo  * io;
    OscilloscopeWnd * osc;
    DcVoltageWnd * dcWnd;
    SinglePulseWnd * spWnd;
    MeandrWnd * mrWnd;
    SweepWnd * swWnd;
    CalibrationWnd * calibrationWnd;

    QLabel * statusLabel;

    qreal aDacLow, aDacHigh, bDac;
    qreal aAdcAux, bAdcAux, aAdcRef, bAdcRef;
    qreal aAdcI, bAdcI;

    static const QString SETTINGS_INI;
};

#endif





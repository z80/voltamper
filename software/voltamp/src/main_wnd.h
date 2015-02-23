
#ifndef __MAIN_WND_H_
#define __MAIN_WND_H_

#include <QtGui>
#include "ui_main_wnd.h"
#include "voltamp_io.h"
#include "oscilloscope_wnd.h"
#include "dc_voltage_wnd.h"
#include "single_pulse_wnd.h"
#include "meandr_wnd.h"

class MainWnd: public QMainWindow
{
    Q_OBJECT
public:
    MainWnd( QWidget * parent = 0 );
    ~MainWnd();

    qreal v( quint16 adc );
    qreal i( quint16 adc );
    void  dac( qreal v, int & dacLow, int & dacHigh );

    void setStatus( quint16 eaux, quint16 eref, quint16 iaux );

private slots:
    void slotQuit();
    void slotReopen();
    void slotAbout();

    void slotDc();
    void slotSinglePulse();
    void slotMeandr();

    void slotShortRelay();
    void slotOutRelay();
private:
    void setTitle( const QString & stri );

    Ui_MainWnd ui;
    VoltampIo  * io;
    OscilloscopeWnd * osc;
    DcVoltageWnd * dcWnd;
    SinglePulseWnd * spWnd;
    MeandrWnd * mrWnd;

    QLabel * statusLabel;
};

#endif





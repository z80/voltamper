
#include "calibration_wnd.h"
#include "main_wnd.h"
#include "oscilloscope_wnd.h"

CalibrationWnd::CalibrationWnd( QWidget * parent )
: QWidget( parent )
{
    ui.setupUi( this );
}

CalibrationWnd::~CalibrationWnd()
{

}

void CalibrationWnd::setIo( VoltampIo * io, MainWnd * mainWnd, OscilloscopeWnd * osc )
{
    this->io      = io;
    this->mainWnd = mainWnd;
    this->osc     = osc;
}

void CalibrationWnd::slotEnable()
{
    bool en = ui.mode->isChecked();
    ui.panel->setEnabled( en );
    if ( en )
    {
        dacLowV.clear();
        dacHighV.clear();
        adcAux.clear();
        adcRef.clear();
        dacLowI.clear();
        dacHighI.clear();
        adcI.clear();
        volt.clear();
        curr.clear();

        setRandomVolt();
    }
}

void CalibrationWnd::slotAddVolt()
{
    qreal v = ui.voltValue->value();
    volt.append( v );

    int eaux, eref, iaux;
    osc->mostRecentVals( eaux, eref, iaux );

    adcAux.append( eaux );
    adcRef.append( eref );

    dacLowV.append( dacLow );
    dacHighV.append( dacHigh );
}

void CalibrationWnd::slotAddCurr()
{
    qreal v = ui.currValue->value();
    curr.append( v );

    int eaux, eref, iaux;
    osc->mostRecentVals( eaux, eref, iaux );
    adcI.append( iaux );

    dacLowI.append( dacLow );
    dacHighI.append( dacHigh );
}

void CalibrationWnd::setRandomVolt()
{
    int range = ui.voltRange->value() * 2047 / 100;
    QTime t;
    int seed = t.msec() + (t.second() + (t.minute() + t.hour() * 24) * 60) * 1000;
    qsrand( seed );
    int dacLow  = qrand() * range / RAND_MAX + 2047;
    int dacHigh = qrand() * range / RAND_MAX + 2047;

    bool res = io->set_dac_raw( dacLow, dacHigh );
    if ( !res )
    {
        QMessageBox::critical( this, "Error", "Failed to set voltage!" );
        return;
    }

    this->dacLow  = dacLow;
    this->dacHigh = dacHigh;
}

void CalibrationWnd::calcVolt()
{

}

void CalibrationWnd::calcCurr()
{

}



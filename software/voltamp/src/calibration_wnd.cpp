
#include "calibration_wnd.h"
#include "main_wnd.h"

CalibrationWnd::CalibrationWnd( QWidget * parent )
: QWidget( parent )
{
    ui.setupUi( this );
}

CalibrationWnd::~CalibrationWnd()
{

}

void CalibrationWnd::setIo( VoltampIo * io, MainWnd * mainWnd )
{
    this->io = io;
    this->mainWnd = mainWnd;
}

void CalibrationWnd::slotEnable()
{
    bool en = ui.mode->isChecked();
    ui.panel->setEnabled( en );

}

void CalibrationWnd::slotAddVolt()
{

}

void CalibrationWnd::slotAddCurr()
{

}

void CalibrationWnd::setRandomVolt()
{

}

void CalibrationWnd::calc()
{

}



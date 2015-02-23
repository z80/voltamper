
#include "dc_voltage_wnd.h"

DcVoltageWnd::DcVoltageWnd( QWidget * parent )
    : QWidget( parent )
{
    ui.setupUi( this );
    io = 0;

    connect( ui.value, SIGNAL(valueChanged(qreal)), this, SLOT(slotChange()) );
    connect( ui.value, SIGNAL(editingFinished()),   this, SLOT(slotApply()) );
}

DcVoltageWnd::~DcVoltageWnd()
{

}

void DcVoltageWnd::setIo( VoltampIo * io )
{
    this->io = io;
}

void DcVoltageWnd::slotChange()
{
    QString ss = "background-color: rgb(185, 10, 10);\nborder-color: rgb(185, 10, 10);";
    setStyleSheet( ss );
}

void DcVoltageWnd::slotApply()
{
    qreal volt = ui.value->value();
    int dacLow, dacHigh;
    dacLow = 2047;
    dacHigh = static_cast<int>( volt );
    bool res = io->set_dac_raw( dacLow, dacHigh );

    QString ss = "background-color: rgb(185, 10, 10);\nborder-color: rgb(185, 10, 10);";
    setStyleSheet( ss );
}




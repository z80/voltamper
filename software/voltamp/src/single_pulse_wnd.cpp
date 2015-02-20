
#include "single_pulse_wnd.h"

SinglePulseWnd::SinglePulseWnd( QWidget * parent )
    : QWidget( parent )
{
    ui.setupUi( this );
    io = 0;
    connect( ui.apply, SIGNAL(clicked()), this, SLOT(slotApply()) );
}

SinglePulseWnd::~SinglePulseWnd()
{

}

void SinglePulseWnd::setIo( VoltampIo * io )
{
    this->io = io;
}

void SinglePulseWnd::slotApply()
{
    qreal volt     = ui.volt->value();
    qreal duration = ui.duration->value();

    int dacLow = 0;
    int dacHigh = static_cast<int>( volt );
    int time = static_cast<int>( duration );

    bool res;
    res = io->set_one_pulse_raw( dacLow, dacHigh, time );
}




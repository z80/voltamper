
#include "sweep_wnd.h"
#include "main_wnd.h"

SweepWnd::SweepWnd( QWidget * parent )
: QWidget( parent )
{
    ui.setupUi( this );
    connect( ui.apply, SIGNAL(clicked()), this, SLOT(slotApply()) );

    setWindowFlags( Qt::Tool | Qt::WindowStaysOnTopHint );
}

SweepWnd::~SweepWnd()
{

}

void SweepWnd::setIo( VoltampIo * io, MainWnd * mainWnd )
{
    this->io      = io;
    this->mainWnd = mainWnd;
}

void SweepWnd::slotApply()
{

    int dacLow1,  dacHigh1;
    qreal volt     = ui.low->value();
    mainWnd->dac( volt, dacLow1, dacHigh1 );

    int dacLow2, dacHigh2;
    volt     = ui.high->value();
    mainWnd->dac( volt, dacLow2, dacHigh2 );

    qreal duration = ui.period->value();

    bool res;
    if ( io->isOpen() )
    {
        res = io->set_sweep_raw( dacLow1, dacHigh1, dacLow2, dacHigh2, duration );
        if ( !res )
            return;
        mainWnd->oscWnd()->updateHdwOsc( false, 2.0*duration/1000.0 );
    }
}




#include "meandr_wnd.h"
#include "main_wnd.h"

MeandrWnd::MeandrWnd( QWidget * parent )
    : QWidget( parent )
{
    ui.setupUi( this );
    io = 0;

    connect( ui.apply, SIGNAL(clicked()), this, SLOT(slotApply()) );
}

MeandrWnd::~MeandrWnd()
{

}

void MeandrWnd::setIo( VoltampIo * io, MainWnd * mainWnd )
{
    this->io      = io;
    this->mainWnd = mainWnd;
}

void MeandrWnd::slotApply()
{
    int dacLow1, dacHigh1, time1,
        dacLow2, dacHigh2, time2;

    qreal volt     = ui.low->value();
    qreal duration = ui.lowTime->value();
    mainWnd->dac( volt, dacLow1, dacHigh1 );
    time1 = io->msToTicks( duration );

    volt     = ui.high->value();
    duration = ui.highTime->value();
    mainWnd->dac( volt, dacLow2, dacHigh2 );
    time2 = io->msToTicks( duration );

    bool res;

    if ( io->isOpen() )
    {
        res = io->set_meandr_raw( dacLow1, dacHigh1, time1,
                                  dacLow2, dacHigh2, time2 );
        if ( !res )
            return;
        mainWnd->oscWnd()->updateHdwOsc( false, (ui.lowTime->value() + ui.highTime->value())/1000.0 );
    }
}




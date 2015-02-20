
#include "oscilloscope_wnd.h"

OscilloscopeWnd::OscilloscopeWnd( QWidget * parent )
    : QMainWindow( parent )
{
    ui.setupUi( this );
    ui.plot->show();
    this->io = io;
}

OscilloscopeWnd::~OscilloscopeWnd()
{

}

bool OscilloscopeWnd::isRunning() const
{

}

void OscilloscopeWnd::setIo( VoltampIo * io )
{
    this->io = io;
}

void OscilloscopeWnd::slotRun()
{

}

void OscilloscopeWnd::slotF_t()
{

}

void OscilloscopeWnd::slotI_v()
{

}

void OscilloscopeWnd::slotNewData()
{

}



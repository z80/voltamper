
#include "oscilloscope_wnd.h"

OscilloscopeWnd::OscilloscopeWnd( VoltampIo * io, QWidget * parent )
    : QMainWindow( parent )
{
    ui.setupUi( this );
    this->io = io;
}

OscilloscopeWnd::~OscilloscopeWnd()
{

}

bool OscilloscopeWnd::isRunning() const
{

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



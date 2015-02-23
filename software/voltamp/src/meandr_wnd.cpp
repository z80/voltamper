
#include "meandr_wnd.h"

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

void MeandrWnd::setIo( VoltampIo * io )
{
    this->io = io;
}

void MeandrWnd::slotApply()
{
    // I'm too lazy to fill this method with valid code for now.
}




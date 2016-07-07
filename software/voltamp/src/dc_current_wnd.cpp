
#include "dc_current_wnd.h"
#include "main_wnd.h"

DcCurrentWnd::DcCurrentWnd( QWidget * parent )
    : QWidget( parent )
{
    ui.setupUi( this );
    io = 0;

    connect( ui.value, SIGNAL(valueChanged(double)), this, SLOT(slotChange()) );
    connect( ui.value, SIGNAL(editingFinished()),    this, SLOT(slotApply()) );
}

DcCurrentWnd::~DcCurrentWnd()
{

}

void DcCurrentWnd::setIo( VoltampIo * io, MainWnd * mainWnd )
{
    this->io = io;
    this->mainWnd = mainWnd;

    qreal vmin = mainWnd->iAux( 0 );
    qreal vmax = mainWnd->iAux( 65535 );

    ui.value->setRange( vmin, vmax );
}

void DcCurrentWnd::slotChange()
{
    QString ss = "background-color: rgb(185, 10, 10);\nfont: 75 22pt \"MS Shell Dlg 2\";\nborder-color: rgb(185, 10, 10);";
    ui.value->setStyleSheet( ss );
}

void DcCurrentWnd::slotApply()
{
    qreal current = ui.value->value();
    int adc;
    mainWnd->iadc( current, adc );
    if ( io->isOpen() )
    {
        bool res = io->setCurrent( adc );
        if ( !res )
            return;
        QString ss = "background-color: rgb(10, 185, 10);\nfont: 75 22pt \"MS Shell Dlg 2\";\nborder-color: rgb(10, 185, 10);";
        ui.value->setStyleSheet( ss );
    }
}




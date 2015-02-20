
#include "main_wnd.h"


MainWnd::MainWnd( QWidget * parent )
    : QMainWindow( parent )
{
    ui.setupUi( this );
    ui.osc->show();
    io = new VoltampIo();

    QVBoxLayout * bl = new QVBoxLayout( ui.osc );
    osc = new OscilloscopeWnd( this );
    bl->addWidget( osc );
    osc->setIo( io );

    dcWnd = new DcVoltageWnd( 0 );
    spWnd = new SinglePulseWnd( 0 );
    mrWnd = new MeandrWnd( 0 );

    connect( ui.actionDC_Volt,      SIGNAL(triggered()), this, SLOT(slotDc()) );
    connect( ui.actionSingle_pulse, SIGNAL(triggered()), this, SLOT(slotSinglePulse()) );
    connect( ui.actionMeandr,       SIGNAL(triggered()), this, SLOT(slotMeandr()) );
}

MainWnd::~MainWnd()
{
    delete io;
}

void MainWnd::slotQuit()
{
    this->deleteLater();
    qApp->quit();
}

void MainWnd::slotReopen()
{
    io->close();
    bool res = io->open();
    if ( res )
        setTitle( "device connected" );
    else
        setTitle( "no device" );
}

void MainWnd::slotAbout()
{
    QMessageBox::about( this, "Hell", "On Earth!" );
}

void MainWnd::slotDc()
{
    dcWnd->show();
}
void MainWnd::slotSinglePulse()
{
    spWnd->show();
}

void MainWnd::slotMeandr()
{
    mrWnd->show();
}

void MainWnd::setTitle( const QString & stri )
{
    setWindowTitle( QString( "Potentiostat: %1" ).arg( stri ) );
}





#include "main_wnd.h"


MainWnd::MainWnd( QWidget * parent )
    : QMainWindow( parent )
{
    ui.setupUi( this );
    //ui.osc->show();

    statusLabel = new QLabel( ui.statusbar );
    ui.statusbar->addWidget( statusLabel );


    io = new VoltampIo();

    QVBoxLayout * bl = new QVBoxLayout( ui.osc );
    osc = new OscilloscopeWnd( this );
    bl->addWidget( osc );
    osc->setIo( io );

    dcWnd = new DcVoltageWnd( 0 );
    dcWnd->setIo( io );

    spWnd = new SinglePulseWnd( 0 );
    spWnd->setIo( io );

    mrWnd = new MeandrWnd( 0 );
    mrWnd->setIo( io );

    connect( ui.action_Quit,  SIGNAL(triggered()), this, SLOT(slotQuit()) );
    connect( ui.actionOpen,   SIGNAL(triggered()), this, SLOT(slotReopen()) );
    connect( ui.action_About, SIGNAL(triggered()), this, SLOT(slotAbout()) );

    connect( ui.actionDC_Volt,      SIGNAL(triggered()), this, SLOT(slotDc()) );
    connect( ui.actionSingle_pulse, SIGNAL(triggered()), this, SLOT(slotSinglePulse()) );
    connect( ui.actionMeandr,       SIGNAL(triggered()), this, SLOT(slotMeandr()) );
}

MainWnd::~MainWnd()
{
    delete io;
}

qreal MainWnd::v( quint16 adc )
{
    return 0.0;
}

qreal MainWnd::i( quint16 adc )
{
    return 0.0;
}

void  MainWnd::dac( qreal v, int & dacLow, int & dacHigh )
{
    dacLow  = 2047;
    dacHigh = 2047;
}

void MainWnd::setStatus( quint16 eaux, quint16 eref, quint16 iaux )
{
    QString stri = QString( "EAUX %1, EREF %2, IAUX %3" ).arg( eaux, eref, iaux );
    statusLabel->setText( stri );
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

void MainWnd::slotShortRelay()
{
    bool en = ui.actionShort_relay->isChecked();
    io->set_sc_relay( en );
}

void MainWnd::slotOutRelay()
{
    bool en = ui.actionOut_relay->isChecked();
    io->set_out_relay( en );
}

void MainWnd::setTitle( const QString & stri )
{
    setWindowTitle( QString( "Potentiostat: %1" ).arg( stri ) );
}




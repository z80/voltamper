
#include "main_wnd.h"

const QString MainWnd::SETTINGS_INI = "./settings.ini";

MainWnd::MainWnd( QWidget * parent )
    : QMainWindow( parent )
{
    ui.setupUi( this );
    //ui.osc->show();

    statusLabel = new QLabel( ui.statusbar );
    ui.statusbar->addWidget( statusLabel );

    io = new VoltampIo();

    loadSettings();
    refreshDevicesList();

    QVBoxLayout * bl = new QVBoxLayout( ui.osc );
    osc = new OscilloscopeWnd( this );
    bl->addWidget( osc );
    osc->setIo( io, this );

    dcWnd = new DcVoltageWnd( 0 );
    dcWnd->setIo( io, this );

    spWnd = new SinglePulseWnd( 0 );
    spWnd->setIo( io, this );

    mrWnd = new MeandrWnd( 0 );
    mrWnd->setIo( io, this );

    swWnd = new SweepWnd( 0 );
    swWnd->setIo( io, this );

    calibrationWnd = new CalibrationWnd( 0 );
    calibrationWnd->setIo( io, this, osc );

    connect( ui.action_Quit,  SIGNAL(triggered()), this, SLOT(slotQuit()) );
    //connect( ui.actionOpen,   SIGNAL(triggered()), this, SLOT(slotReopen()) );
    connect( ui.action_About, SIGNAL(triggered()), this, SLOT(slotAbout()) );

    connect( ui.actionDC_Volt,      SIGNAL(triggered()), this, SLOT(slotDc()) );
    connect( ui.actionSingle_pulse, SIGNAL(triggered()), this, SLOT(slotSinglePulse()) );
    connect( ui.actionMeandr,       SIGNAL(triggered()), this, SLOT(slotMeandr()) );
    connect( ui.actionSweep,        SIGNAL(triggered()), this, SLOT(slotSweep()) );

    connect( ui.actionCalibration,  SIGNAL(triggered()), this, SLOT(slotCalibration()) );
}

MainWnd::~MainWnd()
{
    delete io;
}

qreal MainWnd::vAux( quint16 adc )
{
    return static_cast<qreal>( adc ) * aAdcAux + bAdcAux;
}

qreal MainWnd::vRef( quint16 adc )
{
    return static_cast<qreal>( adc ) * aAdcRef + bAdcRef;
}

qreal MainWnd::iAux( quint16 adc )
{
    return static_cast<qreal>( adc ) * aAdcI + bAdcI;
}

void  MainWnd::dac( qreal v, int & dacLow, int & dacHigh )
{
    qreal fLow = 2047.0;
    qreal fHigh = (v - bDac - fLow * aDacLow ) / aDacHigh;
    fLow = (v - bDac - fHigh*aDacHigh)/aDacLow;
    dacLow  = static_cast<int>( fLow );
    dacHigh = static_cast<int>( fHigh );
}

int MainWnd::timeToTicks( qreal time )
{
    int res = static_cast<int>( time );
    return res;
}

void MainWnd::setStatus( quint16 eaux, quint16 eref, quint16 iaux )
{
    QString stri = QString( "EAUX %1, EREF %2, IAUX %3" ).arg( eaux, eref, iaux );
    statusLabel->setText( stri );
}

void MainWnd::setRelays( bool shortRelay, bool outRelay )
{
    ui.actionShort_relay->setChecked( shortRelay );
    ui.actionOut_relay->setChecked( outRelay );
    slotShortRelay();
    slotOutRelay();
}

void MainWnd::setCalibrationDac( qreal aLow, qreal aHigh, qreal b )
{
    aDacLow  = aLow;
    aDacHigh = aHigh;
    bDac     = b;
}

void MainWnd::setCalibrationAdcVolt( qreal aAux, qreal bAux, qreal aRef, qreal bRef )
{
    aAdcAux = aAux;
    bAdcAux = bAux;
    aAdcRef = aRef;
    bAdcRef = bRef;

    saveSettings();
}

void MainWnd::setCalibrationAdcCurr( qreal aI, qreal bI )
{
    aAdcI = aI;
    bAdcI = bI;

    saveSettings();
}

void MainWnd::loadSettings()
{
    QSettings s( SETTINGS_INI, QSettings::IniFormat );

    devName  = s.value( "devName",  "0" ).toInt();

    aDacLow  = s.value( "aDacLow",  1.0 ).toDouble();
    aDacHigh = s.value( "aDacHigh", 1.0 ).toDouble();
    bDac     = s.value( "bDac",     -2047.0 ).toDouble();
    aAdcAux  = s.value( "aAdcAux",  1.0 ).toDouble();
    bAdcAux  = s.value( "bAdcAux",  -2047.0 ).toDouble();
    aAdcRef  = s.value( "aAdcRef",  1.0 ).toDouble();
    bAdcRef  = s.value( "bAdcRef",  -2047.0 ).toDouble();
    aAdcI    = s.value( "aAdcI",    1.0 ).toDouble();
    bAdcI    = s.value( "bAdcI",    -2047.0 ).toDouble();
}

void MainWnd::saveSettings()
{
    QSettings s( SETTINGS_INI, QSettings::IniFormat );

    s.setValue( "devName", devName );

    s.setValue( "aDacLow",  aDacLow );
    s.setValue( "aDacHigh", aDacHigh );
    s.setValue( "bDac",     bDac );
    s.setValue( "aAdcAux",  aAdcAux );
    s.setValue( "bAdcAux",  bAdcAux );
    s.setValue( "aAdcRef",  aAdcRef );
    s.setValue( "bAdcRef",  bAdcRef );
    s.setValue( "aAdcI",    aAdcI );
    s.setValue( "bAdcI",    bAdcI );
}

int MainWnd::deviceName() const
{
    return devName;
}

void MainWnd::slotQuit()
{
    this->deleteLater();
    qApp->quit();
}

void MainWnd::slotReopen()
{
    io->close();
    bool res = io->open( devName );
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

void MainWnd::slotSweep()
{
    swWnd->show();
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

void MainWnd::slotCalibration()
{
    calibrationWnd->show();
}

void MainWnd::slotDevice()
{
    foreach( QAction * a, devicesList )
        a->setChecked( false );
    QAction * a = qobject_cast<QAction *>( sender() );
    int index = devicesList.indexOf( a );
    bool res = io->open( index );
    a->setChecked( res );
    devName = index;
}

void MainWnd::setTitle( const QString & stri )
{
    setWindowTitle( QString( "Potentiostat: %1" ).arg( stri ) );
}

void MainWnd::refreshDevicesList()
{
    foreach( QAction * a, devicesList )
        a->deleteLater();
    devicesList.clear();
    QStringList l = io->enumDevices();
    foreach( QString stri, l )
    {
        QAction * a = new QAction( stri, ui.menuDevice );
        ui.menuDevice->addAction( a );
        a->setCheckable( true );
        connect( a, SIGNAL(triggered()), this, SLOT(slotDevice()) );
        devicesList.append( a );
    }
}






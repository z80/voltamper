
#include "dc_current_wnd.h"
#include "main_wnd.h"

DcCurrentWnd::DcCurrentWnd( QWidget * parent )
    : QWidget( parent )
{
    ui.setupUi( this );
    io = 0;

    connect( ui.value, SIGNAL(valueChanged(double)), this, SLOT(slotChange()) );
    connect( ui.set,   SIGNAL(clicked()),            this, SLOT(slotApply()) );

    setWindowFlags( Qt::Tool | Qt::WindowStaysOnTopHint );
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

class Sleep: public QThread
{
public:
    Sleep( QObject * p = 0 );
    ~Sleep();

    static void msleep( int ms = 1 )
    {
        QThread::msleep( ms );
    }

};

void DcCurrentWnd::slotApply()
{
    qreal current = ui.value->value();
    int adc;
    if ( io->isOpen() )
    {
        bool res = io->set_sc_relay( true );
        res = io->set_out_relay( false );
        // Set zero voltage.
        int dacLow, dacHigh;
        mainWnd->dac( 0.0, dacLow, dacHigh );
        res = io->set_dac_raw( dacLow, dacHigh );
        // Measure current value.
        int eaux, eref, iaux;
        qreal I = 0.0;
        const int N = 128;
        for ( auto i=0; i<N; i++ )
        {
            mainWnd->osc->mostRecentValsRaw( eaux, eref, iaux );
            I += static_cast<qreal>( iaux );
            qApp->processEvents();
            Sleep::msleep( 10 );
        }
        I /= static_cast<qreal>( N );
        // Adjust current calibration.
        // 0 = a*adc + b
        // b = -a*adc
        mainWnd->bAdcI = -mainWnd->aAdcI*I;

        // Turn out on (at zero voltage).
        res = io->set_out_relay( true );
        // Set zero current.
        mainWnd->iadc( 0.0, adc );
        res = io->setCurrent( adc );

        // Turn short circuit off.
        res = io->set_sc_relay( false );

        // Set desired current.
        mainWnd->iadc( current, adc );
        res = io->setCurrent( adc );

        mainWnd->setVisualRelays( false, true );
        if ( !res )
            return;
        QString ss = "background-color: rgb(10, 185, 10);\nfont: 75 22pt \"MS Shell Dlg 2\";\nborder-color: rgb(10, 185, 10);";
        ui.value->setStyleSheet( ss );
        //mainWnd->oscWnd()->updateHdwOsc( true );
    }
}




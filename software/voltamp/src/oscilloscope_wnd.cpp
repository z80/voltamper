
#include <QtConcurrent/QtConcurrentRun>
#include "oscilloscope_wnd.h"
#include "main_wnd.h"

#include "osc_scaler.h"
#include "qwt_plot.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot_layout.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_curve.h"

#include <boost/bind.hpp>
#include <boost/bind/arg.hpp>
#include <boost/bind/placeholders.hpp>

const int OscilloscopeWnd::CURVES_CNT = 10;
const int OscilloscopeWnd::PTS_CNT = 128;

OscilloscopeWnd::OscilloscopeWnd( QWidget * parent )
    : QMainWindow( parent ), 
    periodicSem( 1 )
{
    curveType = EREF_T;
    period    = T_10s;
    lastPeriod = 10.0;
    lastPtsCnt = PTS_CNT;
    continuousOsc = true;

    lastEaux = 0.0;
    lastEref = 0.0;
    lastIaux = 0.0;

    lastEauxRaw = 2047;
    lastErefRaw = 2047;
    lastIauxRaw = 2047;

    bufferEaux = bufferEref = bufferIaux = false;

    ui.setupUi( this );
    //ui.plot->show();

    COscScaler * scaler = new COscScaler( ui.plot );
    scaler->setWheelZoomX( true );
    scaler->setWheelZoomY( true );
    scaler->setEqualScales( false );
    scaler->setSaveScales( false );

    QwtPlotGrid * g = new QwtPlotGrid();
    g->enableXMin( true );
    g->enableYMin( true );
    g->setPen( QPen( Qt::gray, 0.0, Qt::DotLine ) );
    g->attach( ui.plot );

    g = new QwtPlotGrid();
    g->enableX( true );
    g->enableY( true );
    g->setPen( QPen( Qt::gray, 0.0, Qt::SolidLine ) );
    g->attach( ui.plot );


    qobject_cast<QwtPlotCanvas *>(ui.plot->canvas())->setBorderRadius( 10 );
    ui.plot->plotLayout()->setAlignCanvasToScales( true );

    // Nice background coloration.
    QPalette pal = ui.plot->canvas()->palette();
    QLinearGradient gr( 0.0, 0.0, 1.0, 1.0 );
    gr.setCoordinateMode( QGradient::StretchToDeviceMode );
    gr.setColorAt( 0.0, QColor( 200, 200, 230 ) );
    gr.setColorAt( 1.0, QColor( 230, 230, 250 ) );
    pal.setBrush( QPalette::Window, QBrush( gr ) );
    ui.plot->canvas()->setPalette( pal );

    connect( this, SIGNAL(sigReplot()),        this, SLOT(slotReplot()),        Qt::QueuedConnection );
    connect( this, SIGNAL(sigStartNewCurve()), this, SLOT(slotStartNewCurve()), Qt::QueuedConnection );
    terminate = false;
    this->io = 0;
    future = QtConcurrent::run( boost::bind( &OscilloscopeWnd::measure, this ) );

    connect( ui.actionE_AUX, SIGNAL(triggered()), this, SLOT(slotCurveType()) );
    connect( ui.actionE_REF, SIGNAL(triggered()), this, SLOT(slotCurveType()) );
    connect( ui.actionI_AUX, SIGNAL(triggered()), this, SLOT(slotCurveType()) );
    connect( ui.actionI_EREF, SIGNAL(triggered()), this, SLOT(slotCurveType()) );
    connect( ui.actionI_EAUX, SIGNAL(triggered()), this, SLOT(slotCurveType()) );

    connect( ui.actionT_1s,  SIGNAL(triggered()), this, SLOT(slotPeriod()) );
    connect( ui.actionT_10s, SIGNAL(triggered()), this, SLOT(slotPeriod()) );
    connect( ui.actionT_1m,  SIGNAL(triggered()), this, SLOT(slotPeriod()) );
    connect( ui.actionT_10m, SIGNAL(triggered()), this, SLOT(slotPeriod()) );

    curvesCntChanged();
    curveSizeChanged();
}

OscilloscopeWnd::~OscilloscopeWnd()
{
    stop();
}

bool OscilloscopeWnd::isRunning() const
{
    return true;
}

void OscilloscopeWnd::setIo( VoltampIo * io, MainWnd * mainWnd )
{
    mutex.lock();
        this->io      = io;
    mutex.unlock();
    this->mainWnd = mainWnd;
}

void OscilloscopeWnd::mostRecentVals( qreal & eaux, qreal & eref, qreal & iaux )
{
    QMutexLocker lock( &mutex );
        eaux = lastEaux;
        eref = lastEref;
        iaux = lastIaux;
}

void OscilloscopeWnd::mostRecentValsRaw( int & eaux, int & eref, int & iaux )
{
    QMutexLocker lock( &mutex );
        eaux = lastEauxRaw;
        eref = lastErefRaw;
        iaux = lastIauxRaw;
}

void OscilloscopeWnd::stop()
{
    mutex.lock();
        terminate = true;
    mutex.unlock();
    future.waitForFinished();
}

void OscilloscopeWnd::updateHdwOsc( bool continuous, qreal sweepT )
{
    continuousOsc = continuous;

    if ( sweepT > 0.0 )
        lastPeriod = sweepT;
    else
    {
        switch ( period )
        {
           case T_1s:
               lastPeriod = 1.0;
               break;
           case T_10s:
               lastPeriod = 10.0;
               break;
           case T_1m:
               lastPeriod = 60.0;
               break;
           default:
               lastPeriod = 10.0;
        }
    }
    lastPtsCnt = PTS_CNT; 

    qreal scale = static_cast<qreal>( lastPeriod ) / static_cast<qreal>( lastPtsCnt-1 );
    timeScale = scale;

    if ( io->isOpen() )
    {
        bool res;
        res = io->osc_set_period( lastPeriod, lastPtsCnt );
        if ( !res )
            return;
        res = io->setContinuousOsc( continuousOsc );
        if ( !res )
            return;
        // Start osc just in case if it was stopped.
        res = io->startOsc();
    }

    curveSizeChanged();
    curvesCntChanged();

    paintDataX.clear();
    paintDataY.clear();
    mutex.lock();
        iaux.clear();
        eaux.clear();
        eref.clear();
    mutex.unlock();
}

void OscilloscopeWnd::slotTimeout()
{
    if ( future.isRunning() )
        return;
    future = QtConcurrent::run( boost::bind( &OscilloscopeWnd::measure, this ) );
}

void OscilloscopeWnd::slotCurveType()
{
    do {
        QMutexLocker lock( &mutex );
            eaux.clear();
            eref.clear();
            iaux.clear();
    } while ( false );

    QAction * a = qobject_cast<QAction *>( this->sender() );
    if ( a == ui.actionE_AUX )
        curveType = EAUX_T;
    else if ( a == ui.actionE_REF )
        curveType = EREF_T;
    else if ( a == ui.actionI_AUX )
        curveType = IAUX_T;
    else if ( a == ui.actionI_EAUX )
        curveType = I_EAUX;
    else if ( a == ui.actionI_EREF )
        curveType = I_EREF;
    QList<QAction *> l;
    l.append( ui.actionE_AUX );
    l.append( ui.actionE_REF );
    l.append( ui.actionI_AUX );
    l.append( ui.actionI_EREF );
    l.append( ui.actionI_EAUX );
    for ( QList<QAction *>::iterator i=l.begin(); i!=l.end(); i++ )
    {
        QAction * aa = *i;
        aa->setChecked( aa == a );
    }

    if ( io->isOpen() )
    {
        mutex.lock();
            bool continuous = continuousOsc;
        mutex.unlock();
        updateHdwOsc( continuous );
    }
}

void OscilloscopeWnd::slotPeriod()
{
    QAction * a = qobject_cast<QAction *>( this->sender() );
    qreal t = lastPeriod;
    if ( a == ui.actionT_1s )
    {
        period = T_1s;
        t = 1.0;
    }
    else if ( a == ui.actionT_10s )
    {
        period = T_10s;
        t = 10.0;
    }
    else if ( a == ui.actionT_1m )
    {
        period = T_1m;
        t = 60.0;
    }
    else if ( a == ui.actionT_10m )
    {
        period = T_10m;
        t = 600.0;
    }
    QList<QAction *> l;
    l.append( ui.actionT_1s );
    l.append( ui.actionT_10s );
    l.append( ui.actionT_1m );
    l.append( ui.actionT_10m );
    for ( QList<QAction *>::iterator i=l.begin(); i!=l.end(); i++ )
    {
        QAction * aa = *i;
        aa->setChecked( aa == a );

    }

    if ( io->isOpen() )
        updateHdwOsc( true, t );
}

void OscilloscopeWnd::slotReplot()
{
    mutex.lock();
        bool continuous = continuousOsc;
    mutex.unlock();
    if ( continuous )
        replotContinuous();
    else
        replotPeriodic();
}

void OscilloscopeWnd::slotStartNewCurve()
{
    for ( int j=(curves.size()-1); j>0; j-- )
        curves[j] = curves[j-1];

    // Plot curves.
    for ( int i=0; i<curves.size(); i++ )
        curves[i].prepare();
    // Update plot.
    ui.plot->replot();

    Curve & c = curves[0];
    c.cnt = 0;

    paintDataX.clear();
    paintDataY.clear();
    mutex.lock();
        iaux.clear();
        eaux.clear();
        eref.clear();
    mutex.unlock();

    periodicSem.release();

    qDebug() << "started new curve";
}

class Msleep: public QThread
{
public:
    static void msleep( int ms )
    {
        QThread::msleep( ms );
    }
};

void OscilloscopeWnd::measure()
{
    bool term = false;
    do {
        VoltampIo * io;
        mutex.lock();
            io = this->io;
            bool isContinuousOsc = continuousOsc;
        mutex.unlock();
        if ( io )
        {
            if ( !io->isOpen() )
            {
                reopen();
                Msleep::msleep( 100 );
                continue;
            }
            if ( isContinuousOsc )
                measureContinuous( io );
            else
                measurePeriodic( io );
        }
        else
            Msleep::msleep( 100 );
        mutex.lock();
            term = terminate;
        mutex.unlock();
    } while ( !term );
}

void OscilloscopeWnd::reopen()
{
    io->close();
    io->open( mainWnd->deviceName() );
}

void OscilloscopeWnd::curveSizeChanged()
{
    int cnt = lastPtsCnt;

    int curvesCnt = curves.size();
    for ( int i=0; i<curvesCnt; i++ )
    {
        Curve & c = curves[i];
        c.x.resize( cnt );
        c.y.resize( cnt );
        c.cnt = 0;
    }
}

void OscilloscopeWnd::curvesCntChanged()
{
    const QColor front( Qt::darkGreen );
    QColor back( 230, 230, 250 );
    int r1 = front.red();
    int g1 = front.green();
    int b1 = front.blue();
    int r2 = back.red();
    int g2 = back.green();
    int b2 = back.blue();
    int cnt = CURVES_CNT;
    curves.resize( cnt );

    for ( int i=0; i<cnt; i++ )
    {
        curves[i].attach( ui.plot );
        int r, g, b;
        if ( cnt > 1 )
        {
            r = ((cnt-i-1) * r1 + i * r2)/(cnt-1);
            g = ((cnt-i-1) * g1 + i * g2)/(cnt-1);
            b = ((cnt-i-1) * b1 + i * b2)/(cnt-1);
        }
        else
        {
            r = r1;
            g = g1;
            b = b1;
        }
        QPen pen;
        QColor color( r, g, b );
        pen.setColor( color );
        if ( i == 0 )
        {
            pen.setWidth( 3 );
            pen.setStyle( Qt::SolidLine );
            curves[i].curve->setZ( 100.0 );
        }
        else
        {
            pen.setWidth( 3 );
            pen.setStyle( Qt::DotLine );
            curves[i].curve->setZ( 90.0 );
        }
        curves[i].curve->setPen( pen );
    }
    ui.plot->replot();
}

void OscilloscopeWnd::copyData( QQueue<qreal> & src, QQueue<qreal> & dest, int cnt )
{
    for ( int i=0; i<cnt; i++ )
        dest.enqueue( src.dequeue() );
}

void OscilloscopeWnd::measureContinuous(VoltampIo * io)
{
    mutex.lock();
        CurveType curveType = this->curveType;
    mutex.unlock();
    bool res;
    res = io->osc_eaux( eaux_m );
    int szEaux = eaux_m.size();
    if ( !res )
    {
        reopen();
        Msleep::msleep( 100 );
        return;
    }

    res = io->osc_eref( eref_m );
    int szEref = eref_m.size();
    if ( !res )
    {
        reopen();
        Msleep::msleep( 100 );
        return;
    }

    res = io->osc_iaux( iaux_m );
    int szIaux = iaux_m.size();
    if ( !res )
    {
        reopen();
        Msleep::msleep( 100 );
        return;
    }

    mutex.lock();
        for ( int i=0; i<eaux_m.size(); i++ )
            eaux.enqueue( mainWnd->vAux( eaux_m[i] ) );
        for ( int i=0; i<eref_m.size(); i++ )
            eref.enqueue( mainWnd->vRef( eref_m[i] ) );
        for ( int i=0; i<iaux_m.size(); i++ )
            iaux.enqueue( mainWnd->iAux( iaux_m[i] ) );
        lastEaux = (eaux.size() > 0) ? eaux.head() : 0.0;
        lastEref = (eref.size() > 0) ? eref.head() : 0.0;
        lastIaux = (iaux.size() > 0) ? iaux.head() : 0.0;
        lastEauxRaw = ( eaux_m.size() > 0 ) ? eaux_m.at( eaux_m.size() - 1 ) : 2047;
        lastErefRaw = ( eref_m.size() > 0 ) ? eref_m.at( eref_m.size() - 1 ) : 2047;
        lastIauxRaw = ( iaux_m.size() > 0 ) ? iaux_m.at( iaux_m.size() - 1 ) : 2047;
        int paintSz = iaux.size() + eref.size() + iaux.size();
    mutex.unlock();

    int sleepSz = szEaux + szEref + szIaux;

    if ( paintSz > 12 )
        emit sigReplot();
    if ( sleepSz < 30 )
        Msleep::msleep( 10 );
}

void OscilloscopeWnd::measurePeriodic(VoltampIo * io)
{
    int sz = 0;
    do {
        bool res;
        res = io->osc_eaux( eaux_m );
        res = io->osc_eref( eref_m );
        res = io->osc_iaux( iaux_m );
        sz = eaux_m.size() + eref_m.size() + iaux_m.size();
    } while ( sz > 0 );
    

    mutex.lock();
        eaux.clear();
        eref.clear();
        iaux.clear();
    mutex.unlock();

    bool res = io->startOsc();
    if ( !res )
        return;
    qDebug() << "started osc";

    int totalQty = 0;

    do {
        mutex.lock();
            CurveType curveType = this->curveType;
        mutex.unlock();
        bool res;
        res = io->osc_eaux( eaux_m );
        int szEaux = eaux_m.size();
        if ( !res )
        {
            reopen();
            Msleep::msleep( 100 );
            return;
        }

        res = io->osc_eref( eref_m );
        int szEref = eref_m.size();
        if ( !res )
        {
            reopen();
            Msleep::msleep( 100 );
            return;
        }

        res = io->osc_iaux( iaux_m );
        int szIaux = iaux_m.size();
        if ( !res )
        {
            reopen();
            Msleep::msleep( 100 );
            return;
        }

        mutex.lock();
            for ( int i=0; i<eaux_m.size(); i++ )
                eaux.enqueue( mainWnd->vAux( eaux_m[i] ) );
            for ( int i=0; i<eref_m.size(); i++ )
                eref.enqueue( mainWnd->vRef( eref_m[i] ) );
            for ( int i=0; i<iaux_m.size(); i++ )
                iaux.enqueue( mainWnd->iAux( iaux_m[i] ) );
            lastEaux = (eaux.size() > 0) ? eaux.head() : 0.0;
            lastEref = (eref.size() > 0) ? eref.head() : 0.0;
            lastIaux = (iaux.size() > 0) ? iaux.head() : 0.0;
            lastEauxRaw = ( eaux_m.size() > 0 ) ? eaux_m.at( eaux_m.size() - 1 ) : 2047;
            lastErefRaw = ( eref_m.size() > 0 ) ? eref_m.at( eref_m.size() - 1 ) : 2047;
            lastIauxRaw = ( iaux_m.size() > 0 ) ? iaux_m.at( iaux_m.size() - 1 ) : 2047;
            int paintSz = iaux.size() + eref.size() + iaux.size();
        mutex.unlock();

        int sleepSz = szEaux + szEref + szIaux;
        totalQty += sleepSz;

        if ( paintSz > 12 )
            emit sigReplot();
        if ( sleepSz < 30 )
            Msleep::msleep( 10 );

        bool stopped;
        res = io->oscStopped( stopped );

        if ( ( res ) && ( stopped ) && ( sleepSz == 0 ) && (totalQty > 0) )
        {
            qDebug() << "Total Qty: " << totalQty;
            break;
        }


        mutex.lock();
            bool term = terminate;
            bool cont = continuousOsc;
        mutex.unlock();
        if ( term || cont )
            return;
    } while ( true );

    periodicSem.acquire();
    emit sigStartNewCurve();

    periodicSem.acquire();
    periodicSem.release();
}

void OscilloscopeWnd::replotContinuous()
{
    // Choose what data to paint.
    mutex.lock();
        int sz;
        if ( curveType == I_EAUX )
        {
            sz = eaux.size();
            sz = (sz <= iaux.size() ) ? sz : iaux.size();
        }
        else if ( curveType == I_EREF )
        {
            sz = eref.size();
            sz = (sz <= iaux.size() ) ? sz : iaux.size();
        }
        else
        {
            sz = eaux.size();
            sz = (sz <= eref.size() ) ? sz : eref.size();
            sz = (sz <= iaux.size() ) ? sz : iaux.size();
        }

        // Copy to Lua.
        QQueue<qreal>::const_iterator ci;
        
        luaEaux.clear();
        luaEaux.reserve( sz );
        luaEref.clear();
        luaEref.reserve( sz );
        luaIaux.clear();
        luaIaux.reserve( sz );
        int ind = 0;
        for ( ci=eaux.begin(); ci!=eaux.end(); ci++ )
        {
            luaEaux.append( *ci );
            ind++;
            if ( ind >= sz )
                break;
        }
        ind = 0;
        for ( ci=eref.begin(); ci!=eref.end(); ci++ )
        {
            luaEref.append( *ci );
            ind++;
            if ( ind >= sz )
                break;
        }
        ind = 0;
        for ( ci=iaux.begin(); ci!=iaux.end(); ci++ )
        {
            luaIaux.append( *ci );
            ind++;
            if ( ind >= sz )
                break;
        }

        if ( curveType == EAUX_T )
            copyData( eaux, paintDataY, sz );
        else if ( curveType == EREF_T )
            copyData( eref, paintDataY, sz );
        else if ( curveType == IAUX_T )
            copyData( iaux, paintDataY, sz );
        else if ( curveType == I_EAUX )
        {
            copyData( iaux, paintDataY, sz );
            copyData( eaux, paintDataX, sz );
        }
        else if ( curveType == I_EREF )
        {
            copyData( iaux, paintDataY, sz );
            copyData( eref, paintDataX, sz );
        }
    mutex.unlock();


    Curve & c = curves[0];

    for ( int i=0; i<sz; i++ )
    {
        c.y[c.cnt] = paintDataY.dequeue();
        if ( curveType < I_EAUX )
            c.x[c.cnt] = timeScale * static_cast<qreal>( c.cnt );
        else
            c.x[c.cnt] = paintDataX.dequeue();
        c.cnt++;
        if ( c.cnt >= lastPtsCnt )
        {
            for ( int j=(curves.size()-1); j>0; j-- )
                curves[j] = curves[j-1];

            c.cnt = 0;
        }
    }

    // Plot curves.
    for ( int i=0; i<curves.size(); i++ )
        curves[i].prepare();
    // Update plot.
    ui.plot->replot();

    qreal leaux, leref, liaux;
    mostRecentVals( leaux, leref, liaux );
    // Set current values somewhere.
    mainWnd->setStatus( leaux, leref, liaux );

    // Invoke Lua algorithm by processing the data obtained.
    // When processing callback to speed up turn lua_hook off.
    mainWnd->lua_setHook( false );
        mainWnd->lua_invokeCallback( leref, liaux, leaux );
        mainWnd->lua_invokeCallbackFull( luaEref, luaIaux, luaEaux );
    mainWnd->lua_setHook( true );

    mutex.lock();
        eaux.clear();
        eref.clear();
        iaux.clear();
    mutex.unlock();
}

void OscilloscopeWnd::replotPeriodic()
{
    // Choose what data to paint.
    mutex.lock();
        int sz;
        if ( curveType == I_EAUX )
        {
            sz = eaux.size();
            sz = (sz <= iaux.size() ) ? sz : iaux.size();
        }
        else if ( curveType == I_EREF )
        {
            sz = eref.size();
            sz = (sz <= iaux.size() ) ? sz : iaux.size();
        }
        else
        {
            sz = eaux.size();
            sz = (sz <= eref.size() ) ? sz : eref.size();
            sz = (sz <= iaux.size() ) ? sz : iaux.size();
        }

        // Copy to Lua.
        QQueue<qreal>::const_iterator ci;
        
        luaEaux.clear();
        luaEaux.reserve( sz );
        luaEref.clear();
        luaEref.reserve( sz );
        luaIaux.clear();
        luaIaux.reserve( sz );
        int ind = 0;
        for ( ci=eaux.begin(); ci!=eaux.end(); ci++ )
        {
            luaEaux.append( *ci );
            ind++;
            if ( ind >= sz )
                break;
        }
        ind = 0;
        for ( ci=eref.begin(); ci!=eref.end(); ci++ )
        {
            luaEref.append( *ci );
            ind++;
            if ( ind >= sz )
                break;
        }
        ind = 0;
        for ( ci=iaux.begin(); ci!=iaux.end(); ci++ )
        {
            luaIaux.append( *ci );
            ind++;
            if ( ind >= sz )
                break;
        }

        if ( curveType == EAUX_T )
            copyData( eaux, paintDataY, sz );
        else if ( curveType == EREF_T )
            copyData( eref, paintDataY, sz );
        else if ( curveType == IAUX_T )
            copyData( iaux, paintDataY, sz );
        else if ( curveType == I_EAUX )
        {
            copyData( iaux, paintDataY, sz );
            copyData( eaux, paintDataX, sz );
        }
        else if ( curveType == I_EREF )
        {
            copyData( iaux, paintDataY, sz );
            copyData( eref, paintDataX, sz );
        }
    mutex.unlock();


    Curve & c = curves[0];

    for ( int i=0; i<sz; i++ )
    {
        if ( c.cnt < lastPtsCnt )
        {
            c.y[c.cnt] = paintDataY.dequeue();
            if ( curveType < I_EAUX )
                c.x[c.cnt] = timeScale * static_cast<qreal>( c.cnt );
            else
                c.x[c.cnt] = paintDataX.dequeue();
            c.cnt++;
        }
    }

    // Plot curves.
    for ( int i=0; i<curves.size(); i++ )
        curves[i].prepare();
    // Update plot.
    ui.plot->replot();

    qreal leaux, leref, liaux;
    mostRecentVals( leaux, leref, liaux );
    // Set current values somewhere.
    mainWnd->setStatus( leaux, leref, liaux );

    // Invoke Lua algorithm by processing the data obtained.
    // When processing callback to speed up turn lua_hook off.
    mainWnd->lua_setHook( false );
        mainWnd->lua_invokeCallback( leref, liaux, leaux );
        mainWnd->lua_invokeCallbackFull( luaEref, luaIaux, luaEaux );
    mainWnd->lua_setHook( true );

    mutex.lock();
        eaux.clear();
        eref.clear();
        iaux.clear();
    mutex.unlock();

    qDebug() << "replot";
}






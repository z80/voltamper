
#include "oscilloscope_wnd.h"

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
const int OscilloscopeWnd::PTS_CNT = 1024;

OscilloscopeWnd::OscilloscopeWnd( QWidget * parent )
    : QMainWindow( parent )
{
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


    //connect( this, SIGNAL(sigReplot()), this, SLOT(replot()), Qt::QueuedConnection );

    ui.plot->canvas()->setBorderRadius( 10 );
    ui.plot->plotLayout()->setAlignCanvasToScales( true );

    // Nice background coloration.
    QPalette pal = ui.plot->canvas()->palette();
    QLinearGradient gr( 0.0, 0.0, 1.0, 1.0 );
    gr.setCoordinateMode( QGradient::StretchToDeviceMode );
    gr.setColorAt( 0.0, QColor( 200, 200, 230 ) );
    gr.setColorAt( 1.0, QColor( 230, 230, 250 ) );
    pal.setBrush( QPalette::Window, QBrush( gr ) );
    ui.plot->canvas()->setPalette( pal );

    timer = new QTimer( this );
    timer->setInterval( 10 );
    connect( timer, SIGNAL(timeout()), this, SLOT(slotTimeout()) );

    curvesCntChanged();
}

OscilloscopeWnd::~OscilloscopeWnd()
{

}

bool OscilloscopeWnd::isRunning() const
{
    return false;
}

void OscilloscopeWnd::setIo( VoltampIo * io )
{
    this->io = io;
}

void OscilloscopeWnd::slotTimeout()
{
    if ( future.isRunning() )
        return;
    future = QtConcurrent::run( boost::bind( &OscilloscopeWnd::measure, this ) );
}

void OscilloscopeWnd::slotF_t()
{

}

void OscilloscopeWnd::slotI_v()
{

}

void OscilloscopeWnd::slotReplot()
{
    for ( int i=0; i<paintSz; i++ )
    {
        c.y[c.cnt++] = m_paintData[i];
        if ( c.cnt >= PTS_CNT )
        {
            for ( int j=(m_curves.size()-1); j>0; j-- )
                m_curves[j] = m_curves[j-1];

            c.cnt = 0;
            m_mutex.lock();
            for ( int j=i+1; j<paintSz; j++ )
                    m_data << m_paintData[j];
            m_mutex.unlock();
            break;
        }
    }



    for ( int i=0; i<m_curves.size(); i++ )
        m_curves[i].prepare();
    // Update plot.
    ui.plot->replot();

}

void OscilloscopeWnd::measure()
{
    if ( !io->isOpen() )
    {
        reopen();
        return;
    }
    bool res;
    res = io->osc_eaux( eaux_m );
    if ( !res )
    {
        reopen();
        return;
    }

    res = io->osc_eref( eref_m );
    if ( !res )
    {
        reopen();
        return;
    }

    res = io->osc_iaux( iaux_m );
    if ( !res )
    {
        reopen();
        return;
    }

    QMutexLocker lock( &mutex );
        eaux = eaux_m;
        eref = eref_m;
        iaux = iaux_m;
    emit sigReplot();
}

void OscilloscopeWnd::reopen()
{
    io->close();
    io->open();
}

void OscilloscopeWnd::curvesCntChanged()
{
    const QColor front( Qt::darkGreen );
    QColor back( 50, 50, 50 );
    int r1 = front.red();
    int g1 = front.green();
    int b1 = front.blue();
    int r2 = back.red();
    int g2 = back.green();
    int b2 = back.blue();
    int cnt = CURVES_CNT;
    m_curves.resize( cnt );

    for ( int i=0; i<cnt; i++ )
    {
        m_curves[i].attach( ui.plot );
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
            m_curves[i].curve->setZ( 100.0 );
        }
        else
        {
            pen.setWidth( 1 );
            m_curves[i].curve->setZ( 90.0 );
        }
        m_curves[i].curve->setPen( pen );
    }
    ui.plot->replot();
}






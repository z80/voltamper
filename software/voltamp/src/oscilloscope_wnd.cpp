
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

void OscilloscopeWnd::slotNewData()
{

}

void OscilloscopeWnd::measure()
{
    if ( !io->isOpen() )
    {
        reopen();
        return;
    }
    bool res;
    res = io->osc_eaux( data );
    if ( !res )
    {
        reopen();
        return;
    }

    res = io->osc_eref( data );
    if ( !res )
    {
        reopen();
        return;
    }

    res = io->osc_iaux( data );
    if ( !res )
    {
        reopen();
        return;
    }
}

void OscilloscopeWnd::reopen()
{
    io->close();
    io->open();
}



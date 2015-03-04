
#include "calibration_wnd.h"
#include "main_wnd.h"
#include "oscilloscope_wnd.h"

#include "matrix2.hpp"

CalibrationWnd::CalibrationWnd( QWidget * parent )
: QWidget( parent )
{
    ui.setupUi( this );
}

CalibrationWnd::~CalibrationWnd()
{

}

void CalibrationWnd::setIo( VoltampIo * io, MainWnd * mainWnd, OscilloscopeWnd * osc )
{
    this->io      = io;
    this->mainWnd = mainWnd;
    this->osc     = osc;
}

void CalibrationWnd::slotEnable()
{
    bool en = ui.mode->isChecked();
    ui.panel->setEnabled( en );
    if ( en )
    {
        dacLowV.clear();
        dacHighV.clear();
        adcAux.clear();
        adcRef.clear();
        dacLowI.clear();
        dacHighI.clear();
        adcI.clear();
        volt.clear();
        curr.clear();

        setRandomVolt();
    }
}

void CalibrationWnd::slotAddVolt()
{
    qreal v = ui.voltValue->value();
    volt.append( v );

    int eaux, eref, iaux;
    osc->mostRecentVals( eaux, eref, iaux );

    adcAux.append( eaux );
    adcRef.append( eref );

    dacLowV.append( dacLow );
    dacHighV.append( dacHigh );
}

void CalibrationWnd::slotAddCurr()
{
    qreal v = ui.currValue->value();
    curr.append( v );

    int eaux, eref, iaux;
    osc->mostRecentVals( eaux, eref, iaux );
    adcI.append( iaux );

    dacLowI.append( dacLow );
    dacHighI.append( dacHigh );
}

void CalibrationWnd::setRandomVolt()
{
    int range = ui.voltRange->value() * 2047 / 100;
    QTime t;
    int seed = t.msec() + (t.second() + (t.minute() + t.hour() * 24) * 60) * 1000;
    qsrand( seed );
    int dacLow  = qrand() * range / RAND_MAX + 2047;
    int dacHigh = qrand() * range / RAND_MAX + 2047;

    bool res = io->set_dac_raw( dacLow, dacHigh );
    if ( !res )
    {
        QMessageBox::critical( this, "Error", "Failed to set voltage!" );
        return;
    }

    this->dacLow  = dacLow;
    this->dacHigh = dacHigh;
}

void CalibrationWnd::calcDac2Volt()
{
    // Make linear assumption, e.i.
    //V = a*dacLow + b*dacHigh + c*1;
    Math::Matrix<> XtX;
    Math::Vector<> XtY;
    int sz = dacLowV.size();
    for ( int i=0; i<3; i++ )
    {
        QVector<int> * a;
        if ( i==0 )
            a = &dacLowV;
        else if ( i==1 )
            a = &dacHighV;
        else
            a = 0;
        for ( int j=0; j<3; j++ )
        {
            QVector<int> * b;
            if ( i==0 )
                b = &dacLowV;
            else if ( i==1 )
                b = &dacHighV;
            else
                b = 0;
            qreal v = 0.0;
            for ( int k=0; k<sz; k++ )
            {
                qreal va = ( a ) ? a->at( k ) : 1.0;
                qreal vb = ( b ) ? b->at( k ) : 1.0;
                v += va * vb;
            }
            XtX[i][j] = v;
        }

        qreal v = 0.0;
        for ( int k=0; k<sz; k++ )
        {
            qreal va = ( a ) ? a->at( k ) : 1.0;
            qreal vy = volt.at( k );
            v += va * vy;
        }
        XtY[i] = v;
    }
    // A = (XtX)^-1 * XtY;
    Math::Matrix<> invXtX;
    invXtX = XtX.inv();
    Math::Vector<> A;
    for ( int i=0; i<3; i++ )
    {
        qreal v = 0.0;
        for ( int j=0; j<3; j++ )
        {
            v += invXtX[i][j] * XtY[j];
        }
        A[i] = v;
    }
}

void CalibrationWnd::calcAdcAux2Volt()
{
    // Make linear assumption, e.i.
    //V = a*adc + b*1;
    Math::Matrix<2> XtX;
    Math::Vector<2> XtY;
    int sz = adcAux.size();
    for ( int i=0; i<2; i++ )
    {
        QVector<int> * a;
        if ( i==0 )
            a = &adcAux;
        else
            a = 0;
        for ( int j=0; j<2; j++ )
        {
            QVector<int> * b;
            if ( i==0 )
                b = &adcAux;
            else
                b = 0;
            qreal v = 0.0;
            for ( int k=0; k<sz; k++ )
            {
                qreal va = ( a ) ? a->at( k ) : 1.0;
                qreal vb = ( b ) ? b->at( k ) : 1.0;
                v += va * vb;
            }
            XtX[i][j] = v;
        }

        qreal v = 0.0;
        for ( int k=0; k<sz; k++ )
        {
            qreal va = ( a ) ? a->at( k ) : 1.0;
            qreal vy = volt.at( k );
            v += va * vy;
        }
        XtY[i] = v;
    }
    // A = (XtX)^-1 * XtY;
    Math::Matrix<2> invXtX;
    invXtX = XtX.inv();
    Math::Vector<2> A;
    for ( int i=0; i<2; i++ )
    {
        qreal v = 0.0;
        for ( int j=0; j<2; j++ )
        {
            v += invXtX[i][j] * XtY[j];
        }
        A[i] = v;
    }
}

void CalibrationWnd::calcCurr()
{

}



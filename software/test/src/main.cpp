
#include <QtGui>
#include "voltamp_io.h"

#include "qextserialport.h"


int main( int argc, char * argv[] )
{
    QApplication app( argc, argv );

    /*
    QextSerialPort * port;
    port = new QextSerialPort( "COM14" );
    port->setQueryMode( QextSerialPort::Polling );
    port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
    bool res = port->open( QIODevice::ReadWrite );
    if ( !res )
    {
        qDebug() << port->errorString();
        port->deleteLater();
        return -1;
    }

    while ( true )
    {
        char data[3];
        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        int cnt = port->write( const_cast<const char *>( data ), 1 );
        qDebug() << "Written " << cnt;
        cnt = port->read( data, 3 );
        qDebug() << "Read " << cnt;
    }*/
    
    VoltampIo io;
    bool res;
    QStringList l = io.enumDevices();
    qDebug() << l;
    res = io.open( 4 );
    if ( !res )
        return -1;
    QVector<quint16> data;
    QString stri;
    res = io.hardware_version( stri );
    qDebug() << stri;
    res = io.firmware_version( stri );
    qDebug() << stri;

    res = io.set_dac_raw( 1023, 1023 );
    res = io.set_sc_relay( true );
    res = io.set_sc_relay( false );
    res = io.set_out_relay( true );
    res = io.set_out_relay( false );

    io.close();
    
    return 0;
}


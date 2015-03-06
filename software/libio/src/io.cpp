
#include "io.h"
#include "qextserialport.h"


class Io::PD
{
public:
    PD()
    {
    }

    ~PD()
    {
    }

    QextSerialPort * ftdi;

    static const int TIMEOUT;
};

const int Io::PD::TIMEOUT = 3000;

Io::Io()
{
    pd = new PD();
    pd->ftdi = 0;
}

Io::~Io()
{
    delete pd;
}

/*
int Io::enumDevices()
{
    return 1;
}
*/

bool Io::open( const QString & dev )
{
    if ( pd->ftdi )
    {
        pd->ftdi->deleteLater();
    }
    QextSerialPort * port;
    port = new QextSerialPort(dev);
    port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
    pd->ftdi = port;
    bool res = port->open( QIODevice::ReadWrite );
    if ( !res )
    {
        port->deleteLater();
        pd->ftdi = 0;
    }
    return res;
}

bool Io::isOpen() const
{
    if ( !pd->ftdi )
        return false;
    bool res = pd->ftdi->isOpen();
    return res;

}

void Io::close()
{
    if ( pd->ftdi )
    {
        pd->ftdi->close();
        pd->ftdi->deleteLater();
    }
    pd->ftdi = 0;
}

int Io::write( quint8 * data, int dataSz )
{
    int cnt = pd->ftdi->write( reinterpret_cast<char *>( data ), dataSz );
    return cnt;
}

class Sleep: public QThread
{
public:
    Sleep()
        : QThread()
    {
    }

    ~Sleep()
    {
    }

    static void msleep( int ms )
    {
        QThread::msleep( ms );
    }
};

int Io::read( quint8 * data, int dataSz, bool tillTimeout )
{
    QTime t0 = QTime::currentTime();
    t0.start();
    int cnt;
    int totalCnt = 0;
    do {
        cnt = pd->ftdi->read( reinterpret_cast<char *>( &(data[totalCnt]) ), 1 );
        totalCnt += cnt;
        if ( ( tillTimeout ) && (cnt < 1) )
            Sleep::msleep( 1 );
    } while ( (cnt > 0) || ( (tillTimeout) && (t0.elapsed() < PD::TIMEOUT) ) );
    return cnt;
}



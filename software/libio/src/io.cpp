
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
};

Io::Io()
{
    pd = new PD();
    pd->ftdi = 0;
}

Io::~Io()
{
    delete pd;
}

int Io::enumDevices()
{
    return 1;
}

bool Io::open( int index )
{
    if ( pd->ftdi )
    {
        pd->ftdi->deleteLater();
    }
    QextSerialPort * port;
    port = new QextSerialPort("/dev/ttyUSB0");
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

int Io::read( quint8 * data, int dataSz )
{
    int cnt = pd->ftdi->read( reinterpret_cast<char *>( data ), dataSz );
    return cnt;
}



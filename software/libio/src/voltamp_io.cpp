
#include "voltamp_io.h"
#include "io.h"

class VoltampIo::PD
{
public:
    PD()
    {
    }

    ~PD()
    {
    }

    void encodeData( quint8 * data, int sz );
    Io * io;
    QByteArray buffer_raw;
    QByteArray buffer;

    static const int CMD_SET_ARGS;
    static const int CMD_EXEC_FUNC;
};

const int VoltampIo::PD::CMD_SET_ARGS  = 1;
const int VoltampIo::PD::CMD_EXEC_FUNC = 2;


void VoltampIo::PD::encodeData( quint8 * data, int sz )
{
    QByteArray & arr = buffer;
    arr.reserve( sz * 2 + 2 );
    arr.clear();
    for ( int i=0; i<sz; i++ )
    {
        arr.append( data[i] );
        if ( data[i] == '\\' )
            arr.append( '\\' );
    }
    arr.append( '\\' );
    arr.append( '\0' );
}

VoltampIo::VoltampIo()
{
    pd = new PD;
    pd->io = new Io();
}

VoltampIo::~VoltampIo()
{
    delete pd->io;
    delete pd;
}

bool VoltampIo::setArgs( quint8 * data, int dataSz )
{
    QByteArray & arr = pd->buffer_raw;
    arr.reserve( dataSz + 1 );
    arr.clear();
    quint8 cmd = static_cast<quint8>( PD::CMD_SET_ARGS );
    arr.append( *reinterpret_cast<char *>( &cmd ) );
    arr.append( reinterpret_cast<char *>(data), dataSz );
    pd->encodeData( reinterpret_cast<quint8 *>(arr.data()), arr.size() );
    int cnt = write( reinterpret_cast<quint8 *>( pd->buffer.data() ), pd->buffer.size() );
    return ( cnt == pd->buffer.size() );
}

int VoltampIo::readData( quint8 * data, int dataSz )
{
    int cnt = read( data, dataSz );
    return cnt;
}

bool VoltampIo::execFunc( quint16 funcId )
{
    QByteArray & arr = pd->buffer_raw;
    arr.reserve( 2 + 1 );
    arr.clear();
    quint8 cmd = static_cast<quint8>( PD::CMD_EXEC_FUNC );
    arr.append( *reinterpret_cast<char *>( &cmd ) );
    cmd = static_cast<quint8>( funcId && 0xFF );
    arr.append( cmd );
    cmd = static_cast<quint8>( (funcId >> 8) && 0xFF );
    arr.append( cmd );
    pd->encodeData( reinterpret_cast<quint8 *>(arr.data()), arr.size() );
    int cnt = write( reinterpret_cast<quint8 *>( pd->buffer.data() ), pd->buffer.size() );
    return ( cnt == pd->buffer.size() );
}

int VoltampIo::write( quint8 * data, int dataSz )
{
    pd->encodeData( data, dataSz );
    int cnt = pd->io->write( reinterpret_cast<quint8 *>( pd->buffer.data() ), pd->buffer.size() );
    return cnt;
}

int VoltampIo::read( quint8 * data, int dataSz )
{
    // Here will need to implement readint until end of message is met or timeout is met.
    quint8 one;
    bool slash = false;
    int ind = 0;
    while ( ind < dataSz )
    {
        int cnt = pd->io->read( &one, 1 );
        if ( cnt < 1 )
            break;
        if ( !slash )
        {
            if ( one == '\\' )
                slash = true;
            else
                data[ind++] = one;
        }
        else
        {
            if ( one == '\0' )
                return ind;
            else
            {
                data[ind++] = one;
                slash = false;
            }
        }
    }
    return ind;
}


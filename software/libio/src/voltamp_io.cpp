
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
    QMutex mutex;
    Io * io;
    QByteArray buffer_raw;
    QByteArray buffer;

    static const int CMD_SET_ARGS;
    static const int CMD_EXEC_FUNC;

    static const int TIMEOUT;
    static const int IN_BUFFER_SZ;
};

const int VoltampIo::PD::CMD_SET_ARGS  = 1;
const int VoltampIo::PD::CMD_EXEC_FUNC = 2;

const int VoltampIo::PD::TIMEOUT = 3000;
const int VoltampIo::PD::IN_BUFFER_SZ = (2* 2024);

void VoltampIo::PD::encodeData( quint8 * data, int sz )
{
    QByteArray & arr = buffer;
    arr.reserve( sz * 2 + 2 );
    arr.clear();
    for ( int i=0; i<sz; i++ )
    {
        if ( data[i] == '\\' )
            arr.append( '\\' );
        else if ( data[i] == '\0' )
            arr.append( '\\' );
    }
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

bool VoltampIo::open( const QString & devName )
{
    QMutexLocker lock( &pd->mutex );

    bool res = pd->io->open( devName );
    return res;
}

bool VoltampIo::isOpen() const
{
    QMutexLocker lock( &pd->mutex );

    bool res = pd->io->isOpen();
    return res;
}

void VoltampIo::close()
{
    QMutexLocker lock( &pd->mutex );

    pd->io->close();
}

bool VoltampIo::osc_eaux( QVector<quint16> & vals )
{
    QMutexLocker lock( &pd->mutex );

    quint8 funcInd = 0;
    bool res = execFunc( funcInd );
    if ( !res )
        return false;
    bool eom;
    QByteArray & arr = pd->buffer;
    arr.resize( PD::IN_BUFFER_SZ );
    int cnt = read( reinterpret_cast<quint8 *>( arr.data() ), arr.size(), eom );
    if ( !eom )
        return false;
    cnt /= 2;
    vals.resize( cnt );
    quint8 * b = reinterpret_cast<quint8 *>( arr.data() );
    for ( int i=0; i<cnt; i++ )
        vals[i] = static_cast<quint16>( (b[2*i]) ) + ( static_cast<quint16>( (b[2*i+1]) ) << 8 );
    return true;
}

bool VoltampIo::osc_eref( QVector<quint16> & vals )
{
    QMutexLocker lock( &pd->mutex );

    quint8 funcInd = 1;
    bool res = execFunc( funcInd );
    if ( !res )
        return false;
    bool eom;
    QByteArray & arr = pd->buffer;
    arr.resize( PD::IN_BUFFER_SZ );
    int cnt = read( reinterpret_cast<quint8 *>( arr.data() ), arr.size(), eom );
    if ( !eom )
        return false;
    cnt /= 2;
    vals.resize( cnt );
    quint8 * b = reinterpret_cast<quint8 *>( arr.data() );
    for ( int i=0; i<cnt; i++ )
        vals[i] = static_cast<quint16>( (b[2*i]) ) + ( static_cast<quint16>( (b[2*i+1]) ) << 8 );
    return true;
}

bool VoltampIo::osc_iaux( QVector<quint16> & vals )
{
    QMutexLocker lock( &pd->mutex );

    quint8 funcInd = 2;
    bool res = execFunc( funcInd );
    if ( !res )
        return false;
    bool eom;
    QByteArray & arr = pd->buffer;
    arr.resize( PD::IN_BUFFER_SZ );
    int cnt = read( reinterpret_cast<quint8 *>( arr.data() ), arr.size(), eom );
    if ( !eom )
        return false;
    cnt /= 2;
    vals.resize( cnt );
    quint8 * b = reinterpret_cast<quint8 *>( arr.data() );
    for ( int i=0; i<cnt; i++ )
        vals[i] = static_cast<quint16>( (b[2*i]) ) + ( static_cast<quint16>( (b[2*i+1]) ) << 8 );
    return true;
}

bool VoltampIo::osc_set_period( qreal secs, int per_pts )
{
    QMutexLocker lock( &pd->mutex );

    QByteArray & b = pd->buffer_raw;
    b.clear();
    b.reserve( 4 );

    quint32 ticks = static_cast<quint32>( secs * 24000000.0 / (3*28.5) / static_cast<qreal>( per_pts ) );

    quint8 v;
    v = static_cast<quint8>( ticks & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (ticks >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (ticks >> 16) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (ticks >> 24) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );

    bool res;
    res = setArgs( reinterpret_cast<quint8 *>( b.data() ), b.size() );
    if ( !res )
        return false;

    quint8 funcInd = 3;
    res = execFunc( funcInd );
    if ( !res )
        return false;

    return true;
}

bool VoltampIo::set_leds( int leds )
{
    QMutexLocker lock( &pd->mutex );

    quint8 v;
    v = static_cast<quint8>( leds & 0xFF );

    bool res;
    res = setArgs( &v, 1 );
    if ( !res )
        return false;

    quint8 funcInd = 4;
    res = execFunc( funcInd );
    if ( !res )
        return false;

    return true;
}

bool VoltampIo::set_out_relay( bool en )
{
    QMutexLocker lock( &pd->mutex );

    quint8 v;
    v = en ? 1 : 0;

    bool res;
    res = setArgs( &v, 1 );
    if ( !res )
        return false;

    quint8 funcInd = 5;
    res = execFunc( funcInd );
    if ( !res )
        return false;

    return true;
}

bool VoltampIo::set_sc_relay( bool en )
{
    QMutexLocker lock( &pd->mutex );

    quint8 v;
    v = en ? 1 : 0;

    bool res;
    res = setArgs( &v, 1 );
    if ( !res )
        return false;

    quint8 funcInd = 6;
    res = execFunc( funcInd );
    if ( !res )
        return false;

    return true;
}

bool VoltampIo::set_dac_raw( int dacLow, int dacHigh )
{
    QMutexLocker lock( &pd->mutex );

    QByteArray & b = pd->buffer_raw;
    b.clear();
    b.reserve( 4 );

    quint8 v;
    v = static_cast<quint8>( dacLow & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacLow >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( dacHigh & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacHigh >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );

    bool res;
    res = setArgs( reinterpret_cast<quint8 *>( b.data() ), b.size() );
    if ( !res )
        return false;

    quint8 funcInd = 7;
    res = execFunc( funcInd );
    if ( !res )
        return false;

    return true;
}

bool VoltampIo::set_one_pulse_raw( int dacLow, int dacHigh, int time )
{
    QMutexLocker lock( &pd->mutex );

    QByteArray & b = pd->buffer_raw;
    b.clear();
    b.reserve( 8 );

    quint8 v;
    v = static_cast<quint8>( dacLow & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacLow >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( dacHigh & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacHigh >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );

    quint32 t = static_cast<quint32>( time );
    v = static_cast<quint8>( t & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 16) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 24) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );

    bool res;
    res = setArgs( reinterpret_cast<quint8 *>( b.data() ), b.size() );
    if ( !res )
        return false;

    quint8 funcInd = 8;
    res = execFunc( funcInd );
    if ( !res )
        return false;

    return true;
}

bool VoltampIo::set_meandr_raw( int dacLow1, int dacHigh1, int time1, int dacLow2, int dacHigh2, int time2 )
{
    QMutexLocker lock( &pd->mutex );

    QByteArray & b = pd->buffer_raw;
    b.clear();
    b.reserve( 16 );

    quint8 v;
    v = static_cast<quint8>( dacLow1 & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacLow1 >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( dacHigh1 & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacHigh1 >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );

    quint32 t = static_cast<quint32>( time1 );
    v = static_cast<quint8>( t & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 16) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 24) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );

    v = static_cast<quint8>( dacLow2 & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacLow2 >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( dacHigh2 & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacHigh2 >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );

    t = static_cast<quint32>( time2 );
    v = static_cast<quint8>( t & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 16) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 24) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );

    bool res;
    res = setArgs( reinterpret_cast<quint8 *>( b.data() ), b.size() );
    if ( !res )
        return false;

    quint8 funcInd = 9;
    res = execFunc( funcInd );
    if ( !res )
        return false;

    return true;
}

bool VoltampIo::set_sweep_raw( int dacLow1, int dacHigh1, int dacLow2, int dacHigh2, int period )
{
    QMutexLocker lock( &pd->mutex );

    QByteArray & b = pd->buffer_raw;
    b.clear();
    b.reserve( 12 );

    quint8 v;
    v = static_cast<quint8>( dacLow1 & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacLow1 >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( dacHigh1 & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacHigh1 >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );

    v = static_cast<quint8>( dacLow2 & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacLow2 >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( dacHigh2 & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (dacHigh2 >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );

    quint32 t;
    t = static_cast<quint32>( period );
    v = static_cast<quint8>( t & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 8) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 16) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );
    v = static_cast<quint8>( (t >> 24) & 0xFF );
    b.append( *reinterpret_cast<char *>(&v) );

    bool res;
    res = setArgs( reinterpret_cast<quint8 *>( b.data() ), b.size() );
    if ( !res )
        return false;

    quint8 funcInd = 10;
    res = execFunc( funcInd );
    if ( !res )
        return false;

    return true;
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

bool VoltampIo::execFunc( quint8 funcId )
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

int VoltampIo::readData( quint8 * data, int dataSz )
{
    bool eom;
    int cnt = read( data, dataSz, eom );
    if ( !eom )
        return -1;
    return cnt;
}

int VoltampIo::write( quint8 * data, int dataSz )
{
    pd->encodeData( data, dataSz );
    int cnt = pd->io->write( reinterpret_cast<quint8 *>( pd->buffer.data() ), pd->buffer.size() );
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

int VoltampIo::read( quint8 * data, int dataSz, bool & eom )
{
    quint8 one;
    QTime t0 = QTime::currentTime();
    t0.start();
    bool slash = false;
    int ind = 0;
    while ( ( ind < dataSz ) && ( t0.elapsed() < PD::TIMEOUT ) )
    {
        int cnt = pd->io->read( &one, 1 );
        if ( cnt < 1 )
        {
            Sleep::msleep( 1 );
        }
        if ( !slash )
        {
            if ( one == '\\' )
                slash = true;
            else if ( one == '\\' )
            {
                eom = true;
                return ind;
            }
            else
                data[ind++] = one;
        }
        else
        {
            if ( one == '\0' )
            {
                data[ind++] = one;
                slash = false;
            }
        }
    }
    eom = false;
    return ind;
}


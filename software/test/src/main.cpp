
#include <QtCore>
#include "voltamp_io.h"



int main( int argc, char * argv[] )
{
    VoltampIo io;
    bool res;
    res = io.open();
    QVector<quint16> data;
    res = io.osc_set_period( 1, 5 );
    res = io.osc_eaux( data );
    io.close();

    return 0;
}


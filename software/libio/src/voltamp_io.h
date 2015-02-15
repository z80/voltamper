
#ifndef __VOLTAMP_IO_H_
#define __VOLTAMP_IO_H_

#include <QtCore>

class VoltampIo
{
public:
    VoltampIo();
    ~VoltampIo();

    bool setArgs( quint8 * data, int dataSz );
    int  readData( quint8 * data, int dataSz );
    bool execFunc( quint16 funcId );
protected:
    int write( quint8 * data, int dataSz );
    int read( quint8 * data, int dataSz );

private:
    class PD;
    PD * pd;
};


#endif



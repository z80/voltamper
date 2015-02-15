
#ifndef __LIB_IO_H_
#define __LIB_IO_H_

#include <QtCore>

class LibIo
{
public:
  LibIo();
  ~LibIo();

  int enumDevices();
  bool open( int index=0 );
  bool isOpen() const;
  void close();

  int write( quint8 * data, int dataSz );
  int read( quint8 * data, int dataSz );

private:
  class PD;
  PD * pd;
};

#endif

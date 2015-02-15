
#ifndef __IO_H_
#define __IO_H_

#include <QtCore>

class Io
{
public:
  Io();
  virtual ~Io();

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

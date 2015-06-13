
#ifndef __XMPP_TCP_PROXY_H_
#define __XMPP_TCP_PROXY_H_

#include <QtCore>
#include "QXmppClientExtension.h"
class QXmppClient;

class QXmppTcpProxy: public QXmppClientExtension
{
    Q_OBJECT
public:
    QXmppTcpProxy( int id = -1 );
    ~QXmppTcpProxy();

    void setInPipe( int id = -1 );
    void setOutPipe( const QString & jidDest, int localPort, int remotePort = -1, const QString & remoteHost = QString(), int id = -1 );
    void clearPipe();

    virtual bool handleStanza(const QDomElement &element);

protected slots:
    void serverNewConnection();
    void socketReadyRead();
private:
    class PD;
    PD * pd;
};


#endif





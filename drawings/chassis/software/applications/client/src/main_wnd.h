
#ifndef __MAIN_WND_H_
#define __MAIN_WND_H_

#include <QtGui>
#include "xmpp_io.h"
#include "xmpp_video.h"
#include "xmpp_msg_pipe.h"
#include "lua_machine.h"
#include "ui_main_wnd.h"

class MainWnd: public QMainWindow
{
	Q_OBJECT
public:
	MainWnd( QWidget * parent = 0 );
	~MainWnd();

signals:
    void sigLog( const QString & );
private slots:
    void slotLog( const QString & );
    void slotShowFullLog();
    void slotConnected();
    void slotDisconnected();
    void slotClearLog();
    void slotDontSleep();
    void slotDontSleepTimeout();
    void slotSetupPipe();

    // Controls
    void slotStatus();
    void slotOsc();
    void slotShutdown();
    void slotLight();
    void slotMotoEn();
    void slotForward();
    void slotBackward();
    void slotLeft();
    void slotRight();
    void slotStop();
protected:
    void keyPressEvent( QKeyEvent * event );
    void keyReleaseEvent( QKeyEvent * event );
private:
	void log( const std::string & stri );

    Ui_MainWnd  ui;
	QXmppPeer    * m_peer;
    QXmppVideo   * m_video;
    QXmppMsgPipe * m_pipe;
    QString        m_jidDest;

    QTimer       * m_dontSleepTimer;

    static const QString     CONFIG_FILE;
	static const int         LOG_MAX;
	static const int         MOTO_TIME_MAX; // Due to big ping in the case of fast movements
	                                          // it is necessary to be ablt
	                                          // to set moto time explicitly.
    static const int MOTO1,
                     MOTO2,
                     MOTO3,
                     MOTO4;
    QImage m_img;
public slots:
	void slotSend( const QString & stri );
    void qxmppMessageReceived( const QString & );
};



#endif




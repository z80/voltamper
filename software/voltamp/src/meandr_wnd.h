
#include <QtGui>
#include "ui_meandr_wnd.h"
#include "voltamp_io.h"


class MeandrWnd: public QWidget
{
    Q_OBJECT
public:
    MeandrWnd( QWidget * parent = 0 );
    ~MeandrWnd();

    void setIo( VoltampIo * io );

private slots:
    void slotApply();
private:
    Ui_MeandrWnd ui;
    VoltampIo * io;
};



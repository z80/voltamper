
#include <QtGui>
#include "main_wnd.h"

int main( int argc, char * argv[])
{
    QStringList paths = QApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    QApplication::setLibraryPaths(paths);

    QApplication app( argc, argv );

    MainWnd * mw = new MainWnd( 0 );
    mw->show();

    int res = app.exec();
    return res;
}





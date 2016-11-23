#include "notepad.h"
#include <QApplication>

/*
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPixmap pixmap(":/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    app.processEvents();
    ...
    QMainWindow window;
    window.show();
    splash.finish(&window);
    return app.exec();
}
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap("C:/Users/jiang_000.JIANG_PC/Documents/Qt/mynotepad/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();

    int foo = 1;
    for (int i = 0; i < 1000000000; ++i)
        ++foo;

    a.setStyle("fusion");
    Notepad w;
    w.show();

    splash.finish(&w);
    return a.exec();
}

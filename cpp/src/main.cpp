
#include <QApplication>
// #include "../inc/mainwindow.h"
#include "StartWin.h"



int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    StartWin w;
    w.show();

    return app.exec();
}

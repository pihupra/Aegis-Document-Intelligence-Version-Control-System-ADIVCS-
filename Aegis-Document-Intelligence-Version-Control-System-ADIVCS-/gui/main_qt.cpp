#include "mainwindow.h"
#include <QApplication>
#include "storage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Storage storage("aegis.db");
    MainWindow w(storage);
    w.show();

    return app.exec();
}

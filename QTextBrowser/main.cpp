#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

QString MainWindow::BaseUrl;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (argc < 2) {
        qInfo() << "Usage:" << argv[0] << "{link}";
        return 1;
    } else {

        MainWindow::BaseUrl = QString::fromUtf8(argv[1]);
        qDebug() << MainWindow::BaseUrl;
    }

    MainWindow window;
    window.show();

    return app.exec();
}

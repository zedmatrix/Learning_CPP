#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QTextCursor>
#include <QTextEdit>
#include <QLineEdit>
#include <QDateTime>
#include <QFile>
#include <QStatusBar>
#include <QLabel>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
namespace NetMan { class NetworkManager; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QString BaseUrl;
    QString searchTerm, statusMsg, statusError, msg, prefix, newUrl, check;

private slots:
    void handleResponse(const QByteArray& response);
    void handleError(const QString& errorString);
    void handleURL();
    void UpdateStatus();
    void Quit();
    void Home();

private:
    Ui::MainWindow *ui;
    NetMan::NetworkManager *netman;

};




#endif // MAINWINDOW_H

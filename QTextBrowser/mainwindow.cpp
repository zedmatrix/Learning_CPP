#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networkmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    netman(new NetMan::NetworkManager(this))
{
    //
    ui->setupUi(this);
    ui->urlOutput->setAcceptRichText(true);
    ui->urlOutput->setOpenLinks(false);
    //
    connect(ui->home, &QPushButton::clicked, this, &MainWindow::Home);
    connect(ui->quit, &QPushButton::clicked, this, &MainWindow::Quit);
    connect(netman, &NetMan::NetworkManager::responseReceived, this, &MainWindow::handleResponse);
    connect(netman, &NetMan::NetworkManager::errorOccurred, this, &MainWindow::handleError);
    connect(ui->urlInput, &QLineEdit::returnPressed, this, [this]() {
        ui->urlOutput->clear();
        ui->urlOutput->clearHistory();
        searchTerm = ui->urlInput->text().trimmed();
        handleURL();

    } );
    connect(ui->urlOutput, &QTextBrowser::anchorClicked, this, [this](const QUrl &url) {
        check = url.toString();
        qInfo() << "Clicked URL(check): " << check;
        if (check.startsWith("/")) {
            if (check.contains(".html")) {
                newUrl = BaseUrl + check;
            } else {
                prefix = check;
                newUrl = BaseUrl + prefix;
            }

        } else {
            newUrl = BaseUrl + prefix + check;
        }
        ui->urlInput->setText(newUrl);
        qInfo() << "URL Clicked:" << newUrl;
        netman->makeRequest(QUrl(newUrl));
    });

    netman->makeRequest(QUrl(BaseUrl));
    UpdateStatus();

}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::Home() {
    searchTerm = "http://www.google.com";
    netman->makeRequest(QUrl(searchTerm));
}

void MainWindow::Quit() {
    qDebug() << "Quitting";
    qApp->quit();
}
// void MainWindow::UpdateOutput(const QString &msg) {
//     ui->urlOutput->append(msg);
// }

// void MainWindow::InsertLink(const QString &videoLink) {
//     QTextCursor cursor(ui->urlOutput->document());
//     cursor.movePosition(QTextCursor::End);
//     cursor.insertHtml(videoLink);
// }

void MainWindow::UpdateStatus() {
    msg = QString("| %1 | %2 | %3 | %4 |")
        .arg(newUrl)
        .arg(prefix)
        .arg(statusMsg)
        .arg(statusError);

    ui->statusbar->showMessage(msg);
}

void MainWindow::handleURL() {
    ui->urlOutput->append("<hr>");

    QUrl url(searchTerm);

    //QUrlQuery query;
    //url.setQuery(query);

    if (url.isValid() && !url.host().isEmpty()) {
        statusMsg = "Valid URL:" + url.toString();
        UpdateStatus();
        netman->makeRequest(url);

    } else {
        statusError = "Invalid URL";
        UpdateStatus();
    }
}

void MainWindow::handleResponse(const QByteArray& response) {
    QString responseText = QString::fromUtf8(response);

    ui->urlOutput->setHtml(response);

    statusMsg = "Data received successfully!";
    UpdateStatus();
}

void MainWindow::handleError(const QString& errorString) {
    statusError = "Error:" + errorString;
    UpdateStatus();
    qWarning() << "Error:" << errorString;
}

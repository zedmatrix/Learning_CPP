//Place in mainwindow contructor
connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);

// only needed during the globals setup
#include "mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    QString statusString;

    switch (status) {
        case QMediaPlayer::LoadingMedia:
            statusString = "LoadingMedia";
            break;
        case QMediaPlayer::LoadedMedia:
            statusString = "LoadedMedia";
            UpdateStream();
            break;
        case QMediaPlayer::StalledMedia:
            statusString = "StalledMedia";
            break;
        case QMediaPlayer::BufferingMedia:
            statusString = "BufferingMedia";
            break;
        case QMediaPlayer::EndOfMedia:
            statusString = "EndOfMedia";
            break;
        case QMediaPlayer::InvalidMedia:
            statusString = "InvalidMedia";
            break;
        case QMediaPlayer::BufferedMedia:
            statusString = "BufferedMedia";
            break;
        case QMediaPlayer::MediaStatus::NoMedia:
            statusString = "NoMediaStatus";
            break;
        default:
            statusString = "Unknown Status";
            break;
    }

    // Log the status to the debug output
    qDebug() << "Media status changed:" << statusString;

    // Update the QTextEdit with the current media status
    ui->statusBar->showMessage(statusString);
}

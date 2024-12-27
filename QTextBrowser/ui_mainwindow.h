/********************************************************************************
** Form generated from reading UI file 'mainwindowQRSeGt.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWQRSEGT_H
#define MAINWINDOWQRSEGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *urlInput;
    QTextBrowser *urlOutput;
    QPushButton *quit;
    QPushButton *home;
    QLabel *label;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        urlInput = new QLineEdit(centralwidget);
        urlInput->setObjectName("urlInput");
        urlInput->setGeometry(QRect(130, 10, 661, 24));
        urlOutput = new QTextBrowser(centralwidget);
        urlOutput->setObjectName("urlOutput");
        urlOutput->setGeometry(QRect(10, 50, 781, 421));
        urlOutput->setOpenExternalLinks(false);
        quit = new QPushButton(centralwidget);
        quit->setObjectName("quit");
        quit->setGeometry(QRect(700, 490, 82, 28));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        font.setBold(true);
        quit->setFont(font);
        home = new QPushButton(centralwidget);
        home->setObjectName("home");
        home->setGeometry(QRect(10, 10, 61, 28));
        home->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 10, 41, 21));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        quit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        home->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "< url >", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWQRSEGT_H

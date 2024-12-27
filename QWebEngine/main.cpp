#include <QApplication>
#include <QMenuBar>
#include <QWebEngineView>
#include <QMainWindow>
#include <QAction>
#include <QWebEngineHistory>

class BrowserWindow : public QMainWindow {
    Q_OBJECT

public:
    BrowserWindow() {
        webView = new QWebEngineView(this);
        webView->setUrl(QUrl("https://www.primevideo.com/"));
        setCentralWidget(webView);

        QMenuBar *menuBar = this->menuBar();

        QMenu *fileMenu = menuBar->addMenu("&File");
        QMenu *linksMenu = menuBar->addMenu("&Links");

        // Create items for File menu
        QAction *backAction = fileMenu->addAction("Back");
        connect(backAction, &QAction::triggered, this, [this]() {
            if (webView->page()->history()->canGoBack())
                webView->back();
        });

        QAction *reloadAction = fileMenu->addAction("Reload");
        connect(reloadAction, &QAction::triggered, webView, &QWebEngineView::reload);

        QAction *quitAction = fileMenu->addAction("Quit");
        connect(quitAction, &QAction::triggered, QApplication::quit);

        connect(webView, &QWebEngineView::loadFinished, this, [this, backAction]() {
            backAction->setEnabled(webView->page()->history()->canGoBack());
        });

        // Creat items for Links menu
        QAction *LinkTubi = linksMenu->addAction("Tubi");
        QAction *LinkPluto = linksMenu->addAction("Pluto");
        QAction *LinkYoutube = linksMenu->addAction("YouTube");
        QAction *LinkCHEK = linksMenu->addAction("CHEK+ Victoria");
        QAction *LinkCBCGem = linksMenu->addAction("CBC Gem");
        QAction *LinkShout = linksMenu->addAction("Shout TV");

        connect(LinkTubi, &QAction::triggered, this, [this]() {
            webView->setUrl(QUrl("https://www.tubi.com"));
        });
        connect(LinkPluto, &QAction::triggered, this, [this]() {
            webView->setUrl(QUrl("https://www.pluto.tv"));
        });
        connect(LinkYoutube, &QAction::triggered, this, [this]() {
            webView->setUrl(QUrl("https://www.youtube.com"));
        });
        connect(LinkCHEK, &QAction::triggered, this, [this]() {
            webView->setUrl(QUrl("https://chekplus.ca/"));
        });
        connect(LinkCBCGem, &QAction::triggered, this, [this]() {
            webView->setUrl(QUrl("https://gem.cbc.ca"));
        });
        connect(LinkShout, &QAction::triggered, this, [this]() {
            webView->setUrl(QUrl("https://www.shout-tv.com/"));
        });

    }

private:
    QWebEngineView *webView;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    BrowserWindow window;
    window.resize(800, 600);
    window.show();

    return app.exec();
}

#include "main.moc"

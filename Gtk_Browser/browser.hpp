#ifndef BROWSER_HPP
#define BROWSER_HPP

#include <gtk/gtk.h>
#include <gtk/gtkentry.h>
#include <gdk/gdk.h>
#include <webkit/webkit.h>
#include <print>
#include <string>
#include <memory>
#include <functional>
#include <map>

class Browser {

public:

    Browser();
    ~Browser();
    int app(int argc, char **argv);
    void emitter(const std::string& str);

    struct ButtonData {
        Browser* self;
        const char* name;
    };
    static void onPressed(GtkButton*, gpointer user_data);
    static void onUrlEntered(GtkEntry* entry, gpointer user_data);

private:
    GtkApplication *m_app = nullptr;
    GtkWindow* m_window = nullptr;

    GtkWidget* m_webView = nullptr;
    GtkWidget* m_mainbox = nullptr;
    GtkWidget* m_toolbar = nullptr;
    GtkWidget* m_urlEntry = nullptr;

    GtkEntryBuffer* m_buffer = nullptr;

    GtkWidget* m_buttonBack = nullptr;
    GtkWidget* m_buttonHome = nullptr;
    GtkWidget* m_buttonYoutube = nullptr;
    GtkWidget* m_buttonQuit = nullptr;

    ButtonData m_back;
    ButtonData m_home;
    ButtonData m_quit;

    bool init();
    static void activate(GtkApplication* app, gpointer user_data);
    bool createMenu();
    void loadUrl(std::string url);

    std::string m_title;
    std::string m_homepage;
    std::string m_startpage;
    int m_width;
    int m_height;
    int m_status;


};

#endif //BROWSER_HPP

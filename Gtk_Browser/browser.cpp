#include "browser.hpp"

Browser::Browser() {
    m_title = "GTK Demo Browser";
    m_homepage = "https://www.google.com";
    m_startpage = "https://www.youtube.com";
    m_width = 1024;
    m_height = 768;
    m_status = 0;

}
Browser::~Browser() {
    //Empty
}
int Browser::app(int argc, char** argv) {
    m_app = gtk_application_new("com.example.browser", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(m_app, "activate", G_CALLBACK(Browser::activate), this);
    int status = g_application_run(G_APPLICATION(m_app), argc, argv);
    g_object_unref(m_app);
    return status;
}

void Browser::activate(GtkApplication* app, gpointer user_data) {
    Browser* self = static_cast<Browser*>(user_data);
    self->m_app = app;
    self->init();
}
bool Browser::init() {
    m_window = GTK_WINDOW(gtk_application_window_new(m_app));
    if (!m_window) return false;

    gtk_window_set_title(m_window, m_title.c_str());
    gtk_window_set_default_size(m_window, m_width, m_height);
    m_webView = webkit_web_view_new();
    if (!m_webView) return false;

    gtk_widget_set_hexpand(m_webView, TRUE);
    gtk_widget_set_vexpand(m_webView, TRUE);
    if (!createMenu()) return false;

    m_back = { this, "Back" };
    g_signal_connect(m_buttonBack, "clicked", G_CALLBACK(onPressed), &m_back);

    m_home = { this, "Home" };
    g_signal_connect(m_buttonHome, "clicked", G_CALLBACK(onPressed), &m_home);

    m_quit = { this, "Quit" };
    g_signal_connect(m_buttonQuit, "clicked", G_CALLBACK(onPressed), &m_quit);

    gtk_window_set_child(m_window, m_mainbox);

    if (m_urlEntry) {
        g_signal_connect(m_urlEntry, "activate", G_CALLBACK(onUrlEntered), this);
    } else {
        g_warning("m_urlEntry is null; URL entry activation signal not connected.");
    }

    loadUrl(m_startpage);
    gtk_widget_set_visible(GTK_WIDGET(m_window), TRUE);

    return true;
}

void Browser::loadUrl(std::string url) {
    if (!url.empty()) {
        webkit_web_view_load_uri(WEBKIT_WEB_VIEW(m_webView), url.c_str());
    }
}

bool Browser::createMenu() {
    m_mainbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    m_toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    m_buttonBack = gtk_button_new_with_label("Back");
    m_buttonHome = gtk_button_new_with_label("Home");
    m_buttonYoutube = gtk_button_new_with_label("Youtube");
    m_buttonQuit = gtk_button_new_with_label("Quit");

    m_urlEntry = gtk_entry_new();
    m_buffer = gtk_entry_buffer_new(m_startpage.c_str(), -1);
    gtk_entry_set_buffer(GTK_ENTRY(m_urlEntry), m_buffer);
    gtk_widget_set_hexpand(m_urlEntry, TRUE);

    gtk_box_append(GTK_BOX(m_toolbar), m_buttonBack);
    gtk_box_append(GTK_BOX(m_toolbar), m_buttonHome);
    gtk_box_append(GTK_BOX(m_toolbar), m_buttonYoutube);
    gtk_box_append(GTK_BOX(m_toolbar), m_urlEntry);
    gtk_box_append(GTK_BOX(m_toolbar), m_buttonQuit);

    gtk_box_append(GTK_BOX(m_mainbox), m_toolbar);
    gtk_box_append(GTK_BOX(m_mainbox), m_webView);

    return true;
}

void Browser::onPressed(GtkButton*, gpointer user_data) {
    auto* data = static_cast<ButtonData*>(user_data);
    if (!data || !data->self) return;

    if (strcmp(data->name, "Back") == 0) {
        data->self->emitter("back");
    } else if (strcmp(data->name, "Home") == 0) {
        data->self->emitter("home");
    } else if (strcmp(data->name, "Youtube") == 0) {
        data->self->emitter("youtube");
    } else if (strcmp(data->name, "Quit") == 0) {
        data->self->emitter("quit");
    }
}

void Browser::onUrlEntered(GtkEntry* entry, gpointer user_data) {
    Browser* self = static_cast<Browser*>(user_data);
    const char* url = gtk_entry_buffer_get_text(self->m_buffer);
    if (url && *url) {
        self->loadUrl(url);
    }
}


void Browser::emitter(const std::string& str) {
    std::map<std::string, std::function<void()>> actions = {
        {"back", [this] {
            std::println("Back Pressed");
            if (webkit_web_view_can_go_back(WEBKIT_WEB_VIEW(m_webView)))
                webkit_web_view_go_back(WEBKIT_WEB_VIEW(m_webView));
        }},
        {"home", [this] {
            std::println("Home Pressed");
            loadUrl(m_homepage);
        }},
        {"youtube", [this] {
            std::println("Youtube Pressed");
            loadUrl(m_startpage);
        }},
        {"quit", [this] {
            std::println("Quit Pressed");
            gtk_window_close(m_window);
        }}
    };
    if (auto it = actions.find(str); it != actions.end()) {
        it->second();  // Call the handler
    } else {
        std::println("Unknown Pressed");
    }
}


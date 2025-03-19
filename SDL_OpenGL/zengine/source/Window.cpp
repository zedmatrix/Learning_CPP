#include "Window.hpp"
#include "zengine.hpp"

namespace zengine {

    Window::Window() {

    }
    Window::~Window() {

    }

    int Window::create(std::string windowTitle, int screenWidth, int screenHeight, unsigned int flags) {
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        uint32_t windowFlags = SDL_WINDOW_OPENGL;

        if (INVISIBLE & flags) windowFlags |= SDL_WINDOW_HIDDEN;
        if (MAXIMIZED & flags) windowFlags |= SDL_WINDOW_MAXIMIZED;
        if (FULLSCREEN & flags) windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        if (BORDERLESS & flags) windowFlags |= SDL_WINDOW_BORDERLESS;

        // Create your window using the predefine variables
        _sdlWindow = SDL_CreateWindow(windowTitle.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                _screenWidth,
                                _screenHeight,
                                windowFlags);
        if (_sdlWindow == nullptr) {
            fatalError("SDL Window could not be created!");
        }

        SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
        if (glContext == nullptr) {
            fatalError("SDL_GL Context could not be initialized");
        }
        GLenum error = glewInit();
        if (error != GLEW_OK) {
            fatalError("Could not Initialize GLEW");
        }

        // Get OpenGL version and output to terminal
        std::cout << "*** OpenGL Version: " << glGetString(GL_VERSION) << " ***\n";

        //set background color dark-semi-transparent grey
        glClearColor(0.3f, 0.3f, 0.3f, 0.5f);

        // Enable VSYNC
        SDL_GL_SetSwapInterval(1);
        return 0;

    }
    void Window::swapBuffer() {
        SDL_GL_SwapWindow(_sdlWindow);
    }

}

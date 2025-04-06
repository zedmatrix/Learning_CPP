#include "IMainGame.hpp"
#include "App.hpp"
#include <iostream>
#include <memory>

int main(int argc, char** argv) {

    std::cout << "IMainGame - IMainWindow - Wrapper - meson.build\n";

    std::shared_ptr<App> app = std::make_shared<App>();
    app->run();

    std::cout << "\n \t *** Good Bye! *** \n" << std::endl;

    return 0;
}

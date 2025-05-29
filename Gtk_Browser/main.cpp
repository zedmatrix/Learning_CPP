#include "browser.hpp"

int main(int argc, char **argv) {
    Browser browser;
    int status = browser.app(argc, argv);

    return status;
}

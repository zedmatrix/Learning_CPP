cmake_minimum_required(VERSION 3.5)

project(Web_Browser LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

add_executable(Browser
    mainwindow.h
    ui_mainwindow.h
    mainwindow.ui
    main.cpp
    mainwindow.cpp
    networkmanager.h
    networkmanager.cpp

)

target_link_libraries(Browser Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)

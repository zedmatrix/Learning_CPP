cmake_minimum_required(VERSION 3.5)

project(Browser LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS WebEngineWidgets)

add_executable(Browser
    main.cpp
)

target_link_libraries(Browser Qt6::WebEngineWidgets)

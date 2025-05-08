cmake_minimum_required(VERSION 3.30)
project(CA3BugsLife)

set(CMAKE_CXX_STANDARD 20)

add_executable(CA3BugsLife main.cpp
        Crawler.h
        Crawler.cpp
        Board.cpp
        Board.h
        Util.cpp
        Util.h
        Bug.cpp
        Bug.h
        Hopper.cpp
        Hopper.h
        GUI.cpp
        GUI.h
        Slider.cpp
        Slider.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML-2.5.1/include)
target_link_libraries(CA3BugsLife sfml-system sfml-window sfml-graphics sfml-audio)
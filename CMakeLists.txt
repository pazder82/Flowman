cmake_minimum_required(VERSION 3.6)
project(Flowman)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Character.cpp
        Character.hpp
        ChFlowman.cpp
        ChFlowman.hpp
        ChHacker.cpp
        ChHacker.hpp
        common.hpp
        Desk.cpp
        Desk.hpp
        DrawableObject.cpp
        DrawableObject.hpp
        Item.cpp
        Item.hpp
        main.cpp
        nc_exception.hpp
        TS_ncurses.cpp
        TS_ncurses.hpp)

add_executable(Flowman ${SOURCE_FILES})
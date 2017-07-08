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
        ChBonus.cpp
        ChBonus.hpp
        common.hpp
        Desk.cpp
        Desk.hpp
        LogWindow.cpp
        LogWindow.hpp
        DrawableObject.cpp
        DrawableObject.hpp
        Item.cpp
        Item.hpp
        main.cpp
        nc_exception.hpp
        TS_ncurses.cpp
        TS_ncurses.hpp
        GameStatus.cpp
        GameStatus.hpp)

add_executable(Flowman ${SOURCE_FILES})
link_directories(/usr/local/lib)
target_link_libraries(Flowman -lcursesw -lncursesw -lboost_thread -lboost_system)
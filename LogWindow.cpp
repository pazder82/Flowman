//
// Created by root on 6/30/17.
//

#include "LogWindow.hpp"

void LogWindow::draw() const {
    werase(win);
    mvwprintw(win, 0, 3, "%s", "Points: 0");
    tsn.wrefresh(win);
}

void LogWindow::update_comment(std::string s) const {
    wmove(win, 0, 15);
    wclrtoeol(win);
    mvwprintw(win, 0, 15, "%s", s.c_str());
    tsn.wrefresh(win);
}

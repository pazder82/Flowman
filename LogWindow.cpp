//
// Created by root on 6/30/17.
//

#include "LogWindow.hpp"

#define LIVESLABEL 3
#define LIVESNUM 10
#define SCORELABEL 13
#define SCORENUM 20
#define COMMENT 25

void LogWindow::draw() const {
    werase(win);
    mvwprintw(win, 0, LIVESLABEL, "Lives: ");
    mvwprintw(win, 0, LIVESNUM, "%u", STARTING_LIVES);
    mvwprintw(win, 0, SCORELABEL, "Score: ");
    mvwprintw(win, 0, SCORENUM, "0");
    tsn.wrefresh(win);
}

void LogWindow::update_comment(std::string s) const {
    wmove(win, 0, COMMENT);
    wclrtoeol(win);
    mvwprintw(win, 0, COMMENT, "%s", s.c_str());
    tsn.wrefresh(win);
}

void LogWindow::update_score(unsigned int score) const {
    mvwprintw(win, 0, SCORENUM, "%u", score);
    tsn.wrefresh(win);
}

void LogWindow::update_lives(unsigned int lives) const {
    mvwprintw(win, 0, LIVESNUM, "%u", lives);
    tsn.wrefresh(win);
}

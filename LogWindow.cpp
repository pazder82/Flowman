//
// Created by root on 6/30/17.
//

#include "LogWindow.hpp"

// Horizontal offsets
#define LEVELLABEL 3
#define LEVELNUM 10
#define LIVESLABEL 13
#define LIVESNUM 20
#define SCORELABEL 23
#define SCORENUM 30
#define COMMENT 35

void LogWindow::draw() const {
    werase(win);
    mvwprintw(win, 0, LEVELLABEL, "Level: ");
    mvwprintw(win, 0, LEVELNUM, "1");
    mvwprintw(win, 0, LIVESLABEL, "Lives: ");
    mvwprintw(win, 0, LIVESNUM, "%u", STARTING_LIVES);
    mvwprintw(win, 0, SCORELABEL, "Score: ");
    mvwprintw(win, 0, SCORENUM, "0");
    tsn.wrefresh(win);
}

void LogWindow::update_help(std::string s) const {
    wmove(win, 0, COMMENT);
    wclrtoeol(win);
    mvwprintw(win, 0, COMMENT, "%s", s.c_str());
    tsn.wrefresh(win);
}

void LogWindow::update_comment(std::string s) const {
    return; // comments are not used in final version
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

void LogWindow::update_level(unsigned int level) const {
    mvwprintw(win, 0, LEVELNUM, "%u", level);
    tsn.wrefresh(win);
}

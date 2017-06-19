/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TS_ncurses.hpp
 * Author: Jan Pazdera
 *
 * Created on 6. října 2016, 22:42
 */

#include <thread>
#include <mutex>
#include "common.hpp"
#include "ncurses.h"
#include "curses.h"

#ifndef TS_NCURSES_HPP
#define TS_NCURSES_HPP

using namespace std;

#define LOCK lock_guard<mutex> lck(mtx)

/**
 * Thread safe ncurses
 */
class TS_ncurses {
public:
	RDC_D(TS_ncurses);
    TS_ncurses() = default;
    virtual ~TS_ncurses() = default;

	int ungetch (int i) { LOCK; return ::ungetch(i); }
	int mgetch () { /*LOCK*/; return ::getch(); }
    int endwin () { LOCK; return ::endwin(); }
	WINDOW * newwin (int vsize, int hsize ,int voffset, int hoffset) { LOCK; return ::newwin(vsize, hsize, voffset, hoffset); }
	int wborder (WINDOW * win , chtype ch1,chtype ch2, chtype ch3, chtype ch4, chtype ch5, chtype ch6, chtype ch7, chtype ch8) { LOCK; return ::wborder(win, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8); }
	int init_pair (NCURSES_PAIRS_T pair, NCURSES_COLOR_T fgcolor,NCURSES_COLOR_T bgcolor) { LOCK; return ::init_pair(pair, fgcolor, bgcolor); }
	int mwattron (WINDOW * win, int a) { LOCK; return ::wattron(win, a); }
	int waddch (WINDOW * win, const chtype cht) { LOCK; return ::waddch(win, cht); }
	int mwattroff (WINDOW * win, int a) { LOCK; return ::wattroff(win, a); }
	int wmove (WINDOW * win, int v, int h) { LOCK; return ::wmove(win, v, h); }
	int wrefresh (WINDOW * win) { LOCK; return ::wrefresh(win); }

private:
	mutex mtx;
};



#endif /* TS_NCURSES_HPP */


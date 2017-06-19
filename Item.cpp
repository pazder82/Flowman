/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Item.cpp
 * Author: Jan Pazdera
 * 
 * Created on 25. května 2016, 21:28
 */

#include "Item.hpp"
#include "nc_exception.hpp"

using namespace std;

int Item::last_color_pair = 0; // define and init static variable

Item::Item(int symbol, enum item_type_t item_type, int fgcolor, int bgcolor) :
symbol(symbol), item_type(item_type), fgcolor(fgcolor), bgcolor(bgcolor) { 
    color_pair = ++last_color_pair;
    tsn.init_pair(color_pair, fgcolor, bgcolor);
}

/**
 * Print Item symbol to the curent cursor position count times
 * @param count Number of characters to print
*/
void Item::PrintItem(WINDOW *win, const int count) const {
    tsn.mwattron(win, COLOR_PAIR(color_pair));
    for (int x = 0; x < count; x++) {
        tsn.waddch(win,symbol);
    }
    tsn.mwattroff(win, COLOR_PAIR(color_pair));
}

/**
 * Print an Item asciicharacter to the curent cursor position
*/
void Item::PrintItem(WINDOW *win) const {
    PrintItem(win, 1);
}

/**
 * Print Item asciicharacter to the defined cursor position
 * @param h Horizontal position
 * @param v Vertical position
*/
void Item::PrintItem(WINDOW *win, const int h, const int v) const {
    if ((h < 0) || (v < 0)) throw nc_exception("Can not draw item out of the desk");
    PrintItem(win, h, v, 1);
}

/**
 * Print Item asciicharacter to the defined cursor position count times
 * @param h Horizontal position
 * @param v Vertical position
 * @param count Number of characters to print
*/
void Item::PrintItem(WINDOW *win, const int h, const int v, const int count) const {
    if ((h < 0) || (v < 0)) throw nc_exception("Can not draw item out of the desk");
    tsn.wmove(win, v, h);
    PrintItem(win, count);
}
/**
 * Return type of Item
 * @return 
*/
Item::item_type_t Item::get_item_type() const {
    return item_type;
}


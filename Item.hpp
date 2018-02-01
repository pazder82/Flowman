/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Item.hpp
 * Author: Jan Pazdera
 *
 * Created on 25. května 2016, 21:28
 */

#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <ncurses.h>
#include "common.hpp"
#include "TS_ncurses.hpp"

extern TS_ncurses tsn;

class Item {
    public:
        enum item_type_t { empty, food, wall, hacker, weakhacker, endingweakhackerweak, endingweakhackerhacker, flowman, bonus };

        Item() = default;
        Item(const Item&) = default;
        Item(Item&&) = default;
        Item& operator=(const Item&) = default;
        Item& operator=(Item &&) = default;
        Item(int symbol, enum item_type_t item_type, int fgcolor, int bgcolor);
        void PrintItem(WINDOW *win) const;
        void PrintItem(WINDOW *win, const int count) const;
        void PrintItem(WINDOW *win, const int h, const int v) const;
        void PrintItem(WINDOW *win, const int h, const int v, const int count) const;
        virtual ~Item() {};
        enum item_type_t get_item_type() const;
    private:
        int symbol = ACS_BOARD; /**< character to print for this item */
        int color_pair = 1; /** ncurses color_pair - should be unique per Item */
        static int last_color_pair;
        enum item_type_t item_type = wall; /**< type of item */ 
        int fgcolor = COLOR_YELLOW;
        int bgcolor = COLOR_BLUE;
};

typedef std::map<Item::item_type_t, Item> Items_t;

#endif /* ITEM_HPP */


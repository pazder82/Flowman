/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DrawableObject.cpp
 * Author: Jan Pazdera
 * 
 * Created on 31. května 2016, 20:46
 */

#include "DrawableObject.hpp"

/**
 * Create drawable object of defined horizontal and vertical size place at horizontal and vertical offset
 * @param hsize
 * @param vsize
 * @param hoffset
 * @param voffset
 * @param border If true, print window border.
 */
DrawableObject::DrawableObject(const unsigned short hsize, const unsigned short vsize, const unsigned short hoffset, const unsigned short voffset, const bool border) 
    : hsize(hsize), vsize(vsize), hoffset(hoffset), voffset(voffset) { 
        if ((win = tsn.newwin(vsize, hsize, voffset, hoffset)) == NULL) throw nc_exception("Can't create window!");
        if (border) {
            if (tsn.wborder(win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER) != OK) throw nc_exception("Can't configure window border");
        }else {
            if (tsn.wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ') != OK) throw nc_exception("Can't configure window border");
        }
    }

DrawableObject::~DrawableObject() {
    delwin(win);
}

void DrawableObject::draw_item(const Item& item) const {
    item.PrintItem(win);
}

void DrawableObject::draw_item(const Item& item, const int count) const {
    item.PrintItem(win, count);
}

void DrawableObject::draw_item(const Item& item, const int h, const int v) const {
    item.PrintItem(win, h, v);
}

void DrawableObject::draw_item(const Item& item, const int h, const int v, const int count) const {
    item.PrintItem(win, h, v, count);
}

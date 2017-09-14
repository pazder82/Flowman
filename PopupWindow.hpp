//
// Created by root on 9/14/17.
//

#ifndef FLOWMAN_POPUPWINDOW_H
#define FLOWMAN_POPUPWINDOW_H


#include "DrawableObject.hpp"
#include <exception>
#include <ncurses.h>
#include "nc_exception.hpp"
#include "TS_ncurses.hpp"

extern TS_ncurses tsn;

class PopupWindow : public DrawableObject {
public:
    RDC(PopupWindow);
    PopupWindow(const unsigned short hsize, const unsigned short vsize, const unsigned short hoffset,
                const unsigned short voffset, const std::string msg);
    virtual ~PopupWindow() {}
    void draw() const override;
private:
    std::string msg;
    WINDOW* innerwin;
};


#endif //FLOWMAN_POPUPWINDOW_H

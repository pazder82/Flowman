//
// Created by root on 9/14/17.
//

#include "PopupWindow.hpp"

using namespace std;

void PopupWindow::draw() const {
    mvwprintw(innerwin, 0, 0, msg.c_str());
    string butstr = "Press Enter";
    unsigned short h = (get_hsize() - butstr.length())/2;
    unsigned short v = (get_vsize() - 2);
    mvwprintw(win, v, h, butstr.c_str());
    wrefresh(win);
    wrefresh(innerwin);
}

PopupWindow::PopupWindow(const unsigned short hsize, const unsigned short vsize, const unsigned short hoffset,
                         const unsigned short voffset, const std::string msg)
        : DrawableObject(hsize, vsize, hoffset, voffset, true), msg(msg) {
    if ((innerwin = newwin(vsize - 5, hsize - 4, voffset + 2, hoffset + 2)) == NULL) throw nc_exception("Can't create inner window!");
}

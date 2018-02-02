//
// Created by root on 6/30/17.
//

#ifndef FLOWMAN_LOGWINDOW_H
#define FLOWMAN_LOGWINDOW_H


#include "DrawableObject.hpp"

class LogWindow : public DrawableObject{
    RDC(LogWindow);
public:
    LogWindow(const unsigned short hsize, const unsigned short vsize, const unsigned short hoffset, const unsigned short voffset)
        : DrawableObject(hsize, vsize, hoffset, voffset, false) {}
    virtual ~LogWindow() = default;

    void draw() const override;
    void update_level(unsigned int level) const;
    void update_score(unsigned int score) const;
    void update_lives(unsigned int lives) const;
    void update_comment(std::string s) const;
    void update_help(std::string s) const;

};


#endif //FLOWMAN_LOGWINDOW_H

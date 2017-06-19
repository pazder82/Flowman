/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DrawableObject.hpp
 * Author: Jan Pazdera
 *
 * Created on 31. května 2016, 20:46
 */

#ifndef DRAWABLEOBJECT_HPP
#define DRAWABLEOBJECT_HPP

#include <exception>
#include <ncurses.h>
#include <mutex>
#include "common.hpp"
#include "Item.hpp"
#include "nc_exception.hpp"
#include "TS_ncurses.hpp"

extern TS_ncurses tsn;

class DrawableObject {
    public:
		DrawableObject() = delete;
        DrawableObject(const unsigned short hsize, const unsigned short vsize, const unsigned short hoffset, const unsigned short voffset, const bool border);
		DrawableObject(const DrawableObject&) = default;
		DrawableObject(DrawableObject&&) = default;
		DrawableObject& operator=(const DrawableObject&) = default;
		DrawableObject& operator=(DrawableObject&&) = default;
        virtual ~DrawableObject();
        virtual void draw() const = 0;
        unsigned short get_hsize() const { return hsize; } /**< return horizontal size */
        unsigned short get_vsize() const { return vsize; } /**< return vertical size */
        unsigned short get_hoffset() const { return hoffset; } /**< return horizontal offset */
        unsigned short get_voffset() const { return voffset; } /**< return vertical offset */
    protected:
        void draw_item(const Item& item) const;
        void draw_item(const Item& item, const int count) const;
        void draw_item(const Item& item, const int h, const int v) const;
        void draw_item(const Item& item, const int h, const int v, const int count) const;
        WINDOW* win;
    private:
        const unsigned short hsize, vsize;
        const unsigned short hoffset, voffset;
};

#endif /* DRAWABLEOBJECT_HPP */


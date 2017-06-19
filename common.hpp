/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   common.hpp
 * Author: Jan Pazdera
 *
 * Created on 31. května 2016, 21:12
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include <map>
#include <vector>
#include <utility>
#include <string>

/* Game constants */
const unsigned int GAMESPEED = 200; // ms between each move
const unsigned int HACKERREVIVETIME = 30;  // GAMESPEED*REVIVETIME*speed ms to revive dead hacker
const unsigned int FLOWMANREVIVETIME = 2; // GAMESPEED*REVIVETIME*speed ms to revive dead flowman

/* Types */
typedef std::array<int,2> square_coord_t;

/* Operators */
static square_coord_t operator+(const square_coord_t& a, const square_coord_t& b) {
	return { { a.at(0) + b.at(0), a.at(1) + b.at(1) } };
}

static bool operator==(const square_coord_t& a, const square_coord_t& b) {
	return ((a.at(0) == b.at(0)) && (a.at(1) == b.at(1)));
}

/* Window constants */
const unsigned short MAXH = 80; /**< max terminal horizontal size */
//const unsigned short MAXH = getmaxx(stdscr); /**< max terminal horizontal size */
const unsigned short MAXV = 25; /**< max terminal vertical size */
// const unsigned short MAXV = getmaxy(stdscr); /**< max terminal vertical size */

const unsigned short DESKVSIZE = 24; /**< vertical size of play desk */
const unsigned short DESKHSIZE = 80; /**< horizontal size of play desk */

const unsigned short SCOREVSIZE = MAXV - DESKVSIZE; /**< vertical size of score window */
const unsigned short SCOREHSIZE = MAXH; /**< horizontal size of score window */
const unsigned short SCOREHOFFSET = 0; /**< horizontal offset of score window */
const unsigned short SCOREVOFFSET = DESKVSIZE; /**< vertical offset of score window */

/* Labyrinth parameters */
const unsigned short MAX_WALL_PERCENTS_ALLOWED = 65; /**< In the labyrinth the wall squares can be assigned to less than MAX_WALLS_ALLOWED percents of all squares */
const unsigned short CHANGE_DIR_LIKEHOOD = 10; /**< The higher the number, the less likely the tunnel direction change during generation */

/* Macros */
#define REMOVE_DEFAULT_CONSTRUCTOR(x) x() = delete;
#define REMOVE_COPY_CONSTRUCTOR(x) x(const x&) = delete;
#define REMOVE_MOVE_CONSTRUCTOR(x) x(x&&) = delete;
#define REMOVE_ASSIGNMENT_CONSTRUCTOR(x) x& operator=(const x&) = delete;
#define REMOVE_ASSIGNMENT_MOVE_CONSTRUCTOR(x) x& operator=(x &&) = delete;

// Remove default constructors...
#define RDC(x) REMOVE_DEFAULT_CONSTRUCTOR(x) REMOVE_COPY_CONSTRUCTOR(x) REMOVE_MOVE_CONSTRUCTOR(x) REMOVE_ASSIGNMENT_CONSTRUCTOR(x) REMOVE_ASSIGNMENT_MOVE_CONSTRUCTOR(x)
#define RDC_D(x) REMOVE_COPY_CONSTRUCTOR(x) REMOVE_MOVE_CONSTRUCTOR(x) REMOVE_ASSIGNMENT_CONSTRUCTOR(x) REMOVE_ASSIGNMENT_MOVE_CONSTRUCTOR(x)

#endif /* COMMON_HPP */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Desk.cpp
 * Author: Jan Pazdera
 * 
 * Created on 9. září 2016, 21:37
 */

#include <curses.h>
#include "Desk.hpp"
#include "iostream"

using namespace std;

std::random_device Desk::generator;

/**
 * Create drawable object of defined horizontal and vertical size place at horizontal and vertical offset.
 * Then initialize all desk squares with Item() constructor.
 * @param hsize
 * @param vsize
 * @param hoffset
 * @param voffset
*/
Desk::Desk(const unsigned short hsize, const unsigned short vsize, const unsigned short hoffset, const unsigned short voffset) 
    : DrawableObject(hsize, vsize, hoffset, voffset, false) {
        // create associative array of items
	    // insert method does not require non-parameter constructor for items as operator[] does
        items.insert(make_pair(Item::empty, Item(' ', Item::empty, COLOR_YELLOW, COLOR_BLUE)));
        items.insert(make_pair(Item::wall, Item(ACS_BOARD, Item::wall, COLOR_WHITE, COLOR_BLUE)));
        items.insert(make_pair(Item::bonus, Item(ACS_BULLET, Item::bonus, COLOR_YELLOW, COLOR_BLUE)));
        items.insert(make_pair(Item::flowman, Item(ACS_DIAMOND, Item::flowman, COLOR_BLACK, COLOR_YELLOW)));
        items.insert(make_pair(Item::hacker, Item(ACS_DIAMOND, Item::hacker, COLOR_BLACK, COLOR_RED)));
        items.insert(make_pair(Item::weakhacker, Item(ACS_DIAMOND, Item::hacker, COLOR_BLACK, COLOR_GREEN)));
        items.insert(make_pair(Item::food, Item('.', Item::food, COLOR_WHITE, COLOR_BLUE)));
    }


/**
 * Init squares values. This method randomly generates new labyrinth.
 * In the labyrinth, no dead ends are allowed.
*/
void Desk::init_squares() {
    unsigned short hsize = get_hsize();
    unsigned short vsize = get_vsize();

    squares.clear();
    squares.reserve(hsize);
    for (unsigned short h = 0; h < hsize; h++) {
		// fill the whole labyrinth with walls
        squares.push_back(vector<Item>(vsize));
    }

	// Generate tunnels until 
	// 1) covers more then 100% - MAX_WALL_PERCENRS_ALLOWED% of the desk and
	// 2) there is no dead end tunnel
	unsigned short total_squares = (hsize * vsize);
	unsigned short wall_squares = get_num_of_squares_of_type(Item::wall);
	square_coord_t sc = { { hsize/2, vsize/2 } }; // start in the center of the first quadrant
	square_coord_t sc_old = sc;
	while ((wall_squares*100/total_squares > MAX_WALL_PERCENTS_ALLOWED) || (number_of_neighbors(Item::food, sc_old) < 2)) {
		squares[sc.at(0)][sc.at(1)] = items.at(Item::food);
		squares[hsize - sc.at(0) - 1][sc.at(1)] = items.at(Item::food);
		squares[sc.at(0)][vsize - sc.at(1) - 1] = items.at(Item::food);
		squares[hsize - sc.at(0) - 1][vsize - sc.at(1) - 1] = items.at(Item::food);
		wall_squares = get_num_of_squares_of_type(Item::wall);
		draw();
		sc_old = sc;
        sc = get_next_tunnel_square(sc);
	}
}

/**
 * Draw all items on desk
*/
void Desk::draw() const {
    unsigned short vsize = get_vsize();
    unsigned short hsize = get_hsize();

    for (unsigned short h = 0; h < hsize; h++) {
        for (unsigned short v = 0; v < vsize; v++) {
            draw_item(squares.at(h).at(v).get_item_type(), h, v);
        }
    }
    tsn.wrefresh(win);
}

/**
 * Draw item at specified position
 * @param item
 * @param h
 * @param v
 */
void Desk::draw_item(const Item::item_type_t it, const unsigned short h, const unsigned short v) const {
	items.at(it).PrintItem(win, h+get_hoffset(), v+get_voffset());
}

/**
 * Return Item at position
 * @param h
 * @param v
 * @return 
 */
Item::item_type_t Desk::get_item_type(const unsigned short h, const unsigned short v) const {
    return squares.at(h).at(v).get_item_type();
}

/**
 * Return Item at position
 * @param sc
 * @return 
 */
Item::item_type_t Desk::get_item_type(const square_coord_t sc) const {
	return get_item_type(sc.at(0), sc.at(1));
}

/**
 * Set square in defined position to defined type
 * @param it
 * @param h
 * @param v
 */
void Desk::set_item_type(const Item::item_type_t it, const unsigned short h, const unsigned short v) {
	squares[h][v] = items.at(it);
}

/**
 * Set square in defined position to defined type
 * @param it
 * @param sc
 */
void Desk::set_item_type(const Item::item_type_t it, const square_coord_t sc) {
	set_item_type(it, sc.at(0), sc.at(1));
}

/**
 * Return number of neighbor fields with the same Item type
 * @param Item::item_type_t
 * @param sc square coordinates
 * @return 
 */
int Desk::number_of_neighbors(const Item::item_type_t it, const square_coord_t sc) const {
	int ret = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if ((sc.at(0) + i >= 0) && (sc.at(0) + i < get_hsize()) && (sc.at(1) + j >= 0) && (sc.at(1) + j < get_vsize()) && 
					(((i == 0) && (j != 0)) || ((j == 0) && (i != 0))) && (squares.at(sc.at(0)+i).at(sc.at(1)+j).get_item_type() == it)) {
				ret++;
			}
		}
	}
	return ret;
}

/**
 * Get next square for generated tunnel. Found square coordinate is returned in sc reference.
 * @param sc Reference - if suitable square found, return it in sc reference.
 * @return direction_t new 
 */
square_coord_t Desk::get_next_tunnel_square(square_coord_t sc) {
	update_direction();
	if ((dir == Desk::up) && (sc[1] > 0)) {
			sc[1] -= 1;
	} else if ((dir == Desk::down) && (sc[1] < (get_vsize()/2) - 1)) {
			sc[1] += 1;
	} else if ((dir == Desk::left) && (sc[0] > 0)) {
		sc[0] -= 1;
	} else if ((dir == Desk::right) && (sc[0] < (get_hsize()/2) -1)) {
		sc[0] += 1;
	}
	return sc;
}

/**
 * Update direction in 1 of CHANGE_DIR_LIKEHOOD cases
 */
void Desk::update_direction(void) {
	Desk::direction_t newdir = dir;
	uniform_int_distribution<unsigned short> randdist(0, CHANGE_DIR_LIKEHOOD);
    if (randdist(generator) == 0) {
		// change direction
		randdist = uniform_int_distribution<unsigned short>(0, 3); // four direction
		// find new direction which is not the oposite direction
		while (is_oposite_dir(newdir = static_cast<Desk::direction_t>(randdist(generator)), dir) || (newdir == dir)) { }
	}
	dir = newdir;
}

/**
 * Return true, if d1 and d2 are oposite directions
 * @param d1
 * @param d2
 * @return 
 */
bool Desk::is_oposite_dir(const direction_t d1, const direction_t d2) const {
	return ((d1 == Desk::up && d2 == Desk::down) || (d1 == Desk::down && d2 == Desk::up) ||
			(d1 == Desk::right && d2 == Desk::left) || (d1 == Desk::left && d2 == Desk::right));
}

/**
 * Return number of squares of provided type
 * @param 
 * @return 
 */
unsigned short Desk::get_num_of_squares_of_type(const Item::item_type_t it) const {
	unsigned short ret = 0;
	for (auto row : squares) {
		for (auto square : row) {
			if (square.get_item_type() == it) ret++;
		}
	}
	return ret;
}

/**
 * Check if the square is valid for placing a Character
 */
bool Desk::is_valid_square(const unsigned short hpos, const unsigned short vpos) const {
	if ((hpos >= get_hsize()) || (vpos >= get_vsize())) {
		return false;
	}
	Item::item_type_t it = get_item_type(hpos, vpos);
	if ((it == Item::wall)) {
		return false;
	}
	return true;
}

/**
 * Check if the square is valid for placing a Character
 */
bool Desk::is_valid_square(const square_coord_t sc) const {
	return is_valid_square(sc.at(0), sc.at(1));
}

/**
 * Find square of Item::item_type_t.
 * At least one square of this type must be present in the desk, otherwise this method will cause endless loop.
 * @param it
 * @return 
 */
square_coord_t Desk::find_square_in_center() const {
	const unsigned short hstep = 3;
	const unsigned short vstep = 1;
	unsigned short hradius = 0;
	unsigned short vradius = 0;
	const unsigned short hcenter = get_hsize()/2;
	const unsigned short vcenter = get_vsize()/2;
	uniform_int_distribution<unsigned short> randhdist(hcenter-hradius, hcenter+hradius);
	uniform_int_distribution<unsigned short> randvdist(vcenter-vradius, vcenter+vradius);
	
	// start searching in the center and increasingly expand the searching radius
	// for each radius increase number of tries
	while(1) {
		for (int i = 0; i <= hradius; i++) {
			unsigned short h = randhdist(generator);
			unsigned short v = randvdist(generator);
			
			if (is_valid_square(h, v)) {
				return { {h, v} };
			}
		}
		hradius += hstep;
		vradius += vstep;
		if ((hradius*2)+1 >= get_hsize()) {
			randhdist = uniform_int_distribution<unsigned short>(0, get_hsize()-1);
		}else {
			randhdist = uniform_int_distribution<unsigned short>(hcenter-hradius, hcenter+hradius);
		}
		if ((vradius*2)+1 >= get_vsize()) {
			randvdist = uniform_int_distribution<unsigned short>(0, get_vsize()-1);
		}else {
			randvdist = uniform_int_distribution<unsigned short>(vcenter-vradius, vcenter+vradius);
		}
	}
}


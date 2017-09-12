/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Desk.hpp
 * Author: Jan Pazdera
 *
 * Created on 9. září 2016, 21:37
 */

#ifndef DESK_HPP
#define DESK_HPP

#include <vector>
#include <algorithm>
#include <random>
#include "DrawableObject.hpp"
#include "Item.hpp"

typedef std::vector< std::vector<Item> > desk_t;

class Desk : public DrawableObject {
public:
	enum direction_t { left, up, right, down };

	Desk() = delete;
    Desk(const unsigned short hsize, const unsigned short vsize, const unsigned short hoffset, const unsigned short voffset);
	Desk(const Desk&) = default;
	Desk(Desk&&) = default;
	Desk& operator=(const Desk&) = default;
	Desk& operator=(Desk&&) = default;
    virtual ~Desk() = default;

	void draw() const override;
	void draw_item(const Item::item_type_t it, const unsigned short h, const unsigned short v) const;

	Item::item_type_t get_item_type(const unsigned short h, const unsigned short v) const;
	Item::item_type_t get_item_type(const square_coord_t sc) const;
	void set_item_type(const Item::item_type_t it, const unsigned short h, const unsigned short v);
	void set_item_type(const Item::item_type_t it, const square_coord_t sc);
	unsigned int get_num_of_items(Item::item_type_t it) const;

	void init_squares();
	void refresh_win() { tsn.wrefresh(win); }

	bool is_valid_square(const unsigned short hpos, const unsigned short vpos) const;
	bool is_valid_square(const square_coord_t sc) const;

	square_coord_t find_square_in_center() const;
private:
    desk_t squares;
    Items_t items;
	direction_t dir = up;
	static std::random_device generator;

	int number_of_neighbors(const Item::item_type_t, const square_coord_t sc) const;
	square_coord_t get_next_tunnel_square(square_coord_t sc);
	void update_direction(void);
	bool is_oposite_dir(const direction_t d1, const direction_t d2) const;
	unsigned short get_num_of_squares_of_type(const Item::item_type_t it) const;
	
};

#endif /* DESK_HPP */


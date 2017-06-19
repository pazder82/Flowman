/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChHacker.cpp
 * Author: Jan Pazdera
 * 
 * Created on 18. října 2016, 21:37
 */

#include "ChHacker.hpp"
#include "ChFlowman.hpp"

std::random_device ChHacker::generator;

/**
 * Get next position for move
 * @return 
 */
Character::direction_t ChHacker::get_next_position() const{
	square_coord_t newdirsc;
	Character::direction_t newdir = dir;
	uniform_int_distribution<int> randnewdirdist(0, 3);

	while (!check_next_position(newdir)) {
		newdir = static_cast<Character::direction_t>(randnewdirdist(generator));		
	}
	return newdir;
}

/**
 * Return true, if there is no wall in the provided direction
 * @param dir
 * @return 
 */
bool ChHacker::check_next_position(const direction_t dir) const {
	square_coord_t newdirsc;
	if (dir == Character::up) {
		newdirsc = { { 0, -1 } };	
	}else if (dir == Character::down) {
		newdirsc = { { 0, 1 } };
	}else if (dir == Character::left) {
		newdirsc = { { -1, 0 } };
	}else { // Character::right
		newdirsc = { { 1, 0 } };
	}
	return (desk.is_valid_square(get_pos() + newdirsc));
}

/**
 * Hacker moved - check new position and modify environment if necessary
 */
void ChHacker::process_new_square() {
	for (auto ch : chvector) {
		// check, if some other character is not at the same position
		if ((ch->get_pos() == this->get_pos()) && (ch != this)) {
			// if found, check its type. If it is flowman, kill him	
			if (dynamic_cast<ChFlowman*>(ch)) {
				ch->kill(Character::revive);
			}
		}
	}
}

/**
 * Restart hacker position
 */
void ChHacker::restart_position() {
	uniform_int_distribution<unsigned short> randhdist(0, desk.get_hsize());
	uniform_int_distribution<unsigned short> randvdist(0, desk.get_vsize());
	while (!desk.is_valid_square(hpos = randhdist(generator), vpos = randvdist(generator)));
}

void ChHacker::move_character(const direction_t dir) {
	this->dir = dir;
	Character::move_character(dir);
}


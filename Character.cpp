/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.cpp
 * Author: Jan Pazdera
 * 
 * Created on 10. září 2016, 22:38
 */

#include "Character.hpp"

using namespace std;

vector<Character*> Character::chvector;
mutex Character::mtx;

/**
 * Construct Character
 * @param item
 * @param h Initial horizontal coordinate
 * @param v Initial vertical coordinate
 * @param speed_multiplier Character speed
 */
Character::Character(const Item::item_type_t it, Desk& desk, const float speed_multiplier) : it(it), desk(desk), speed(
        static_cast<int>(speed_multiplier)*GAMESPEED) {
}

/**
 * Move character on desk (redraw it at new relative position)
 * @param dir Direction 
 */
void Character::move_character(const direction_t dir) {
	square_coord_t sc = {{ 0, 0 }};
	if (dir == up) {
		sc = {{ 0, -1 }};	
	}else if (dir == down) {
		sc = {{ 0, 1 }};
	}else if (dir == left) {
		sc = {{ -1, 0 }};
	}else if (dir == right) {
		sc = {{ 1, 0 }};
	}
	if (desk.is_valid_square(hpos+sc.at(0), vpos+sc.at(1))) {
		desk.draw_item(desk.get_item_type(hpos, vpos), hpos, vpos); // replace the character with the square on desk
		hpos = hpos+sc.at(0);
		vpos = vpos+sc.at(1);
		desk.draw_item(it, hpos, vpos); // draw item into new position
		desk.refresh_win();
	}
}

/**
 * set type of death
 * @param tod
 */
void Character::kill(const lifestatus_t tod) {
	if (tod == deadrevive || tod == deadnorevive) {
		this->lifestatus = tod;
	}
}

/**
 * Character's main loop
 */
void Character::run_i() {
	int revive_count = get_revive_time();
	std::chrono::system_clock::time_point laststatus = std::chrono::system_clock::now(); // keep timepoint of the last character status update
    std::chrono::system_clock::time_point lastanim = std::chrono::system_clock::now(); // keep timepoint of the last character animation update
	while(!quit) {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		// Update status of character
		if (now - laststatus > std::chrono::milliseconds(get_speed())) {
			unique_lock<mutex> lck(mtx);
			if (lifestatus == alive) {
				move_character(get_next_position());
				process_new_square(); // call hook
			} else if (lifestatus == deadrevive) {
				if (revive_count <= 0) {
					revive_count = get_revive_time();
					lifestatus = alive;
					restart_position();
				} else {
					revive_count -= 1;
				}
			}
			update_character_status(); // call hook
			lck.unlock();
            laststatus = std::chrono::system_clock::now();
		}
		if (now - lastanim > std::chrono::milliseconds(ANIMSPEED)) {
            unique_lock<mutex> lck(mtx);
            animate_character();
            lck.unlock();
            lastanim = std::chrono::system_clock::now();
        }
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

/**
 * Activate character's thread running main loop
 */
void Character::run() {
	if (!th.joinable()) {
		quit = false;
		th = move(thread(&Character::run_i, this));
	}
}

/**
 * Terminate character's main loop and remove character from chvector.
 */
void Character::terminate() {
	quit = true;
	if (th.joinable()) {
		th.join();
	}
}

/**
 * Check if character has joinable thread (i.e. run() method was called)
 * @return true if joinable
 */
bool Character::joinable() const {
	return th.joinable();
}

/**
 * Restart position of character at proper square of desk.
 * This method should be called in case of game restart.
 */
void Character::restart_position() {
	square_coord_t sc = desk.find_square_in_center();
	hpos = sc.at(0);
	vpos = sc.at(1);
	desk.draw_item(it, hpos, vpos); // draw item into start position
	desk.refresh_win();
}

/**
 * Return true, if character is in lifestatus_t == alive
 * @return
 */
bool Character::is_alive() const {
	return lifestatus == Character::alive;
}

/**
 * Change item_type of character to newit
 * @param newit
 */
void Character::change_item_type(Item::item_type_t newit) {
	it = newit;
}

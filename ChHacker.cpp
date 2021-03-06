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


/**
 * Get next position for move
 * @return 
 */
Character::direction_t ChHacker::get_next_position() {
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
			// if found, check its type.
			if (dynamic_cast<ChFlowman*>(ch) && ch->is_alive()) {
                // It is alive Flowmon. If I am common hacker, kill Flowman, if I am weak hacker, kill me.
                if (get_item_type() == Item::hacker) {
                    ch->kill(Character::deadrevive);
					gameStatus.dec_life();
                    logWindow.update_lives(gameStatus.get_lives());
					logWindow.update_comment("Killed by hacker");
                } else{
                    kill(Character::deadrevive);
                    gameStatus.inc_score(SCORE_FOR_HACKER);
                    logWindow.update_score(gameStatus.get_score());
					logWindow.update_comment("Hacker killed");
                }
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
    logWindow.update_comment(std::string("Hacker restarted at ") + std::to_string(hpos) + std::string(",") + std::to_string(vpos));
    turn_into_common_hacker(); // Newborn hackers are always common ones.
}

void ChHacker::move_character(const direction_t dir) {
	this->dir = dir;
	Character::move_character(dir);
}

/**
 * Return Hacker revive time
 * @return
 */
unsigned int ChHacker::get_revive_time() const {
	return HACKERREVIVETIME;
}

/**
 * Turn hacker into weak hacker form, when he can be eaten by Flowman
 */
void ChHacker::turn_into_weak_hacker() {
    change_item_type(Item::weakhacker);
    ttl = WEAKHACKERLIFETIME * (GAMESPEED / static_cast<float>(get_speed())); // We want every hacker to stay at weak state for the same time, so we multiply the ttl by hacker speed.
}

/**
 * Turn hacker back into the form of dangerous hacker
 */
void ChHacker::turn_into_common_hacker() {
    change_item_type(Item::hacker);
}

/**
 * Turn weak hacker into item_type to warn user that this one is changing into common soon
 */
void ChHacker::turn_into_endingweak_hacker() {
    change_item_type(Item::endingweakhackerweak);
}

/**
 * Update weak hacker status if necessary
 */
void ChHacker::update_character_status() {
    if (is_weak()) {
        // countdown weakhacker lifetime and once it's zero, turn him back into the common dangerous hacker form
        ttl--;
        if (ttl < WEAKHACKERLIFETIME/3){
            turn_into_endingweak_hacker();
        }
        if (ttl == 0) {
            turn_into_common_hacker();
        }
    }
}

int ChHacker::get_speed() const {
	return Character::get_speed() - (gameStatus.get_level() * SPEEDACCELERATORPERLEVEL);
}

bool ChHacker::is_weak() {
    Item::item_type_t t = get_item_type();
	return (t == Item::weakhacker) || (t == Item::endingweakhackerweak) || (t == Item::endingweakhackerhacker);
}

bool ChHacker::is_endingweak() {
    Item::item_type_t t = get_item_type();
    return (t == Item::endingweakhackerweak) || (t == Item::endingweakhackerhacker);
}

void ChHacker::animate_character() {
    if (is_endingweak()) {
		if (get_item_type() == Item::endingweakhackerweak) {
			change_item_type(Item::endingweakhackerhacker);
		} else {
			change_item_type(Item::endingweakhackerweak);
		}
		desk.refresh_win();
	}
}


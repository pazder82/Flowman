/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChFlowman.cpp
 * Author: Jan Pazdera
 * 
 * Created on 9. října 2016, 13:39
 */

#include "ChFlowman.hpp"
#include "ChHacker.hpp"
#include "ChBonus.hpp"

ChFlowman::~ChFlowman() {
}

/**
 * This class uses user interaction to determine next move. User interacts with
 * this class by keyboard. This method is used to report pressed key.
 * @param keyp
 */
void ChFlowman::report_pressed_key(const int keyp) {
	this->keyp = keyp;
}

/**
 * Get next position of this character in the next cycle
 * @return Relative position in next cycle
 */
Character::direction_t ChFlowman::get_next_position() {
	if (keyp == KEY_LEFT) {
		return Character::left;
	}else if (keyp == KEY_RIGHT) {
		return Character::right;
	}else if (keyp == KEY_UP) {
		return Character::up;
	}else if (keyp == KEY_DOWN) {
		return Character::down;
	}else {
		return Character::left;
	}
}

/**
 * Flowman moved to new square, so check and modify the environment
 */
void ChFlowman::process_new_square() {
	for (auto ch : chvector) {
		// Check, if some other character is not alive at the same position
		// if so, check whether it is weak hacker or common hacker.
		// If it is common hacker, flowman (this) must die, if it is weak hacker, hacker must die.
		if ((ch->get_pos() == this->get_pos()) && (ch != this)) {
			// if found, check its type.
			if (dynamic_cast<ChHacker*>(ch) && ch->is_alive()) {
                // It is hacker, check, whether it is common hacker or weak hacker and then kill one or another accordingly
				if (ch->get_item_type() == Item::hacker) {
					// common hacker -> Flowman will die
					this->kill(Character::deadrevive);
					logWindow.update_comment("Killed by hacker");
				}else {
					// weak hacker -> Hacker will die
					ch->kill(Character::deadrevive);
					logWindow.update_comment("Hacker killed");
				}
			}
			if (dynamic_cast<ChBonus*>(ch) && ch->is_alive()) {
				// it is food -> eat it (== kill it) and turn all hackers into weak hackers
				ch->kill(Character::deadrevive);
				logWindow.update_comment("Ate bonus");
                for (auto ch2 : chvector) {
                    if (dynamic_cast<ChHacker*>(ch2) && ch2->is_alive()) {
                        dynamic_cast<ChHacker*>(ch2)->turn_into_weak_hacker();
                    }
                }
			}
		}
	}
	desk.set_item_type(Item::empty, get_hpos(), get_vpos());
}

/**
 * Return revive time of Flowman
 * @return
 */
unsigned int ChFlowman::get_revive_time() const {
	return FLOWMANREVIVETIME;
}


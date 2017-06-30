//
// Created by root on 6/30/17.
//

#include "ChBonus.hpp"

std::random_device ChBonus::generator;

void ChBonus::restart_position() {
    uniform_int_distribution<unsigned short> randhdist(0, desk.get_hsize());
    uniform_int_distribution<unsigned short> randvdist(0, desk.get_vsize());
    while (!desk.is_valid_square(hpos = randhdist(generator), vpos = randvdist(generator)));
}

Character::direction_t ChBonus::get_next_position() const {
    return Character::none;
}

/**
 * Return bonus revive time
 * @return
 */
unsigned int ChBonus::get_revive_time() const {
    return BONUSREVIVETIME;
}

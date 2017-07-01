//
// Created by root on 6/30/17.
//

#include "ChBonus.hpp"


void ChBonus::restart_position() {
    uniform_int_distribution<unsigned short> randhdist(0, desk.get_hsize());
    uniform_int_distribution<unsigned short> randvdist(0, desk.get_vsize());
    while (!desk.is_valid_square(hpos = randhdist(generator), vpos = randvdist(generator)));
    ttl = BONUSLIFETIME;
    logWindow.update_comment("Bonus was born");
}

Character::direction_t ChBonus::get_next_position() {
    return Character::none;
}

/**
 * Return bonus revive time
 * @return
 */
unsigned int ChBonus::get_revive_time() const {
    return BONUSREVIVETIME;
}

/**
 * Countdown the bonus time to live. When it is zero, the bonus dies.
 */
void ChBonus::process_new_square() {
    ttl--;
    if (ttl == 0) {
        kill(deadrevive);
        desk.draw_item(desk.get_item_type(hpos, vpos), hpos, vpos);
        logWindow.update_comment("Bonus has died");
    }
}
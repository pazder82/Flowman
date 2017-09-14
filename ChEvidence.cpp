//
// Created by root on 6/30/17.
//

#include "ChEvidence.hpp"


void ChEvidence::restart_position() {
    uniform_int_distribution<unsigned short> randhdist(0, desk.get_hsize());
    uniform_int_distribution<unsigned short> randvdist(0, desk.get_vsize());
    while (!desk.is_valid_square(hpos = randhdist(generator), vpos = randvdist(generator)));
    ttl = BONUSLIFETIME;
    desk.draw_item(Item::bonus, hpos, vpos);
    logWindow.update_comment("Bonus was born");
}

Character::direction_t ChEvidence::get_next_position() {
    return Character::none;
}

/**
 * Return bonus revive time
 * @return
 */
unsigned int ChEvidence::get_revive_time() const {
    return BONUSREVIVETIME;
}

/**
 * Countdown the bonus time to live. When it is zero, the bonus dies.
 */
void ChEvidence::update_character_status() {
    if (is_alive()) {
        ttl--;
        // redraw bonus as it could have been erased by hacker moving over it
        desk.draw_item(Item::bonus, hpos, vpos);

        if (ttl == 0) {
            kill(deadrevive);
            desk.draw_item(desk.get_item_type(hpos, vpos), hpos, vpos);
            logWindow.update_comment("Bonus has died");
        }
    }
}

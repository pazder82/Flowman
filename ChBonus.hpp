//
// Created by root on 6/30/17.
//

#ifndef FLOWMAN_CHBONUS_H
#define FLOWMAN_CHBONUS_H

#include "Character.hpp"

class ChBonus : public Character{
public:
    RDC(ChBonus);
    ChBonus(const Item::item_type_t it, Desk& desk) : Character(it, desk, 1) {}
    virtual ~ChBonus() { }
    void restart_position() override;
private:
    static std::random_device generator;
    direction_t get_next_position() const override;
    void process_new_square() override {};

    unsigned int get_revive_time() const override;
};


#endif //FLOWMAN_CHBONUS_H

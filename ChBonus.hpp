//
// Created by root on 6/30/17.
//

#ifndef FLOWMAN_CHBONUS_H
#define FLOWMAN_CHBONUS_H

#include "Character.hpp"
#include "LogWindow.hpp"

class ChBonus : public Character{
public:
    RDC(ChBonus);
    ChBonus(const Item::item_type_t it, Desk& desk, LogWindow& logWindow) : logWindow(logWindow), Character(it, desk, 1) {}
    virtual ~ChBonus() = default;
    void restart_position() override;
private:
    virtual direction_t get_next_position() override;
    virtual void process_new_square() override {};
    void update_character_status() override;
    virtual unsigned int get_revive_time() const override;
    LogWindow& logWindow;

    unsigned int ttl;
};


#endif //FLOWMAN_CHBONUS_H

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChHacker.hpp
 * Author: Jan Pazdera
 *
 * Created on 18. října 2016, 21:37
 */

#ifndef CHHACKER_HPP
#define CHHACKER_HPP

#include "Character.hpp"
#include "LogWindow.hpp"


class ChHacker : public Character {
public:
	RDC(ChHacker);
	ChHacker(const Item::item_type_t it, Desk& desk, LogWindow& logWindow, const float speed_multiplier)
			: logWindow(logWindow), Character(it, desk, speed_multiplier) {}
    virtual ~ChHacker() = default;
	void restart_position() override;


private:
	virtual Character::direction_t get_next_position() override;
	virtual void process_new_square() override;
	direction_t dir; /**< current direction of character */
	bool check_next_position(const Character::direction_t dir) const;
	virtual void move_character(const direction_t dir) override;
	LogWindow& logWindow;

protected:
	virtual unsigned int get_revive_time() const override;
};

#endif /* CHHACKER_HPP */


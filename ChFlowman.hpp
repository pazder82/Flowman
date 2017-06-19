/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChFlowman.hpp
 * Author: Jan Pazdera
 *
 * Created on 9. října 2016, 13:39
 */

#ifndef CHFLOWMAN_HPP
#define CHFLOWMAN_HPP

#include "Character.hpp"


class ChFlowman : public Character {
public:
	RDC(ChFlowman);
	ChFlowman(const Item::item_type_t it, Desk& desk, const float speed_multiplier) : Character(it, desk, speed_multiplier) {}
    virtual ~ChFlowman();
	void report_pressed_key(const int keyp);

private:
	Character::direction_t get_next_position() const override; // return new position of character in next step
	virtual void process_new_square() override;

	int keyp = 0;
	

};

#endif /* CHFLOWMAN_HPP */


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
#include "LogWindow.hpp"
#include "GameStatus.hpp"


class ChFlowman : public Character {
public:
	RDC(ChFlowman);
	ChFlowman(const Item::item_type_t it, Desk& desk, LogWindow& logWindow, GameStatus& gameStatus, const float speed_multiplier)
			: logWindow(logWindow), gameStatus(gameStatus), Character(it, desk, speed_multiplier) {}
    virtual ~ChFlowman();
	void report_pressed_key(const int keyp);
	virtual int get_speed() const override;

private:
	virtual Character::direction_t get_next_position() override; // return new position of character in next step
	virtual void process_new_square() override;
	LogWindow& logWindow;
	GameStatus& gameStatus;
	void update_character_status() override;
	void animate_character() override {};

private:
	virtual unsigned int get_revive_time() const override;

private:

	int keyp = 0;
	

};

#endif /* CHFLOWMAN_HPP */


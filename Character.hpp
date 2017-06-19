/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.hpp
 * Author: Jan Pazdera
 *
 * Created on 10. září 2016, 22:38
 */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <chrono>
#include <thread>
#include "common.hpp"
#include "DrawableObject.hpp"
#include "Desk.hpp"

extern TS_ncurses tsn;

class Character {
public:
	enum direction_t { left, up, right, down };
	enum typeofdeath_t { norevive, revive, alive };

	RDC(Character);
	Character(const Item::item_type_t it, Desk& desk, const float speed_multiplier);
    virtual ~Character() = default;

	virtual void restart_position(); /**< Not thread-safe method. Can be called before run() or after kill(). */
	void terminate(); /** terminate character's thread */
	void run(); /**< start character's thread */
	void kill(const typeofdeath_t tod); /**< set status of chracter */
	unsigned short get_hpos() const { return hpos; }
	unsigned short get_vpos() const { return vpos; }
	square_coord_t get_pos() const { return { { hpos, vpos } }; }
	Item::item_type_t get_item_type() const { return it; }
	bool joinable() const;
	static vector<Character*> chvector; /**< Vector of references to all Character objects created */

protected:
	virtual direction_t get_next_position() const = 0; // return new position of character in next step
	virtual void process_new_square() = 0; // let character know it moved to the new square so it has to be processed
	virtual void move_character(const direction_t dir);
	Desk& desk; /**< Associated Desk */
	unsigned short hpos = 0; /**< Character horizontal position */
	unsigned short vpos = 0; /**< Character vertical position */
private:
	void run_i();

	Item::item_type_t it; /**< Item assigned to character */
	int speed; /**< Character speed in ms between each move */
	thread th; /**< Thread associated to object instance */
	bool quit = false; /**< Set to true to end the Character's main loop */
	typeofdeath_t tod = Character::norevive; /**< Set to alive to start characters action */
	static mutex mtx; /**< Mutex for thread safe access to tod */
	static mutex mtx_nc; /**< Mutex for thread safe access to ncurses */
	
};

#endif /* CHARACTER_HPP */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jan Pazdera
 *
 * Created on 9. září 2016, 21:07
 */

#include <cstdlib>
#include <ncurses.h>
#include <boost/thread/thread.hpp>
#include "common.hpp"
#include "Item.hpp"
#include "Desk.hpp"
#include "TS_ncurses.hpp"
#include "Character.hpp"
#include "ChFlowman.hpp"
#include "ChHacker.hpp"
#include "ChBonus.hpp"
#include "LogWindow.hpp"
#include "GameStatus.hpp"

using namespace std;

TS_ncurses tsn; // global object for use ncurses library in thread-safe manner

/**
 * init ncurses function - not thread safe, must be called before any thread created.
*/
void init_ncurses() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    timeout(-1); // use blocking getch
    start_color();
    curs_set(0);
}

/**
 * Draw intruduction picture
 */
void introduction() {
	// TODO:
	// draw something
}


/*
 * 
 */
int main(int argc, char** argv) {
	introduction();
    init_ncurses();

    // hack: this is necessary to properly display windows' content before first key is pressed

	tsn.ungetch('a');
	tsn.mgetch();

	// Create Desk, LogWindow and GameStatus objects
	Desk desk(DESKHSIZE, DESKVSIZE, 0, 0);
	LogWindow logWindow(DESKHSIZE, 1, 0, DESKVSIZE);
	GameStatus gameStatus;

	// Create Character objects
	ChFlowman flowman(Item::flowman, desk, logWindow, gameStatus, 1);
	ChHacker hacker1(Item::hacker, desk, logWindow, gameStatus, 0.5);
	ChHacker hacker2(Item::hacker, desk, logWindow, gameStatus, 0.8);
	ChHacker hacker3(Item::hacker, desk, logWindow, gameStatus, 1);
	ChHacker hacker4(Item::hacker, desk, logWindow, gameStatus, 1);
	ChHacker hacker5(Item::hacker, desk, logWindow, gameStatus, 1.2);
    ChBonus food(Item::bonus, desk, logWindow);

	// Fill Character vector
	Character::chvector.push_back(&flowman);
	Character::chvector.push_back(&hacker1);
	Character::chvector.push_back(&hacker2);
	Character::chvector.push_back(&hacker3);
	Character::chvector.push_back(&hacker4);
	Character::chvector.push_back(&hacker5);
	Character::chvector.push_back(&food);
	for (Character* ch : Character::chvector) {
		ch->run(); // start threads
	}

    int keyp = 'a'; // unused key
	bool game_started = true;
    while (!gameStatus.get_quit_status()) {
        if (game_started || (desk.get_num_of_items(Item::food) == 0)) {
            // Start new level - kill all characters with no deadrevive before we init the desk
			for (Character* ch : Character::chvector) ch->kill(Character::deadnorevive);
			desk.init_squares();
			gameStatus.restart_lives();
			gameStatus.inc_level();
			logWindow.draw();
			logWindow.update_level(gameStatus.get_level());
			logWindow.update_lives(gameStatus.get_lives());
			logWindow.update_score(gameStatus.get_score());
			game_started = false;
			for (Character* ch : Character::chvector) ch->kill(Character::deadrevive);
        } else if ((keyp == KEY_LEFT) || (keyp == KEY_RIGHT) || (keyp == KEY_UP) || (keyp == KEY_DOWN)) {
            // Move Flowman
			flowman.report_pressed_key(keyp);
		}
    	keyp = tsn.mgetch();
        if (keyp == KEY_F(10)) {
            gameStatus.quit_game();
        }
    }
	for (Character* ch : Character::chvector) {
		// terminate all character threads
		ch->terminate();
	}

    tsn.endwin();
    return 0;
}


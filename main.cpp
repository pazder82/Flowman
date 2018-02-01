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
#include "ChEvidence.hpp"
#include "LogWindow.hpp"
#include "GameStatus.hpp"
#include "PopupWindow.hpp"

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
    timeout(10); // block getch for X ms
    start_color();
    curs_set(0);
}

string get_level_message(unsigned int level) {
	switch (level) {
        case 1 :
            return "\
                Level 1\n\n\
                Warm up!";
		case 2 :
			return "\
                Level 2\n\n\
You're not alone in your network! There is\n\
a hacker with you. You must avoid him.\n\
The hacker can be tracked and removed,\n\
if you find an evidence. When evidence found\n\
the hacker turns green and can be removed if\n\
you catch him. But stay alarmed! The hacker\n\
will notice you shortly. Once he starts\n\
alternate red and green, you can still remove\n\
him, but he will turn back red in a moment!";
		default:
			return "\
               Level "+to_string(level)+"\n\n\
   More hackers and more speed!";
	}
}

/**
 * Init game parameters based on game level
 */
void init_game(GameStatus& gameStatus, Desk& desk, LogWindow& logWindow) {
	// Start new level
	// Kill all characters with no deadrevive before we init the desk
	for (Character* ch : Character::chvector) ch->kill(Character::deadnorevive);

    desk.init_squares(gameStatus.get_level()); // Generate new labyrinth
	gameStatus.restart_lives(); // Reset number of lives on default value
	gameStatus.inc_level(); // Increase level number

    // Draw window with info about level, no. of lives and score
	logWindow.draw();
	logWindow.update_level(gameStatus.get_level());
	logWindow.update_lives(gameStatus.get_lives());
	logWindow.update_score(gameStatus.get_score());

    // Display message box with level info
    PopupWindow popupWindow(50, 20, 15, 2, get_level_message(gameStatus.get_level()));
	popupWindow.draw();
	while(tsn.mgetch() == ERR); // wait for any key
    desk.draw(); // Hide message box

    // Start level - revive all characters
	unsigned short num_of_hackers = 0;
	for (Character* ch : Character::chvector) {
		// revive number of hackers equal to level - 1
		if (dynamic_cast<ChHacker*>(ch)) {
			if (++num_of_hackers < gameStatus.get_level()) {
				ch->kill(Character::deadrevive);
			}
		} else {
			ch->kill(Character::deadrevive);
		}
	}
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
    ChEvidence evidence(Item::bonus, desk, logWindow);

	// Fill Character vector
	Character::chvector.push_back(&flowman);
	Character::chvector.push_back(&evidence);
	Character::chvector.push_back(&hacker5);
	Character::chvector.push_back(&hacker4);
	Character::chvector.push_back(&hacker3);
	Character::chvector.push_back(&hacker2);
	Character::chvector.push_back(&hacker1);
	for (Character* ch : Character::chvector) {
		ch->run(); // start threads
	}

    int keyp = 'a'; // unused key
    while (!gameStatus.get_quit_status()) {
        if (gameStatus.get_start_new_level_status()) {
            // Start new level - kill all characters with no deadrevive before we init the desk
            init_game(gameStatus, desk, logWindow);
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


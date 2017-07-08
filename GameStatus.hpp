//
// Created by root on 7/8/17.
//

#ifndef FLOWMAN_GAMESTATUS_H
#define FLOWMAN_GAMESTATUS_H

#include <mutex>
#include "common.hpp"

using namespace std;

#define LOCK lock_guard<mutex> lck(mtx)

class GameStatus {
public:
    RDC_D(GameStatus);
    GameStatus() = default;
    virtual ~GameStatus() = default;
    void inc_life() { LOCK; lives++; }
    void inc_lives(unsigned int l) { LOCK; lives += l; }
    void dec_life() { LOCK; lives--; }
    void dec_lives(unsigned int l) { LOCK; lives -= l; }
    void quit_game() {LOCK; quit = true; }
    unsigned int get_lives() const { return lives; }
    unsigned int inc_score(unsigned int s) { LOCK; score += s; }
    unsigned int get_score() const { return score; }
    bool get_quit_status() const { return quit; }

private:
    mutex mtx;
    unsigned int lives = STARTING_LIVES;
    unsigned int score = 0;
    bool quit = false;
};


#endif //FLOWMAN_GAMESTATUS_H

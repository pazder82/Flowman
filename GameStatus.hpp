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
    void restart_lives() { LOCK; lives = STARTING_LIVES; }
    void quit_game() {LOCK; quit = true; }
    unsigned int get_lives() const { return lives; }
    void inc_score(unsigned int s) { LOCK; score += s; }
    unsigned int get_score() const { return score; }
    unsigned int get_level() const { return level > 0 ? level : 1; }
    void inc_level() { LOCK; level++; start_new_level_status = false; }
    bool get_quit_status() const { return quit; }
    bool get_start_new_level_status() const { return start_new_level_status; }
    void start_new_level() { LOCK; start_new_level_status = true; }

private:
    mutex mtx;
    unsigned int lives = STARTING_LIVES;
    unsigned int score = 0;
    unsigned int level = 0;
    bool quit = false;
    bool start_new_level_status = true;
};


#endif //FLOWMAN_GAMESTATUS_H

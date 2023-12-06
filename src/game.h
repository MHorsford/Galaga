#ifndef GAME_H
#define GAME_H
#include <iostream>
using std::cin;
#include "fighter.h"
#include "enemy.h"
#include "enemyWave.h"



class Game{
    public:
    // loop principal do jogo
    void play();
    void update();
    void draw();
    private:


};
#endif
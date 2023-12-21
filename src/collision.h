#ifndef COLLISION_H
#define COLLISION_H
#include <iostream>
#include "enemyWave.h"


class Bullet;
class Collision{
    public:
    void waveCollision(EnemyWave& wave, Enemy& newEnemy);
    bool checkCollision(Fighter& fighter, Enemy& enemy, Bullet& bullet);

};

#endif
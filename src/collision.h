#ifndef COLLISION_H
#define COLLISION_H
#include <iostream>
#include "enemyWave.h"


class Collision{
    public:

    // Verifica se no vetor existe um inimigo com a mesma posição(X) que o inimigo que ira ser adicionado
    void waveCollision(EnemyWave& wave, Enemy& newEnemy);
    //void bulletCollision();
    private:
};

#endif
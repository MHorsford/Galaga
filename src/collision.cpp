#include "collision.h"


void Collision::waveCollision(EnemyWave& wave, Enemy& newEnemy){
    if (wave.getWaveEnemy().empty()){
        wave.addEnemy(newEnemy);
        return;
    }
    
    for (const Enemy& existingEnemy : wave.getWaveEnemy()){
        if (existingEnemy.get_positionX() == newEnemy.get_positionX()){
            newEnemy.set_positionX(newEnemy.get_positionX() + 10);     
        }
    }
    wave.addEnemy(newEnemy);
    
};
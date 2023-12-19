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

bool Collision::checkCollision(Fighter& fighter, Enemy& enemy, Bullet& bullet){
    if (bullet.get_isPlayerBullet() && bullet.get_positionX() == enemy.get_positionX() 
        && bullet.get_positionY() == enemy.get_positionY()){
        return true;
    } else if (!bullet.get_isPlayerBullet() && bullet.get_positionX() == fighter.get_positionX() 
        && bullet.get_positionY() == fighter.get_positionY()){
        return true;
    }
    return false;
};


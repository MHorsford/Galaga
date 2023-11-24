#include "bullet.h"


Bullet::Bullet(){}
Bullet::Bullet(double bulletX, double bulletY, bool isPlayerBullet) 
        : bulletX(bulletX), bulletY(bulletY), isPlayerBullet(true),speed(5.0), active(false) {};



void Bullet::moveBullet(){
    if (isPlayerBullet){
        bulletY -= speed;
    } else{
        bulletY += speed; 
    }
};
void Bullet::updateBullet(){};
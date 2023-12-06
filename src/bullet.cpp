#include "bullet.h"


Bullet::Bullet(){}
Bullet::Bullet(double bulletX, double bulletY, bool isPlayerBullet) 
        : bulletX(bulletX), bulletY(bulletY), isPlayerBullet(true),speed(5.0), active(false) {};
Bullet::Bullet(const Bullet& copyBullet) 
        : bulletX(copyBullet.bulletX), bulletY(copyBullet.bulletY), isPlayerBullet(copyBullet.isPlayerBullet), speed(5.0), active(false) {}


void Bullet::moveBullet(){
    if (isPlayerBullet){
        bulletY -= speed;
    } else{
        bulletY += speed;
    }
};

// Laser
Laser::Laser() : Bullet() {}
Laser::Laser(double bulletX, double bulletY, bool isPlayerBullet)
        : Bullet(bulletX, bulletY, isPlayerBullet) {}
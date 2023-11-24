#ifndef BULLET_H
#define BULLET_H
#include "fighter.h"
//#include "enemy.h"


class Bullet{

    public:
    Bullet();
    Bullet(double bulletX, double bulletY, bool isPlayerBullet);
    Bullet(const Bullet& copyBullet);

    void moveBullet(){};
    void updateBullet(){};

    private:
    int bulletX;
    int bulletY;
    double speed;
    bool active;
    bool isPlayerBullet;
    static const double MAX_SPEED;

};

class Laser: public Bullet{
    public:
    Laser();
    Laser(double bulletX, double bulletY, double speed, bool active);
    Laser(const Laser& copyLaser);
    private:
};

#endif
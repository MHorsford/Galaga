#ifndef BULLET_H
#define BULLET_H
#include "fighter.h"
#include "enemy.h"




//Declaração antecipada
class Collision;


class Bullet{

    public:
    Bullet();
    Bullet(double bulletX, double bulletY, bool isPlayerBullet);
    Bullet(const Bullet& copyBullet);

    void moveBullet();
    bool destroyBullet();
    bool get_isPlayerBullet() const;
    double get_positionX() const;
    double get_positionY() const;

    private:
    double bulletX;
    double bulletY;
    double speed;
    bool active;
    bool isPlayerBullet;
    static const double MAX_SPEED;

};

class Laser: public Bullet{
    public:

    Laser();
    Laser(double bulletX, double bulletY, bool isPlayerBullet);
    Laser(const Laser& copyLaser);

    void continuousDamage(Interceptor& interceptor, Enemy& enemy, Collision& collision);

};

class Missile: public Laser{
    public:
    Missile();
    Missile(double bulletX, double bulletY, bool isPlayerBullet);
    Missile(const Missile& copyMissile);

    void explosiveDamage(Destroyer& destroyer, Enemy& enemy, Collision& collision);
};

#endif
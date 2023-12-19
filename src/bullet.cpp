#include "bullet.h"
#include "collision.h"


Bullet::Bullet(){}
Bullet::Bullet(double bulletX, double bulletY, bool isPlayerBullet) 
        : bulletX(bulletX), bulletY(bulletY), isPlayerBullet(true),speed(5.0), active(false) {};
Bullet::Bullet(const Bullet& copyBullet) 
        : bulletX(copyBullet.bulletX), bulletY(copyBullet.bulletY), isPlayerBullet(copyBullet.isPlayerBullet), speed(5.0), active(false) {}


void Bullet::moveBullet(){
    if (isPlayerBullet){
        bulletY += speed;
    } else{
        bulletY -= speed;
    }
}
// refatorar
bool Bullet::destroyBullet(){
    if (!active){
        return true;
    }
    return false;
}

double Bullet::get_positionX() const {
    return bulletX;
}
bool Bullet::get_isPlayerBullet() const {
    return isPlayerBullet;
}

double Bullet::get_positionY() const {
    return bulletY;
}

// Laser
Laser::Laser() : Bullet() {}
Laser::Laser(double bulletX, double bulletY, bool isPlayerBullet)
        : Bullet(bulletX, bulletY, isPlayerBullet) {}
Laser::Laser(const Laser& copyLaser)
        : Bullet(copyLaser) {}

void Laser::continuousDamage(Interceptor& interceptor, Enemy& enemy, Collision& collision) {
    if (collision.checkCollision(interceptor, enemy, *this)){
        if (!this->get_isPlayerBullet()){
            while(enemy.isAlive()){
                enemy.set_health(enemy.get_health() - 100);
                if (enemy.get_health() <= 0){
                    enemy.set_health(0);
                    enemy.defeat();
                    break;
                }
            } 
        }
    }
}

Missile::Missile() : Laser() {}
Missile::Missile(double bulletX, double bulletY, bool isPlayerBullet)
        : Laser(bulletX, bulletY, isPlayerBullet) {}
Missile::Missile(const Missile& copyMissile): Laser(copyMissile) {}

void Missile::explosiveDamage(Destroyer& destroyer, Enemy& enemy, Collision& collision) {
    if (collision.checkCollision(destroyer, enemy, *this)){
        if (!this->get_isPlayerBullet()){
            int enemyPosition = enemy.get_positionX();
            int enemyIndex = -1;
            EnemyWave* wave = new EnemyWave();

            for (int i = 0; i < wave->getWaveEnemy().size(); i++) {
                if (wave->getWaveEnemy()[i].get_positionX() == enemyPosition) {
                    enemyIndex = i;
                    break;
                }
            }

            // Verificar se o inimigo foi encontrado
            if (enemyIndex != -1) {
                // Verifica se há um inimigo à esquerda
                if (enemyIndex > 0) {
                    Enemy& leftEnemy = const_cast<Enemy&>(wave->getWaveEnemy()[enemyIndex - 1]);
                    int damage = destroyer.get_atk() / 2;
                    leftEnemy.set_health(leftEnemy.get_health() - damage);
                    if (leftEnemy.get_health() <= 0) {
                        leftEnemy.set_health(0);
                        leftEnemy.defeat();
                    }
                }                
                // Verifica se há um inimigo à direita
                if (enemyIndex < wave->getWaveEnemy().size() - 1) {
                    Enemy& leftEnemy = const_cast<Enemy&>(wave->getWaveEnemy()[enemyIndex + 1]);
                    int damage = destroyer.get_atk() / 2;
                    leftEnemy.set_health(leftEnemy.get_health() - damage);
                    if (leftEnemy.get_health() <= 0) {
                        leftEnemy.set_health(0);
                        leftEnemy.defeat();
                    }
                }
            } 
        }
    }
}

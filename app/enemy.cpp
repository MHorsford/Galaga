#include "enemy.h"

Enemy::Enemy() : name("Enemy"), health(100), damage(1000), speed(1.0), alive(true) {}
Enemy::Enemy(const std::string name, int health, const int damage, double speed, bool alive)
    : name(name), health(health), damage(damage), speed(speed), alive(alive) {}
Enemy::Enemy(const Enemy& copyEnemy)
    : name(copyEnemy.name), health(copyEnemy.health), damage(copyEnemy.damage), speed(copyEnemy.speed),
      alive(copyEnemy.alive) {}


void Enemy::attack(Fighter& target) const{
    if(target.isAlive()) {
        target.set_health(target.get_health() - damage);
        if (target.get_health() == 0){
            target.defeat();  // Lutador morto
            cout<< "Fighter destruido!!!"<< endl;
        }
        else{
            cout<< "Fighter Sobreviveu!!!"<< endl;
        }
    }
}
void Enemy::limitNameLength(const int MAXLENGTH) {
    if (name.length() > MAXLENGTH) {
        name = name.substr(0, MAXLENGTH);
        cout << "\nNome alterado. Excedeu o valor maximo. \n";
    }
}
void Enemy::move(){}

void Enemy::defeat(){
    alive = false;
}

// set e get

void Enemy::set_name(const std::string newName){
    this->name = newName;
}
std::string Enemy::get_name() const{
    return name;
}

void Enemy::set_health(int newHealth){
    this->health = newHealth;
}
int Enemy::get_health() const{
    return health;
}

void Enemy::set_speed(double newSpeed){
    this->speed = newSpeed;
}
double Enemy::get_speed() const{
    return speed;
}

int Enemy::get_damage() const {
    return damage;
}


void Enemy::setIsAlive(bool value) {
    alive = value;
}

bool Enemy::isAlive() const {
    return alive;
}

void Enemy::getInfo() const{
    cout << "Nome: " << name << endl;
    cout << "Pontos de Vida: " << health << endl;
    cout << "Status(alive): " << alive <<endl;
    cout << "Velocidade: " << speed << endl;
    cout << "Forca de Ataque: " << damage << endl;
}
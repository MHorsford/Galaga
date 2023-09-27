#include "fighter.h"


Fighter::Fighter(): name("Fighter"), health(1000), speed(100.0), atk(100), alive(true) {};
Fighter::Fighter(const std::string name, int health, double speed, int atk, bool alive)
        : name(name), health(health), speed(speed), atk(atk), alive(alive) {};
Fighter::Fighter(const Fighter& copyFighter)
    : name(copyFighter.name), health(copyFighter.health), speed(copyFighter.speed), atk(copyFighter.atk),
      alive(copyFighter.alive) {}


// metodos
void Fighter::move(){
    double originSpeed = speed;  // Armazena a velocidade padão
    speed += 20.0;
    cout<<name<<" esta se movendo mais rapido!!! "<< speed<<endl;

    for (int i=0; i < 2; i++){
         cout<<"Turno " << i + 1 << ": Movimento rapido ainda ativo." <<endl;
    }

    speed = originSpeed;
    cout << "Movimento rapido expirou. Velocidade restaurada para " << speed <<endl;
}

void Fighter::specialAbility(){
    int originAtk = atk;  // Armazena o atk padrão
    atk +=10;
    cout<<name<<" aumentou o ataque!!! "<<atk<<endl;

    for (int i=0; i < 3; i++){
         cout<<"Turno " << i + 1 << ": Habilidade especial ainda ativa." <<endl;
    }

    atk = originAtk;
    cout << "Habilidade especial expirou. Ataque restaurado para " << atk <<endl;
}

void Fighter::defeat(){
    alive = false;
}

// set e get

void Fighter::set_name(const std::string newName){
    this->name = newName;
}
std::string Fighter::get_name() const{
    return name;
}

void Fighter::set_health(int newHealth){
    this->health = newHealth;
}
int Fighter::get_health() const{
    return health;
}

void Fighter::set_speed(double newSpeed){
    this->speed = newSpeed;
}
double Fighter::get_speed() const{
    return speed;
}

void Fighter::set_atk(int newAtk){
    this->atk = newAtk;
}
int Fighter::get_atk() const{
    return atk;
}

void Fighter::setIsAlive(bool value) {
    alive = value;
}

bool Fighter::isAlive() const {
    return alive;
}

void Fighter::getInfo() const{
    cout << "Nome: " << name << endl;
    cout << "Pontos de Vida: " << health << endl;
    cout << "Status(alive): " << alive <<endl;
    cout << "Velocidade: " << speed << endl;
    cout << "Forca de Ataque: " << atk << endl;
}


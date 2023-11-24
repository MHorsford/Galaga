#include "fighter.h"
#include "enemyWave.h"
#include "bullet.h"


Fighter::Fighter(): name("Player_1"), health(5000), speed(7.0), damage(100),posiX(0.0), posiY(0.0), alive(true) {};
Fighter::Fighter(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive)
        : name(name), health(health), speed(speed), damage(damage), posiX(posiX), posiY(posiY), alive(alive) {};
Fighter::Fighter(const Fighter& copyFighter)
    : name(copyFighter.name), health(copyFighter.health), speed(copyFighter.speed), damage(copyFighter.damage),
      posiX(copyFighter.posiX), posiY(copyFighter.posiY), alive(copyFighter.alive) {}
Fighter::~Fighter(){
    for (size_t i = 0; i < fighterBullet.size(); i++){
        delete fighterBullet[i];
    }
}


// metodos
void Fighter::move(){
    double originSpeed = speed;  // Armazena a velocidade padão
    speed += 20.0;
    cout<<name<<" esta se movendo mais rapido!!! "<< speed<<"\n";

    for (int i=0; i < 2; i++){
         cout<<"Turno " << i + 1 << ": Movimento rapido ainda ativo." <<"\n";
    }

    speed = originSpeed;
    cout << "Movimento rapido expirou. Velocidade restaurada para " << speed <<"\n";
}

void Fighter::specialAbility(){
    int originAtk = damage;  // Armazena o damage padrão
    damage +=10;
    cout<<name<<" aumentou o ataque!!! "<<damage<<"\n";

    for (int i=0; i < 3; i++){
         cout<<"Turno " << i + 1 << ": Habilidade especial ainda ativa." <<"\n";
    }

    damage = originAtk;
    cout << "Habilidade especial expirou. Ataque restaurado para " << damage <<"\n";
}

void Fighter::shootBullet(double bulletX, double bulletY, bool isPlayerBullet){
    Bullet* newBullet = new Bullet(posiX, posiY, true);
    fighterBullet.push_back(newBullet); 
}

void Fighter::attack(EnemyWave& target) {
    if (!target.enemies.empty()){
        for (Enemy& enemy : target.enemies){
            if (enemy.isAlive()){
                enemy.set_health(enemy.get_health() - damage);
                if (enemy.get_health() < 0){
                    enemy.set_health(0);
                }
                enemy.defeat();
                calculatePlayerScore(enemy);
            }
        }
    }
}

void Fighter::addPowerUp(const std::string& name, int effect) {
    if (powerUps.size() < 3) {
        PowerUp newPowerUp = {name, effect};
        powerUps.push_back(newPowerUp);
    } else {
        std::cout << "Voce ja possui 3 power-ups. Nao e possivel adicionar mais." << std::endl;
    }
}


void Fighter::calculatePlayerScore(const Enemy& enemy){
    if(!enemy.isAlive()){

        playerScore[name] += enemy.get_score();
    } 
}

int Fighter::get_score(const std::string name) const {
    auto it = playerScore.find(name); // encontra o Fighter
    if (it != playerScore.end()){
        return it->second;
    }
    return 0;
}

std::map<std::string, int> Fighter::getPlayerScore() const{
    return playerScore;
}

void Fighter::defeat(){
    alive = false;
}

void Fighter::loadConfig(const string& filename){
    configManager = ConfigManager("data/" + filename + ".txt");
    if (configManager.loadConfig()){
        name = configManager.getValue("name");
        health = stoi(configManager.getValue("health"));
        speed = stod(configManager.getValue("speed"));
        damage = stoi(configManager.getValue("damage"));
        posiX = stoi(configManager.getValue("posiX"));
        posiY = stoi(configManager.getValue("posiY"));
        alive = (configManager.getValue("alive") == "true") ? true : false;
    } else{
        throw std::runtime_error("Nao foi possível carregar o arquivo de configuraçao.\n");
    }
}
void Fighter::saveConfig(){
    configManager = ConfigManager("data/" + get_name() + ".txt");
    configManager.setValue("name", name);
    configManager.setValue("health", to_string(health));
    configManager.setValue("speed", to_string(speed));
    configManager.setValue("damage", to_string(damage));
    configManager.setValue("posiX", to_string(posiX));
    configManager.setValue("posiY", to_string(posiY));
    configManager.setValue("alive", alive ? "true" : "false");
    if (!configManager.saveConfig()){
        throw std::runtime_error("Não foi possível salvar o arquivo de configuração.\n");
    }
}


// operators

std::ostream& operator<<(std::ostream& out, const Fighter& fighter){
    out<< "Name: " << fighter.name <<"\n";
    out<< "Hp: " << fighter.health <<"\n";
    out<< "Damage: " << fighter.damage <<"\n";
    out<< "Position X: " << fighter.posiX << " | " << "Position Y" << fighter.posiY <<"\n";
    out<< "Alive: " << (fighter.alive ? "Yes" : "No") <<"\n";
    return out;
}


// set e get

void Fighter::set_name(const std::string newName){
    this->name = newName;
}
std::string Fighter::get_name() const{
    return name;
}

void Fighter::set_positionX(double newPosiX){
    this->posiX = newPosiX;
}
void Fighter::set_positionY(double newPosiY){
    this->posiY = newPosiY;
}
double Fighter::get_positionX() const{
    return posiX;
}
double Fighter::get_positionY() const{
    return posiY;
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
    this->damage = newAtk;
}
int Fighter::get_atk() const{
    return damage;
}

void Fighter::setIsAlive(bool value) {
    alive = value;
}

bool Fighter::isAlive() const {
    return alive;
}

Data Fighter::getUserData() const {
    return data;
}
void Fighter::printUserData() const {
    std::cout << "User Date: " << data.toString() <<"\n\n";
}


// Class Interceptor
Interceptor::Interceptor(): Fighter("Interceptor", 7000, 10.0, 75, 0, 0, true) {}
Interceptor::Interceptor(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive)
            : Fighter(name, health, speed, damage, posiX, posiY, alive) {}
Interceptor::Interceptor(const Interceptor& copyInterceptor): Fighter(copyInterceptor) {}

void Interceptor::shootBullet(double bulletX, double bulletY, bool isPlayerBullet){
    Bullet* newBullet1 = new Bullet(bulletX, bulletY, true);
    Bullet* newBullet2 = new Bullet(bulletX, bulletY, true);
    fighterBullet.push_back(newBullet1);
    fighterBullet.push_back(newBullet2);
}
    
// Class Destroyer
Destroyer::Destroyer(): Fighter("Destroyer", 15000, 4.0, 100, 0, 0, true) {}
Destroyer::Destroyer(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive)
            : Fighter(name, health, speed, damage, posiX, posiY, alive) {}
Destroyer::Destroyer(const Destroyer& copyDestroyer): Fighter(copyDestroyer) {}

void Destroyer::shootBullet(double bulletX, double bulletY, bool isPlayerBullet){
    Bullet* newBullet1 = new Bullet(bulletX, bulletY, true);
    Bullet* newBullet2 = new Bullet(bulletX, bulletY, true);
    Bullet* newBullet3 = new Bullet(bulletX, bulletY, true);
    fighterBullet.push_back(newBullet1);
    fighterBullet.push_back(newBullet2);
    fighterBullet.push_back(newBullet3);
}
#include "fighter.h"
#include "enemyWave.h"
#include "bullet.h"

// Constructors
SpaceShip::SpaceShip() {}

SpaceShip::SpaceShip(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive):
                     name(name), health(health), speed(speed), damage(damage), posiX(posiX), posiY(posiY), alive(alive) {}

SpaceShip::SpaceShip(const SpaceShip& copySpaceShip): name(copySpaceShip.name), health(copySpaceShip.health), speed(copySpaceShip.speed),
                     damage(copySpaceShip.damage), posiX(copySpaceShip.posiX), posiY(copySpaceShip.posiY), alive(copySpaceShip.alive) {}

// 
SpaceShip::~SpaceShip() {}

const double SpaceShip::MAX_SPEED = 10.0;
const int SpaceShip::MAX_HEALTH = 5000;
SpaceShip::BulletType SpaceShip::currentBullet = SpaceShip::BulletType::BULLET;

void SpaceShip::addPowerUp(PowerUp* newpowerUp){
    powerUps.push_back(newpowerUp);
}
void SpaceShip::applyEffects(){
    if (!isAlive()){
        for (auto it = powerUps.begin(); it != powerUps.end();){
            PowerUp* powerUp = *it;
            if (powerUp->type == PowerUp::Type::HEALTH){
                health += powerUp->value;
                if (health > MAX_HEALTH){
                    health = MAX_HEALTH;
                }
                it = powerUps.erase(it);
            } else {
                ++it;
            }
        }   
    }
}

// setters and getters
void SpaceShip::set_name(const std::string newName){
    this->name = newName;
}
std::string SpaceShip::get_name() const{
    return name;
}

void SpaceShip::set_positionX(double newPosiX){
    this->posiX = newPosiX;
}
void SpaceShip::set_positionY(double newPosiY){
    this->posiY = newPosiY;
}
double SpaceShip::get_positionX() const{
    return posiX;
}
double SpaceShip::get_positionY() const{
    return posiY;
}

void SpaceShip::set_health(int newHealth){
    this->health = newHealth;
}
int SpaceShip::get_health() const{
    return health;
}

void SpaceShip::set_speed(double newSpeed){
    this->speed = newSpeed;
}
double SpaceShip::get_speed() const{
    return speed;
}

void SpaceShip::set_atk(int newAtk){
    this->damage = newAtk;
}
int SpaceShip::get_atk() const{
    return damage;
}

void SpaceShip::setIsAlive(bool value) {
    alive = value;
}

bool SpaceShip::isAlive() const {
    return alive;
}

//SpaceShipSkill construtores
SpaceShipII::SpaceShipII(): SpaceShip(){}

SpaceShipII::SpaceShipII(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive):
    SpaceShip(name, health, speed, damage, posiX, posiY, alive) {}
SpaceShipII::SpaceShipII(const SpaceShipII& copySpaceShipII): SpaceShip(copySpaceShipII) {}
SpaceShipII::~SpaceShipII() {}


Fighter::Fighter(): SpaceShipII("Default_Fighter", 5000, 7.0, 100,0.0, 0.0, true) {}
Fighter::Fighter(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive)
        : SpaceShipII(name, health, speed, damage, posiX, posiY, alive) {}
Fighter::Fighter(const Fighter& copyFighter)
    : SpaceShipII(copyFighter) {}
Fighter::~Fighter(){
    for (size_t i = 0; i < fighterBullet.size(); i++){
        delete fighterBullet[i];
    }
    fighterBullet.clear();
}


void Fighter::move(){
    double originSpeed = get_speed();  // Armazena a velocidade padão
    set_speed(get_speed() + 20.0);
    cout<<get_name()<<" esta se movendo mais rapido!!! "<< get_speed()<<"\n";

    for (int i=0; i < 2; i++){
         cout<<"Turno " << i + 1 << ": Movimento rapido ainda ativo." <<"\n";
    }

    set_speed(originSpeed);
    cout << "Movimento rapido expirou. Velocidade restaurada para " << get_speed() <<"\n";
}

void Fighter::specialAbility(){
    int originAtk = get_atk();
    set_atk(get_atk() +10);
    cout<<get_name()<<" aumentou o ataque!!! "<<get_atk()<<"\n";

    for (int i=0; i < 3; i++){
         cout<<"Turno " << i + 1 << ": Habilidade especial ainda ativa." <<"\n";
    }

    set_atk(originAtk);
    cout << "Habilidade especial expirou. Ataque restaurado para " << get_atk() <<"\n";
}

void Fighter::shootBullet(double bulletX, double bulletY, bool isPlayerBullet){
    Bullet* newBullet = new Bullet(get_positionX(), get_positionY(), true);
    fighterBullet.push_back(newBullet); 
}

void Fighter::update(){
    for (Bullet* bullet : fighterBullet){
        bullet->moveBullet();
    }
}

void Fighter::attack(EnemyWave& target) {
    if (!target.enemies.empty()){
        for (Enemy& enemy : target.enemies){
            if (enemy.isAlive()){
                enemy.set_health(enemy.get_health() - get_atk());
                if (enemy.get_health() < 0){
                    enemy.set_health(0);
                }
                enemy.defeat();
                calculatePlayerScore(enemy);
            }
        }
    }
}




void Fighter::calculatePlayerScore(const Enemy& enemy){
    if(!enemy.isAlive()){

        playerScore[get_name()] += enemy.get_score();
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
    setIsAlive(false);
}


void Fighter::evade(){
    Interceptor* interceptor = dynamic_cast<Interceptor*>(this);
    if (interceptor){
        interceptor->evade();
    } else {
        cout << "Evadir so esta disponivel para Interceptor." << "\n\n";
    }
}
void Fighter::shield(){
    Destroyer* destroyer = dynamic_cast<Destroyer*>(this);
    if (destroyer){
        destroyer->shield();
    } else {
        cout << "Escudo so esta disponivel para Destroyer." << "\n\n";
    }
}

void Fighter::loadConfig(const string& filename){
    configManager = ConfigManager("data/" + filename + ".txt");
    if (configManager.loadConfig()){
 
        set_name(configManager.getValue("name"));
        set_health(stoi(configManager.getValue("health")));
        set_speed(stod(configManager.getValue("speed")));
        set_atk(stoi(configManager.getValue("damage")));
        set_positionX(stod(configManager.getValue("posiX")));
        set_positionY(stod(configManager.getValue("posiY")));
        setIsAlive((configManager.getValue("alive") == "true") ? true : false);

    } else{
        throw std::runtime_error("Nao foi possível carregar o arquivo de configuraçao.\n");
    }
}
void Fighter::saveConfig(){
    configManager = ConfigManager("data/" + get_name() + ".txt");
    configManager.setValue("name", get_name());
    configManager.setValue("health", to_string(get_health()));
    configManager.setValue("speed", to_string(get_speed()));
    configManager.setValue("damage", to_string(get_atk()));
    configManager.setValue("posiX", to_string(get_positionX()));
    configManager.setValue("posiY", to_string(get_positionY()));
    configManager.setValue("alive", isAlive() ? "true" : "false");
    if (!configManager.saveConfig()){
        throw std::runtime_error("Não foi possível salvar o arquivo de configuração.\n");
    }
}

// getters
Data Fighter::getUserData() const {
    return data;
}
void Fighter::printUserData() const {
    std::cout << "User Date: " << data.toString() <<"\n\n";
}
vector<Bullet*> Fighter::getBullet() const{
    return fighterBullet;
}

// sobrecarga
std::ostream& operator<<(std::ostream& out, const Fighter& fighter){
    out<< "Name: " << fighter.get_name() <<"\n";
    out<< "Hp: " << fighter.get_health() <<"\n";
    out<< "Damage: " << fighter.get_atk() <<"\n";
    out<< "Position X: " << fighter.get_positionX() << " | " << "Position Y" << fighter.get_positionY() <<"\n";
    out<< "Alive: " << (fighter.isAlive() ? "Yes" : "No") <<"\n";
    return out;
}
Fighter& Fighter::operator=(const Fighter& otherFighter){
    if (*this != otherFighter){
        set_name(otherFighter.get_name());
        set_health(otherFighter.get_health());
        set_atk(otherFighter.get_atk());
        set_speed(otherFighter.get_speed());
        set_positionX(otherFighter.get_positionX());
        set_positionY(otherFighter.get_positionY());
        setIsAlive(otherFighter.isAlive());
    }
    return *this;
}
bool Fighter::operator==(const Fighter& otherFighter){
    return this->get_positionX() == otherFighter.get_positionX();
}
bool Fighter::operator!=(const Fighter& otherFighter){
    return !(*this == otherFighter);
}
bool Fighter::operator!(){
    return !isAlive();
}


// Class Interceptor
Interceptor::Interceptor(): Fighter("Default_Interceptor", 7000, 10.0, 75, 0, 0, true) {}
Interceptor::Interceptor(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive)
            : Fighter(name, health, speed, damage, posiX, posiY, alive) {}
Interceptor::Interceptor(const Interceptor& copyInterceptor): Fighter(copyInterceptor) {}

int Interceptor::laserCount = 0;


void Interceptor::shootBullet(double bulletX, double bulletY, bool isPlayerBullet){
    if (currentBullet == LASER){
        Bullet* newLaser = new Laser(bulletX, bulletY, true);
        if (typeid(*newLaser) == typeid(Laser)){
            fighterBullet.push_back(newLaser);
            cout<<"Municao a laser equipada"<<"\n";
        }
    } else{
        Bullet* newBullet1 = new Bullet(bulletX, bulletY, true);
        Bullet* newBullet2 = new Bullet(bulletX, bulletY, true);
        Bullet* newBullet3 = new Bullet(bulletX, bulletY, true);
        fighterBullet.push_back(newBullet1);
        fighterBullet.push_back(newBullet2);
        fighterBullet.push_back(newBullet3);
    }
}


void Interceptor::laser(){
    if (!currentBullet == LASER){
        if (laserCount < 10){
            currentBullet = LASER;
            laserCount++;
        } else {
            cout<<"O limite de laser foi atingido."<<"\n";
        }
    } else {
        currentBullet = BULLET;
    }
}

void Interceptor::evade(){
 
    double originSpeed = get_speed();
    set_speed(MAX_SPEED);
    // escolhe se vai para esquerda ou direita (A ou D).
    char direction;
    cout << "A - esquerda | D - direita: \n";
    cin >> direction;
    if(direction == 'A'){
        set_positionX(get_positionX() - get_speed());
    } else if(direction == 'D'){
        set_positionX(get_positionX() + get_speed());
    } else {
        cout << "Evadir so esta disponivel para direita e esquerda.";
    }
    set_speed(originSpeed);   
}

void Interceptor::shield(){
    Destroyer* destroyer = dynamic_cast<Destroyer*>(this);
    if (destroyer){
        destroyer->shield();
    } else {
        cout << "Escudo so esta disponivel para Destroyer." << "\n\n";
    }
}

//sobrecarga(utilizar static_cast se for necessario)
std::ostream& operator<<(std::ostream& out, const Interceptor& interceptor){
    out<< "Name: " << interceptor.get_name() <<"\n";
    out<< "Hp: " << interceptor.get_health() <<"\n";
    out<< "Damage: " << interceptor.get_atk() <<"\n";
    out<< "Position X: " << interceptor.get_positionX() << " | " << "Position Y" << interceptor.get_positionY() <<"\n";
    out<< "Alive: " << (interceptor.isAlive() ? "Yes" : "No") <<"\n";
    return out;
}
Interceptor& Interceptor::operator=(const Interceptor& otherInterceptor){
    if (*this != otherInterceptor){
        set_name(otherInterceptor.get_name());
        set_health(otherInterceptor.get_health());
        set_atk(otherInterceptor.get_atk());
        set_speed(otherInterceptor.get_speed());
        set_positionX(otherInterceptor.get_positionX());
        set_positionY(otherInterceptor.get_positionY());
        setIsAlive(otherInterceptor.isAlive());
    }
    return *this;
}
bool Interceptor::operator==(const Interceptor& otherInterceptor){
    return this->get_positionX() == otherInterceptor.get_positionX();
}
bool Interceptor::operator!=(const Interceptor& otherInterceptor){
    return !(*this == otherInterceptor);
}
bool Interceptor::operator!(){
    return !isAlive();
}
 

// Class Destroyer
Destroyer::Destroyer(): Interceptor("Default_Destroyer", 15000, 4.0, 100, 0, 0, true) {}
Destroyer::Destroyer(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive)
            : Interceptor(name, health, speed, damage, posiX, posiY, alive) {}
Destroyer::Destroyer(const Destroyer& copyDestroyer): Interceptor(copyDestroyer) {}



int Destroyer::missileCount = 0;

void Destroyer::shootBullet(double bulletX, double bulletY, bool isPlayerBullet){
    if (currentBullet == MISSILE){
        Bullet* newMissile = new Missile(bulletX, bulletY, true);
        if (typeid(*newMissile) == typeid(Missile)){
            fighterBullet.push_back(newMissile);
            cout<<"Municao a laser equipada"<<"\n";
        }
    } else{
        Bullet* newBullet1 = new Bullet(bulletX, bulletY, true);
        Bullet* newBullet2 = new Bullet(bulletX, bulletY, true);
        Bullet* newBullet3 = new Bullet(bulletX, bulletY, true);
        fighterBullet.push_back(newBullet1);
        fighterBullet.push_back(newBullet2);
        fighterBullet.push_back(newBullet3);
    }
}


void Destroyer::missile(){
    if (!currentBullet == MISSILE){
        if (missileCount < 10){
            currentBullet = MISSILE;
            missileCount++;
        } else {
            cout<<"O limite de misseis foi atingido."<<"\n";
        }
    } else {
        currentBullet = BULLET;
    }
}

void Destroyer::evade(){
    Interceptor* interceptor = dynamic_cast<Interceptor*>(this);
    if (interceptor){
        interceptor->evade();
    } else {
        cout << "Evadir so esta disponivel para Interceptor." << "\n\n";
    }
}

void Destroyer::shield(){
    int originHealth = get_health();
    int shieldHealth = 2000;
    set_health(get_health() + shieldHealth);
    if (get_health() <= originHealth){
        cout<<"O escudo foi quebrado."<<"\n";
    }
}

// sobrecarga
std::ostream& operator<<(std::ostream& out, const Destroyer& destroyer){
    out<< "Name: " << destroyer.get_name() <<"\n";
    out<< "Hp: " << destroyer.get_health() <<"\n";
    out<< "Damage: " << destroyer.get_atk() <<"\n";
    out<< "Position X: " << destroyer.get_positionX() << " | " << "Position Y" << destroyer.get_positionY() <<"\n";
    out<< "Alive: " << (destroyer.isAlive() ? "Yes" : "No") <<"\n";
    return out;
}
Destroyer& Destroyer::operator=(const Destroyer& otherDestroyer){
    if (*this != otherDestroyer){
        set_name(otherDestroyer.get_name());
        set_health(otherDestroyer.get_health());
        set_atk(otherDestroyer.get_atk());
        set_speed(otherDestroyer.get_speed());
        set_positionX(otherDestroyer.get_positionX());
        set_positionY(otherDestroyer.get_positionY());
        setIsAlive(otherDestroyer.isAlive());
    }
    return *this;
}
bool Destroyer::operator==(const Destroyer& otherDestroyer){
    return this->get_positionX() == otherDestroyer.get_positionX();
}
bool Destroyer::operator!=(const Destroyer& otherDestroyer){
    return !(*this == otherDestroyer);
}
bool Destroyer::operator!(){
    return !isAlive();
}


// Power Up
PowerUp::PowerUp(Type type): type(type) {
    switch (type){
        case Type::HEALTH:
            value = 1000;
            break;
        case Type::SPEED:
            value = 0;
            break;
        case Type::DAMAGE:
            value = 0;
            break;
        default:
            break;
    }
}
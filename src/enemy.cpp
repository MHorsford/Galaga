#include "enemy.h"


//Enemy Constuctor
Enemy::Enemy() : name("Enemy"), health(1000), damage(100), speed(7.0), posiX(0.0), posiY(50.0), score(100), alive(true) {}
Enemy::Enemy(const string name, int health, int damage, double speed, double posiX, double posiY, int score, bool alive)
    : name(name), health(health), damage(damage), speed(speed), posiX(posiX), posiY(posiY), score(score), alive(alive) {}
Enemy::Enemy(const Enemy& copyEnemy)
    : name(copyEnemy.name), health(copyEnemy.health), damage(copyEnemy.damage), speed(copyEnemy.speed),
      posiX(copyEnemy.posiX), posiY(copyEnemy.posiY), score(copyEnemy.score), alive(copyEnemy.alive) {}
Enemy::~Enemy(){
    for (size_t i = 0; i < enemyBullet.size(); i++){
        delete enemyBullet[i];
    }
}

void Enemy::attack(Fighter& target) const{
    if(target.isAlive()) {
        target.set_health(target.get_health() - damage);
        if (target.get_health() == 0){
            target.defeat();  // Lutador morto
            cout<< "Fighter destruido!!!"<< "\n";
        }
        else{
            cout<< "Fighter Sobreviveu!!!"<< "\n";
        }
    }
}

void Enemy::shootBullet(double bulletX, double bulletY, bool isPlayerBullet){
    Bullet* newBullet = new Bullet(bulletX, bulletY, false);
    enemyBullet.push_back(newBullet);
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

//Sobrecarga

bool Enemy::operator==(const Enemy& otherEnemy) const {
    return this->get_positionX() == otherEnemy.get_positionX();
}
bool Enemy::operator!() const{
    return !isAlive();
}
bool Enemy::operator!=(const Enemy& otherEnemy) const{
    return !(*this == otherEnemy);
}

Enemy& Enemy::operator=(const Enemy& otherEnemy){
    if (*this != otherEnemy){
        name = otherEnemy.name;
        health = otherEnemy.health;
        damage = otherEnemy.damage;
        speed = otherEnemy.speed;
        posiX = otherEnemy.posiX;
        posiY = otherEnemy.posiY;
        score = otherEnemy.score;
        alive = otherEnemy.alive;
    }
    return *this;
};

std::ostream& operator<<(std::ostream& out, const Enemy& enemy){
    out<< "Name: " << enemy.name <<"\n";
    out<< "Hp: " << enemy.health <<"\n";
    out<< "Damage: " << enemy.damage <<"\n";
    out<< "Position X: " << enemy.posiX << " | " << "Position Y" << enemy.posiY <<"\n";
    out<< "Alive: " << (enemy.alive ? "Yes" : "No") <<"\n";
    return out;
}

void Enemy::loadConfig(const string& filename){
    configManager = ConfigManager("data/" + filename + ".txt");
    if (configManager.loadConfig()){
        name = configManager.getValue("name");
        health = stoi(configManager.getValue("health"));
        damage = stoi(configManager.getValue("damage"));
        speed = stod(configManager.getValue("speed"));
        posiX = stoi(configManager.getValue("posiX"));
        posiY = stoi(configManager.getValue("posiY"));
        score = stoi(configManager.getValue("score"));
        alive = (configManager.getValue("alive") == "true") ? true : false;
    } else{
        throw std::runtime_error("Não foi possível carregar o arquivo de configuração.\n");
    }
}
void Enemy::saveConfig(){
    configManager = ConfigManager("data/" + get_name() + ".txt");
    configManager.setValue("name", name);
    configManager.setValue("health", to_string(health));
    configManager.setValue("damage", to_string(damage));
    configManager.setValue("speed", to_string(speed));
    configManager.setValue("posiX", to_string(posiX));
    configManager.setValue("posiY", to_string(posiY));
    configManager.setValue("score", to_string(score));
    configManager.setValue("alive", alive ? "true" : "false");
    if (!configManager.saveConfig()){
        throw std::runtime_error("Não foi possível salvar o arquivo de configuração.\n");
    }
}


// set e get

void Enemy::set_name(const std::string newName){
    this->name = newName;
}

std::string Enemy::get_name() const{
    return name;
}

void Enemy::set_positionX(double newPosiX){
    this->posiX = newPosiX;
}
void Enemy::set_positionY(double newPosiY){
    this->posiY = newPosiY;
}
double Enemy::get_positionX() const{
    return posiX;
}
double Enemy::get_positionY() const{
    return posiY;
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

void Enemy::set_damage(int newDamage){
    this->damage = newDamage;
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

int Enemy::get_score() const{
    return score;
};

//Struct
SpecialAbilities::SpecialAbilities(): boostDamage(100), boostHealth(100) {}

// Boss
Boss::Boss(): Enemy("Boss", 10000, 200, 7.0, 100, 100, 1000, true), skill(){}
Boss::Boss(const string name, int health, int damage, double speed, int posiX, int posiY, int score, bool alive,
    const SpecialAbilities& skill): Enemy(name, health, damage, speed, posiX, posiY, score, alive), skill(skill) {}
Boss::Boss(const Boss& copyBoss): Enemy(copyBoss) {}


void Boss::activateSkillsDamage(){
    std::chrono::steady_clock::time_point lastSkill;
    int originDamage = get_damage();
    cout<<"Init Damage: "<<get_damage()<<"\n";
    auto now = std::chrono::steady_clock::now();
    if (this->isAlive()){
        auto timeLastSkill = std::chrono::duration_cast<std::chrono::seconds>(now - lastSkill).count();
        if (!skillActive && timeLastSkill >= SKILL_INTERVAL){
            // Habilidade é ativa e o tempos da ultima skill lançada é atualizada
            skillActive = true;
            lastSkill = now;
            set_damage(skill.boostDamage + get_damage());
            for (int i=0; i < 3; i++){
                cout<<"Turno " << i + 1 << ": Habilidade especial ainda ativa." <<"\n";
                cout<<"Damage: "<<get_damage()<<"\n";
            }
            set_damage(originDamage);
            cout<<"Rest Damage: "<<get_damage()<<"\n";
        } else if (skillActive && timeLastSkill<= SKILL_INTERVAL){
            // Desativa a habilidade
            skillActive = false;
        }
    }
}
void Boss::activateSkillsHealth(){
    if (this->isAlive()){
        if (rand() % 100 < 20){
            int currentHealth = get_health();
            int healAmount = currentHealth * 0.05;
            set_health(currentHealth + healAmount);

        }    
    }
}
void Boss::attack(Fighter& target) const{
    if(target.isAlive()) {
        target.set_health(target.get_health() - get_damage());
        if (target.get_health() == 0) {
            target.defeat();  // Lutador morto
            cout << "Fighter destruido!!!" << "\n";
        } else {
            cout << "Fighter Sobreviveu!!!" << "\n";
        }
    }
}

//sobrecarga
Boss& Boss::operator=(const Boss& otherBoss){
    if(this != &otherBoss){
        Enemy::operator=(otherBoss);
        skill = otherBoss.skill;
        skillActive = otherBoss.skillActive;
    }
    return *this;
}


// Mini-Boss

MiniBoss::MiniBoss(): Boss("Mini Boss",1000, 10, 5.0, 100, 100, 500, true, SpecialAbilities()) {}
MiniBoss::MiniBoss(const string name, int health, int damage, double speed, int posiX, int posiY, int score, bool alive)
        : Boss(name, health, damage, speed, posiX, posiY, score, alive, SpecialAbilities()) {}
MiniBoss::MiniBoss(const MiniBoss& copyMiniBoss): Boss(copyMiniBoss) {}


void MiniBoss::attack(Fighter& target) const{
    // vincular dano ao fighter apenas se a bala tiver atingido
    if(target.isAlive()) {
        target.set_health(target.get_health() - get_damage());
        if (target.get_health() == 0) {
            target.defeat();  // Lutador morto
            cout << "Fighter destruido!!!" << "\n";
        } else {
            cout << "Fighter Sobreviveu!!!" << "\n";
        }
    }
}

//sobrecarga
MiniBoss& MiniBoss::operator=(const MiniBoss& otherMiniBoss){
    if(this != &otherMiniBoss){
        Boss::operator=(otherMiniBoss);
    }
    return *this;
}
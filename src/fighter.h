#ifndef FIGHTER_H
#define FIGHTER_H

#include <iostream>
using std::cout;
#include <string>
using std::string;
using std::to_string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include "data.h"
#include "configManager.h"






//Forward declaration
class Bullet;
class EnemyWave;
class Enemy;
struct PowerUp {
    std::string name;
    int effect;
};

class Fighter{

    public:
    Fighter();
    Fighter(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive);
    Fighter(const Fighter& copyFighter);
    ~Fighter();


    void move();
    void defeat();
    void specialAbility();
    void attack(EnemyWave& target);
    void calculatePlayerScore(const Enemy& enemy);
    void addPowerUp(const std::string& name, int effect);
    virtual void shootBullet(double bulletX, double bulletY, bool isPlayerBullet);
    // renderização da nave

    void saveConfig();
    void loadConfig(const string& filename);

    // SOBRECARGA
    friend std::ostream& operator<<(std::ostream& out, const Fighter& fighter);
    
    // setter and getter
    
    Data getUserData() const;
    void printUserData() const;

    void set_name(const std::string newName);
    std::string get_name() const;

    void set_positionX(double newPosiX);
    void set_positionY(double newPosiY);

    double get_positionX() const;
    double get_positionY() const;

    void set_health(int newHealth);
    int get_health() const;

    void set_speed(double newSpeed);
    double get_speed() const;
    
    void set_atk(int newAtk);
    int get_atk() const;

    void setIsAlive(bool value);
    bool isAlive() const;

    int get_score(std::string name) const;
    std::map<std::string, int> getPlayerScore() const;


    protected:
    vector<Bullet*> fighterBullet;

    private:
    ConfigManager configManager;
    std::vector<PowerUp> powerUps;
    map<std::string, int> playerScore;
    Data data;
    int score; 
    std::string name;
    int health;
    double speed;
    int damage;
    bool alive;
    double posiX;
    double posiY;

};

class Interceptor : public Fighter{
    public:

    Interceptor();
    Interceptor(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive);
    Interceptor(const Interceptor& copyInterceptor);

    void shootBullet(double bulletX, double bulletY, bool isPlayerBullet) override;

};

class Destroyer : public Interceptor{

    public:
    
    Destroyer();
    Destroyer(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive);
    Destroyer(const Destroyer& copyDestroyer);	

    void shootBullet(double bulletX, double bulletY, bool isPlayerBullet) override;
};


#endif
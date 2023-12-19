#ifndef FIGHTER_H
#define FIGHTER_H

#include <iostream>
using std::cout;
using std::cin;
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

class SpaceShip {
    public:
    SpaceShip();
    SpaceShip(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive);
    SpaceShip(const SpaceShip& copySpaceShip);
    virtual ~SpaceShip();

    virtual void move() = 0;
    virtual void attack(EnemyWave& target) = 0;
    virtual void saveConfig() = 0;
    virtual void loadConfig(const string& filename) = 0;

    // setters and getters
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


    protected:
    enum BulletType {BULLET, LASER, MISSILE};
    const static double MAX_SPEED;
    static BulletType currentBullet;


    private:
    std::string name;
    int health;
    double speed;
    int damage;
    bool alive;
    double posiX;
    double posiY;
};

class SpaceShipII: public SpaceShip {
    public:
    SpaceShipII();
    SpaceShipII(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive);
    SpaceShipII(const SpaceShipII& copySpaceShipII);
    virtual ~SpaceShipII();
    virtual void evade() = 0;
    virtual void shield() = 0;
};



class Fighter: public SpaceShipII {

    public:
    Fighter();
    Fighter(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive);
    Fighter(const Fighter& copyFighter);
    ~Fighter();

    void move() override;
    void defeat();
    void specialAbility();
    void attack(EnemyWave& target) override;
    void calculatePlayerScore(const Enemy& enemy);
    void addPowerUp(const std::string& name, int effect);
    virtual void shootBullet(double bulletX, double bulletY, bool isPlayerBullet);
    void update();
    void saveConfig() override;
    void loadConfig(const string& filename) override;

    // METODOS DE NÃO UTILITARIOS
    void evade() override;
    void shield() override;

    // SOBRECARGA
    friend std::ostream& operator<<(std::ostream& out, const Fighter& fighter);
    
    // setter and getter
    Data getUserData() const;
    void printUserData() const;
    int get_score(std::string name) const;
    std::map<std::string, int> getPlayerScore() const;
    vector<Bullet*> getBullet() const;


    protected:
    vector<Bullet*> fighterBullet;

    private:
    ConfigManager configManager;
    std::vector<PowerUp> powerUps;
    map<std::string, int> playerScore;
    Data data;
    int score; 
};

class Interceptor : public Fighter{

    public:
    Interceptor();
    Interceptor(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive);
    Interceptor(const Interceptor& copyInterceptor);
    //~Interceptor();

    void shootBullet(double bulletX, double bulletY, bool isPlayerBullet) override;
    void evade() override;
    void shield() override;
    void laser();

    private:
    static int laserCount;

};

class Destroyer : public Interceptor{

    public:
    
    Destroyer();
    Destroyer(const std::string name, int health, double speed, int damage, double posiX, double posiY, bool alive);
    Destroyer(const Destroyer& copyDestroyer);
    //~Destroyer();		

    void shootBullet(double bulletX, double bulletY, bool isPlayerBullet) override;
    void evade() override;
    void shield() override;
    void missile();

    private:
    static int missileCount;
};


#endif
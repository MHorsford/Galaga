#ifndef ENEMY_H
#define ENEMY_H
#include "fighter.h"
#include "bullet.h"
#include <iostream>
using std::cout;
#include <string>
using std::string;
#include<chrono>

#include "configManager.h"



class Enemy{

    public:
    Enemy();
    Enemy(const string name, int health, int damage, double speed, double posiX, double posiY, int score, bool alive);
    Enemy(const Enemy& copyEnemy);
    ~Enemy();

    virtual void attack(Fighter& target) const;
    void limitNameLength(const int MAXLENGTH);
    void move();
    void defeat();
    void saveConfig();
    void loadConfig(const string& filename);

    //Sobrecargas
    bool operator==(const Enemy& otherEnemy) const;
    bool operator!() const;
    bool operator!=(const Enemy& otherEnemy) const;
    Enemy& operator=(const Enemy& otherEnemy);
    friend std::ostream& operator<<(std::ostream& out, const Enemy& enemy);
    void shootBullet(double bulletX, double bulletY, bool isPlayerBullet);

    // getters e setters
    void set_name(const std::string newName);
    std::string get_name() const;

    void set_positionX(double newPosiX);
    void set_positionY(double newPosiY);
    double get_positionX() const;
    double get_positionY() const;

    void set_health(int newHealth);
    int get_health() const;

    void set_damage(int newDamage);
    int get_damage() const;

    void set_speed(double newSpeed);
    double get_speed() const;

    void setIsAlive(bool value);
    bool isAlive() const;

    int get_score() const;



    private:
    ConfigManager configManager;
    string name;
    vector<Bullet*> enemyBullet;
    int health;
    int damage;
    double speed;
    bool alive;
    double posiX;
    int posiY;
    int score = 100;


};

struct SpecialAbilities{
    int boostDamage;
    int boostHealth;
    
    SpecialAbilities();
};


class Boss : public Enemy{
    
    public:
    Boss();
    Boss(const string name, int health, int damage, double speed, int posiX, int posiY, int score, bool alive, const SpecialAbilities& skill);
    Boss(const Boss& copyBoss);

    void activateSkillsDamage();
    void activateSkillsHealth();
    void attack(Fighter& target) const override;


    // sobrecarga
    Boss& operator=(const Boss& otherBoss);

    private:
    SpecialAbilities skill;
    const int SKILL_INTERVAL = 30;
    const int SKILL_DURATION = 10;
    bool skillActive = false;
     

};

class MiniBoss : public Boss{

    public:

    MiniBoss();
    MiniBoss(const string name, int health, int damage, double speed, int posiX, int posiY, int score, bool alive);
    MiniBoss(const MiniBoss& copyMiniBoss);

    void attack(Fighter& target) const override;
    // sobrecarga
    MiniBoss& operator=(const MiniBoss& otherMiniBoss);
};

#endif
#pragma once
#include "fighter.h"
#include <iostream>
#include <string>

using std::cout;
using std::string;

class Enemy{

    private:
    std::string name;
    int health;
    const int damage;
    double speed;

    bool alive;

    public:
// item 1
    Enemy(const std::string name, int health, const int damage, double speed, bool alive);
    Enemy(const Enemy& copyEnemy);

    void attack(Fighter& target) const;
    void limitNameLength(const int MAXLENGTH);
    void move();
    void defeat();

    void set_name(const std::string newName);
    std::string get_name() const;

    void set_health(int newHealth);
    int get_health() const;

    void set_damage(int newDamage);
    int get_damage() const;

    void set_speed(double newSpeed);
    double get_speed() const;

    void setIsAlive(bool value);
    bool isAlive() const;

    void getInfo() const;

};
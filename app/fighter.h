#pragma once
#include <iostream>
#include <string>


using std::cout;
using std::string;
using std::endl;


class Fighter{

    private:
    std::string name;
    int health;
    double speed;
    int atk;
    bool alive;

    public:
    Fighter();
    Fighter(const std::string name, int health, double speed, int atk, bool alive);
    Fighter(const Fighter& copyFighter);

    void move();
    void specialAbility();
    void defeat();

    
    //set and get
    void set_name(const std::string newName);
    std::string get_name() const;

    void set_health(int newHealth);
    int get_health() const;

    void set_speed(double newSpeed);
    double get_speed() const;
    
    void set_atk(int newAtk);
    int get_atk() const;

    void setIsAlive(bool value);
    bool isAlive() const;

    void getInfo() const;
};


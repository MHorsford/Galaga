#pragma once

#include "enemy.h"
#include <vector>

using std::vector;

class EnemyWave {
public:

    EnemyWave();
    EnemyWave(const EnemyWave& other); 
    ~EnemyWave();

 
    void addEnemy(const Enemy& enemy);
    void clearWave();
    void cadRegInHist(int numEnemy);
    int calculateWaveScore() const;
    void getInfo() const;
    void displayMemoryAllocationInfo() const;

private:
    vector<Enemy> enemies;
    int* histPtr; 
    int histSize; 
    int nextEntrieInHist;
    int* score; 
    void alocarHist(int numEnemy);
};


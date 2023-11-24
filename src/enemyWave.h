#ifndef ENEMYWAVE_H
#define ENEMYWAVE_H
#include "enemy.h"
#include <algorithm>
#include <vector>

using std::vector;
class Fighter;
class EnemyWave {
public:

    EnemyWave();
    EnemyWave(const EnemyWave& other); 
    ~EnemyWave();

 
    void addEnemy(const Enemy& enemy);
    void clearWave();
    const std::vector<Enemy>& getWaveEnemy() const;
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
    friend class Fighter;
};

#endif
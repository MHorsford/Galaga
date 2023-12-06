#include "enemyWave.h"
#include <cmath> 


EnemyWave::EnemyWave() : histSize(0), nextEntrieInHist(0), histPtr(nullptr), score(nullptr){}

EnemyWave::EnemyWave(const EnemyWave& other) : enemies(other.enemies), histSize(other.histSize), 
nextEntrieInHist(other.nextEntrieInHist), score(nullptr) {
    histPtr = new int[histSize];
    for (int i = 0; i < nextEntrieInHist; i++) {
        histPtr[i] = other.histPtr[i];
    }
}
// implementar o contrutor copiar

EnemyWave::~EnemyWave() {
    delete[] histPtr;
}

void EnemyWave::addEnemy(const Enemy& enemy) {
    enemies.push_back(enemy);
}

void EnemyWave::clearWave() {
    enemies.clear();
}

const std::vector<Enemy>& EnemyWave::getWaveEnemy() const{
    return enemies;
}

void EnemyWave::alocarHist(int numEnemy) {
    int* histTemp = new int[histSize];
    for (int i = 0; i < nextEntrieInHist; i++) {
        histTemp[i] = histPtr[i];
    }

    delete[] histPtr;
    histSize += static_cast<int>(ceil(histSize * 0.5));
    histPtr = new int[histSize];
    for (int i = 0; i < nextEntrieInHist; i++) {
        histPtr[i] = histTemp[i];
    }
    histPtr[nextEntrieInHist++] = numEnemy;

    delete[] histTemp;
}

void EnemyWave::cadRegInHist(int numEnemy) {
    if (nextEntrieInHist < histSize) {
        histPtr[nextEntrieInHist++] = numEnemy;
        return;
    }

    if (histSize == 0) {
        histSize = 1;
        histPtr = new int[histSize];
        histPtr[nextEntrieInHist++] = numEnemy;
        return;
    }

    alocarHist(numEnemy);
}

int EnemyWave::calculateWaveScore() const {
    auto totalScore = 0;
    
    std::for_each(enemies.begin(), enemies.end(), [&totalScore]( const Enemy& enemy){
        if (enemy.isAlive()){
            totalScore += enemy.get_damage();
            }
    });


    return totalScore;
}

void EnemyWave::displayMemoryAllocationInfo() const {
    cout << "\nAlocacao de memoria na classe EnemyWave:" << "\n";
    cout << "Tamanho do historico alocado: " << histSize << "\n";
    cout << "Proxima entrada no historico: " << nextEntrieInHist << "\n";
}




void EnemyWave::getInfo() const {

    cout << "Pontuacao da Wave: " << calculateWaveScore() << "\n";
    for (const Enemy& enemy : enemies) {

        cout << "Nome do Inimigo: " << enemy.get_name() << "\n";
        cout << "Saude: " << enemy.get_health() << "\n";
        cout << "Velocidade: " << enemy.get_speed() << "\n";
        cout << "Ataque: " << enemy.get_damage() << "\n";
        cout << "Vivo: " << (enemy.isAlive() ? "Yes" : "No") << "\n";
        cout<<"X: "<<enemy.get_positionX()<<" | "<<"Y: "<<enemy.get_positionY()<<"\n";
        cout << "\n";
    }
}



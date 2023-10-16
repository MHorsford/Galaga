#include "fighter.h"
#include "enemy.h"
#include "enemyWave.h"


int main() {

    // 1. Alocação de memória para objetos das classes Enemy e EnemyWave usando ponteiros
    Enemy* enemy1 = new Enemy("Enemy 1", 100, 10, 1.0, true);
    Enemy* enemy2 = new Enemy("Enemy 2", 80, 15, 0.8, true);


    // Exibir informações sobre os inimigos
    cout << "Informacoes sobre os inimigos:" << "\n";
    enemy1->getInfo();
    enemy2->getInfo();

    // 1. Alocação de memória para um objeto da classe EnemyWave usando ponteiro
    EnemyWave* wave = new EnemyWave();
    cout<<"\nInformacao sobre a wave default:\n";
    wave->getInfo();


    wave->cadRegInHist(0);


    // 1. Adicionar os inimigos à onda
    wave->addEnemy(*enemy1);
    wave->addEnemy(*enemy2);

    // Copia
    EnemyWave* wave2 = new EnemyWave(*wave);

    // Exibir informações sobre a wave de inimigos
    cout << "\nInformacoes sobre a Wave de Inimigos apos adicionar inimigos:" << "\n";
    wave->getInfo();
    cout<<"\nInformacao sobre a copia: \n";
    wave2->getInfo();

    wave->displayMemoryAllocationInfo();

    // 3. Liberar a memória alocada para os inimigos e a onda
    cout<<"\nLiberando memoria alocada\n";
    delete enemy1;
    delete enemy2;
    wave->clearWave();
    wave2->clearWave();
    wave2->getInfo();

    // 4. Realocar e repetir o processo, se necessário
    cout<<"\nCriando novos inimigos: \n";
    enemy1 = new Enemy("Enemy 3", 120, 12, 1.2, true);
    enemy2 = new Enemy("Enemy 4", 90, 18, 0.9, true);
    wave = new EnemyWave();

    // 4. Adicionar os novos inimigos à onda
    wave->addEnemy(*enemy1);
    wave->addEnemy(*enemy2);

    // Exibir informações sobre os novos inimigos e a nova wave
    cout << "\nInformacoes sobre os novos inimigos:" << "\n";
    enemy1->getInfo();
    enemy2->getInfo();

    // 5. Liberar a memória novamente
    cout<<"\nLiberando memoria novamente:\n";
    delete enemy1;
    delete enemy2;
    wave->clearWave();
    cout<<"\nWave de inimigos apos liberacao de memoria:\n";
    wave->getInfo();


    getchar();
    return 0;
    
}

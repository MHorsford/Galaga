#include "fighter.h"
#include "enemy.h"
#include "enemyWave.h"
#include "collision.h"
#include "configManager.h"



int main() {

    //Collision collision;
    Fighter* fighter = new Fighter();
    Enemy* galaga  = new Enemy();
    Enemy* butterfly = new Enemy();
    Enemy* bumblebee = new Enemy();
    //Boss* boss = new Boss();
    //Enemy* copyEnemy = new Enemy(*enemyDefault);
    //EnemyWave* wave1 = new EnemyWave();

    //cout<<*fighter<<"\n";
    //cout<<"\n\nTeste Save(Fighter).\n\n";
    //fighter->saveConfig();
    cout<<"\n\nTeste Load(Fighter).\n\n";
    fighter->loadConfig("Player_1");

    cout<<"\n\nTeste Load(Enemys).\n\n";
    galaga->loadConfig("Galaga");
    bumblebee->loadConfig("Bumblebee");
    butterfly->loadConfig("Butterfly");


    cout<<*fighter<<"\n";
    cout<<*galaga<<"\n";
    cout<<*butterfly<<"\n";
    cout<<*bumblebee<<"\n";


    delete fighter;
    //delete wave1;
    //delete copyEnemy;
    //delete butterfly;
    //delete boss;

    
    getchar();
    return 0;
    
}

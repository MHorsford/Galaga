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
    Boss* boss = new Boss();
    Boss* boss2 = new Boss();
    MiniBoss* miniBoss1 = new MiniBoss("Mini Boss 1",5000, 100, 7.0, 100, 100, 500, true);
    MiniBoss* miniBoss2 = new MiniBoss();
    Enemy* copyEnemy = new Enemy(*galaga);
    EnemyWave* wave1 = new EnemyWave();

    //cout<<*fighter<<"\n";
    cout<<"\n\nTeste Save(Boss).\n\n";
    boss->saveConfig();

    cout<<"\n\nTeste Load(Fighter).\n\n";
    fighter->loadConfig("Player_1");

    cout<<"\n\nTeste Load(Enemys).\n\n";
    galaga->loadConfig("Galaga");
    bumblebee->loadConfig("Bumblebee");
    butterfly->loadConfig("Butterfly");

    cout<<"\n\nTeste operador <<\n\n";
    cout<<*fighter<<"\n";
    cout<<*galaga<<"\n";
    cout<<*butterfly<<"\n";
    cout<<*bumblebee<<"\n";
    cout<<*boss<<"\n";

    cout<<"\n\nAdicionando inimigos na wave.\n\n";
    wave1->addEnemy(*galaga);
    wave1->addEnemy(*butterfly);
    wave1->addEnemy(*bumblebee);
    wave1->addEnemy(*boss);

    wave1->getInfo();

    cout<<"\n\nTeste ataque\n\n";
    fighter->attack(*wave1);
    wave1->getInfo();

    cout<<"\n\nTeste operator =!\n\n";
    cout<<"Bumblebee != Butterfly: "<<butterfly->operator!=(*bumblebee);
    cout<<"\n";
    cout<<"boss != boss2: "<<boss->operator!=(*boss);
    cout<<"\n";
    cout<<"\n\nTeste operator ==\n\n";
    cout<<"boss == boss2: "<<boss->operator==(*boss);
    cout<<"\n\nTeste operator !\n\n";
    cout<<"boss !isAlive: "<<boss->operator!();
    cout<<"\n\nTeste operator =\n\n";
    miniBoss2 = miniBoss1;
    cout<<"Miniboss2 = MiniBoss1: \n"<<*miniBoss1<<"\n"<<*miniBoss2;

    //boss->saveConfig();



    delete fighter;
    delete wave1;
    delete bumblebee;
    delete galaga;
    delete butterfly;
    delete boss;
    delete boss2;
    delete miniBoss1;
    delete miniBoss2;

    getchar();
    return 0;
    
}

#include "fighter.h"
#include "enemy.h"

int main() {
    // Criando objetos com valores personalizados
    Fighter standardFighter;
    Fighter fighter1("Fighter 1", 1000, 40.0, 80, true);
    const Enemy butterfly("Butterfly", 200, 100, 30.0, true);
    Enemy bumblebee("Bumblebee111", 300, 1000, 35.0, true);

    // criando copias
    Fighter copyFighter1(fighter1);
    Enemy copyBumblebee(bumblebee);
    cout <<"Criando copia de Fighter1\n";
    copyFighter1.getInfo();
    cout << "\nCriando copia de Bumblebee\n";
    copyBumblebee.getInfo();

    // verificando tamanho do nome
    cout<< "\n\nVerificando comprimento de nome." << "\n";
    cout<<"\nNome: "<<bumblebee.get_name();
    bumblebee.limitNameLength(9);
 
    // Exibindo informações dos Fighter
    cout << "\n\nInformacoes do Fighter 1:" << "\n";
    fighter1.getInfo();
    cout << "\nInformacoes do Bumblebee(Enemy):" <<"\n";
    bumblebee.getInfo();

    // exibindo ataque feito a Fighter 1 e Standard(metodo const)
    cout<<"\n\nInteracao de ataque: \n";
    cout<< "\nFighter 1 atacado!!!" << "\n";
    bumblebee.attack(fighter1);
    cout<< "\nStandardFighter atacado!!!" << "\n";
    butterfly.attack(standardFighter);

    // exibindo informações atualizadas
    cout << "\n\nInformacoes atualizadas do Fighter 1:" << "\n";
    fighter1.getInfo();

    cout << "\nInformacoes atualizadas do StandardFighter:" << "\n";
    standardFighter.getInfo();

    // exibindo valores booleando isoladamente
    cout<<"\n\nExibindo os valores boleanos isoladamente.\n";
    cout<<"\nAlive: "<<fighter1.isAlive()<<"\n";
    cout<<"\nAlive: "<<bumblebee.isAlive()<<"\n";

    system("pause");
    return 0;
}

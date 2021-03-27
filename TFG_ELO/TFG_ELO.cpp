#include <iostream>
#include "Precompiled.h"
#include "Player.h"

int main()
{
    cout << "Introdueix número de jugadors" << endl;
    int numPlayers;
    cin >> numPlayers;
    shared_ptr<Player> p = make_shared<Player>();
    p->createPlayers(numPlayers);
    for (int i = 0; i < numPlayers; i++) {
        Player::player ps = p->getPlayer(i);
        cout << "EL Player num " << ps.id << " té " << ps.elo << " punts d'elo" << endl;
    }
}



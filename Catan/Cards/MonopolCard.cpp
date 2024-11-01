// 326627635 | adi.peisach@gmail.com
#include "MonopolCard.hpp"


void MonopolCard::play(Player& p, Game& g) {
    cout << "Choose resource:" << endl << Constants::RESOURCES_ICONS << endl << "0 1 2 3 4" << endl;
    unsigned int resource;
    while (true) {
        *g.getInput() >> resource;
        if (resource > 4) cout << "Resource has to be between 0 and 4" << endl;
        else break;
    }

    for (unsigned int i = 0; i < g.numPlayers(); i++) {
        if (g.getPlayer(i).getId() == p.getId()) continue;
        unsigned int transfer = g.getPlayer(i).numProducts(resource);
        g.getPlayer(i).pay(resource, transfer);
        p.receiveProduct(resource, transfer);
    }
}

string MonopolCard::toString() const {
    return Constants::MONOPOL_CARD;
}
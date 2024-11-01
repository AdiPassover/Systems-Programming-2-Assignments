// 326627635 | adi.peisach@gmail.com
#include "YearOfPlenty.hpp"

void YearOfPlenty::play(Player& p, Game& g) {
    cout << "Choose two resources: (by index)" << endl << Constants::RESOURCES_ICONS << endl << "0 1 2 3 4" << endl;
    unsigned int resource1, resource2;
    while (true) {
        *g.getInput() >> resource1 >> resource2;
        if (resource1 > 4 || resource2 > 4) cout << "Resource has to be between 0 and 4" << endl;
        else break;
    }
    p.receiveProduct(resource1, 1);
    p.receiveProduct(resource2, 1);
}

string YearOfPlenty::toString() const {
    return Constants::YEAR_OF_PLENTY_CARD;
}
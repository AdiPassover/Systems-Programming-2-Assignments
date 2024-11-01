// 326627635 | adi.peisach@gmail.com
#include "Settlement.hpp"

void Settlement::upgradeToCity(Player& p) {
    if (level != 1) throw std::invalid_argument("Cannot upgrade to city");
    level = 2;
    p.addPoints(1);
}

void Settlement::buildVillage(Player& p) {
    if (level != 0) throw std::invalid_argument("Cannot build village");
    level = 1;
    player = &p;
    p.addPoints(1);
}

string Settlement::toString() const {
    string ans = Constants::VACANT_ICON;
    if (level == 1)
        ans = player->getColor() + Constants::VILLAGE_ICON;
    if (level == 2)
        ans = player->getColor() + Constants::CITY_ICON;
    return ans + Constants::RESET;
}

void Settlement::receiveProducts(unsigned int product) {
    if (level == 0) return;
    player->receiveProduct(product, level);
}

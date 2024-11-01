// 326627635 | adi.peisach@gmail.com
#ifndef CATAN_SETTLEMENT_HPP
#define CATAN_SETTLEMENT_HPP
//#include <string>
//#include <stdexcept>
//#include "../../Constants.hpp"
#include "../../Player.hpp"

using std::string;

class Settlement {
private:
    unsigned int level;
    Player* player = nullptr;

public:
    Settlement() { level = 0; }

    Player* getOwner() const { return player; }

    unsigned int getLevel() const { return level; }
    void receiveProducts(unsigned int product);
    bool isBuilt() const { return level > 0; }

    void buildVillage(Player& p);
    void upgradeToCity(Player& p);
    string toString() const;

};

#endif

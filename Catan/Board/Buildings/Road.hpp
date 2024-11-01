// 326627635 | adi.peisach@gmail.com
#ifndef CATAN_ROAD_HPP
#define CATAN_ROAD_HPP
#include "../../Player.hpp"

using std::string;

enum class Oriention : char {
    Vertical = '|',
    DiagonalLeft = '\\',
    DiagonalRight = '/'
};

class Road {
private:
    bool built = false;
    Oriention orientation;
    Player* player = nullptr;

public:
    explicit Road(Oriention orientation) { this->orientation = orientation; }

    Player* getOwner() const { return player; }

    void buildRoad(Player& p) { player = &p; built = true; }

    bool isBuilt() const { return built; };
    string toString() const;
    string orientationString() const;

};

#endif
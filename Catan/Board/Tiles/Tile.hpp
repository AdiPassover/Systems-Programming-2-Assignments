// 326627635 | adi.peisach@gmail.com
#ifndef CATAN_TILE_HPP
#define CATAN_TILE_HPP
#include <utility>
#include <vector>
#include <memory>
#include <stdexcept>
#include "direction.hpp"
#include "../../Constants.hpp"

class Settlement;
class Road;
class Player;
using std::vector;
using std::unique_ptr;
using std::make_unique;

class Tile {
protected:
    string symbol;
    unsigned int diceNumber;
    unsigned int product;
    vector<Settlement*> settlements;
    vector<Road*> roads;

    unsigned int directionToSettlementIndex(Direction) const;
    unsigned int directionToRoadIndex(Direction) const;

public:

    Tile(vector<Settlement*>& set, vector<Road*>& r)
            : symbol(Constants::DESERT_ICON), diceNumber(0), product(9), settlements(std::move(set)), roads(std::move(r)) {}
    Tile(string s, unsigned int n, unsigned int p, vector<Settlement*>& set, vector<Road*>& r)
        : symbol(std::move(s)), diceNumber(n), product(p), settlements(std::move(set)), roads(std::move(r)) {}


    virtual Settlement* getSettlement(Direction d) const { return settlements[directionToSettlementIndex(d)]; };
    virtual Road* getRoad(Direction d) const { return roads[directionToRoadIndex(d)]; }

    void placeSettlement(Direction, Player&);
    void upgradeSettlement(Direction, Player&);
    void placeRoad(Direction, Player&);
    virtual void produce();

    virtual string toString() { return symbol; }
};

#endif
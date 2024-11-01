// 326627635 | adi.peisach@gmail.com
#ifndef CATAN_MINE_HPP
#define CATAN_MINE_HPP
#include "Tile.hpp"

class Mine : public Tile {
public:
    Mine(unsigned int n, vector<Settlement*>& set, vector<Road*>& r)
    : Tile(Constants::BRICK_ICON,n,Constants::BRICK,set,r) {}

};

#endif //CATAN_MINE_HPP
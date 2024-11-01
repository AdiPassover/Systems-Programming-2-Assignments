// 326627635 | adi.peisach@gmail.com
#ifndef CATAN_MOUNTAINS_HPP
#define CATAN_MOUNTAINS_HPP
#include "Tile.hpp"

class Mountains : public Tile {
public:
    Mountains(unsigned int n, vector<Settlement*>& set, vector<Road*>& r)
    : Tile(Constants::STONE_ICON,n,Constants::STONE,set,r) {}

};

#endif //CATAN_MOUNTAINS_HPP
// 326627635 | adi.peisach@gmail.com
#ifndef CATAN_PASTURE_HPP
#define CATAN_PASTURE_HPP
#include "Tile.hpp"

class Pasture : public Tile {
public:
    Pasture(unsigned int n, vector<Settlement*>& set, vector<Road*>& r) :
    Tile(Constants::WOOL_ICON,n,Constants::WOOL,set,r) {}

};

#endif //CATAN_PASTURE_HPP
// 326627635 | adi.peisach@gmail.com
#ifndef CATAN_FIELD_HPP
#define CATAN_FIELD_HPP
#include "Tile.hpp"

class Field : public Tile {
public:
    Field(unsigned int n, vector<Settlement*>& set, vector<Road*>& r)
    : Tile(Constants::WHEAT_ICON,n,Constants::WHEAT,set,r) {}

};

#endif //CATAN_FIELD_HPP
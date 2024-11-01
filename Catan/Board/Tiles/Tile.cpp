// 326627635 | adi.peisach@gmail.com
#include "Tile.hpp"
#include "../Buildings/Settlement.hpp"
#include "../Buildings/Road.hpp"

void Tile::produce() {
    for (size_t i = 0; i < settlements.size(); i++) {
        settlements[i]->receiveProducts(product);
    }
}

unsigned int Tile::directionToSettlementIndex(Direction d) const {
    if (d == Direction::North) {
        return 0;
    } else if (d == Direction::NorthEast) {
        return 1;
    } else if (d == Direction::SouthEast) {
        return 2;
    } else if (d == Direction::South) {
        return 3;
    } else if (d == Direction::SouthWest) {
        return 4;
    } else if (d == Direction::NorthWest) {
        return 5;
    }
    throw std::invalid_argument("Invalid direction for settlement on tile " + std::to_string((int)d));
}

unsigned int Tile::directionToRoadIndex(Direction d) const {
    if (d == Direction::NorthEast) {
        return 0;
    } else if (d == Direction::East) {
        return 1;
    } else if (d == Direction::SouthEast) {
        return 2;
    } else if (d == Direction::SouthWest) {
        return 3;
    } else if (d == Direction::West) {
        return 4;
    } else if (d == Direction::NorthWest) {
        return 5;
    }
    throw std::invalid_argument("Invalid direction for road on tile");
}

void Tile::placeSettlement(Direction d, Player& p) {
    if (settlements[directionToSettlementIndex(d)]->getLevel() != 0)
        throw std::invalid_argument("Settlement already built");
    settlements[directionToSettlementIndex(d)]->buildVillage(p);
}

void Tile::upgradeSettlement(Direction d, Player& p) {
    if (settlements[directionToSettlementIndex(d)]->getLevel() != 1)
        throw std::invalid_argument("Settlement not built or already a city");
    settlements[directionToSettlementIndex(d)]->upgradeToCity(p);
}

void Tile::placeRoad(Direction d, Player& p) {
    if (roads[directionToRoadIndex(d)]->isBuilt())
        throw std::invalid_argument("Road already built");
    roads[directionToRoadIndex(d)]->buildRoad(p);
}

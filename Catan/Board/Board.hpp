// 326627635 | adi.peisach@gmail.com
#ifndef CATAN_BOARD_HPP
#define CATAN_BOARD_HPP
#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include "Tiles/Tile.hpp"
#include "Tiles/Field.hpp"
#include "Tiles/Forest.hpp"
#include "Tiles/Mine.hpp"
#include "Tiles/Mountains.hpp"
#include "Tiles/Pasture.hpp"
#include "../Player.hpp"
#include "Buildings/Settlement.hpp"
#include "Buildings/Road.hpp"

using std::vector;
using std::unique_ptr;
using std::move;
using std::make_unique;

class Board {
private:
    vector<unique_ptr<Tile>> tiles;
    vector<unique_ptr<Settlement>> settlements;
    vector<unique_ptr<Road>> roads;
    const vector<unsigned int> TILES_NUMBERS = {10,2,9,12,6,4,10,9,11,0,3,8,8,3,4,5,5,6,11};

    bool distanceRule(char tile, Direction direction) const;
    void initRoads();
    void initTiles();
    void drawTop(unsigned int index, vector<vector<string>>& mat, unsigned int topI, unsigned int topJ) const;
    void drawLeft(unsigned int index, vector<vector<string>>& mat, unsigned int topI, unsigned int topJ) const;
    void drawBottom(unsigned int index, vector<vector<string>>& mat, unsigned int topI, unsigned int topJ) const;
    bool isThereRoad(Player&, char, Direction) const;

public:
    explicit Board();

    Tile* getTile(char c) const;

    bool canPlaceSettlement(Player&, char, Direction) const;
    bool canUpgradeSettlement(Player&, char, Direction) const;
    bool canPlaceRoad(Player&, char, Direction) const;
    bool canPlaceFirstSettlement(char, Direction) const;

    void placeSettlement(Player&, char, Direction);
    void upgradeSettlement(Player&, char, Direction);
    void placeRoad(Player&, char, Direction);

    void produce(unsigned int);

    string toString() const;
    void print() const { std::cout << toString() << std::endl; }

};
#endif

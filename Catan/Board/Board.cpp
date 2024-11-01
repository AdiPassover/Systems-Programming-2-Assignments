// 326627635 | adi.peisach@gmail.com
#include "Board.hpp"

const vector<vector<unsigned int>> TILES_SETTELEMENTS = {
                                   {0,4,8,12,7,3}, {1,5,9,13,8,4}, {2,6,10,14,9,5},
                    {7,12,17,22,16,11}, {8,13,18,23,17,12}, {9,14,19,24,18,13}, {10,15,20,25,19,14},
        {16,22,28,33,27,21}, {17,23,29,34,28,22}, {18,24,30,35,29,23}, {19,25,31,36,30,24}, {20,26,32,37,31,25},
                   {28,34,39,43,38,33}, {29,35,40,44,39,34}, {30,36,41,45,40,35}, {31,37,42,46,41,36},
                             {39,44,48,51,47,43}, {40,45,49,52,48,44}, {41,46,50,53,49,45}
};

const vector<vector<unsigned int>> TILES_ROADS = {
                                   {1,7,12,11,6,0}, {3,8,14,13,7,2}, {5,9,16,15,8,4},
                   {11,19,25,24,18,10}, {13,20,27,26,19,12}, {15,21,29,28,20,14}, {17,22,31,30,21,16},
        {24,34,40,39,33,23}, {26,35,42,41,34,25}, {28,36,44,43,35,27}, {30,37,46,45,36,29}, {32,38,48,47,37,31},
                   {41,50,55,54,49,40}, {43,51,57,56,50,42}, {45,52,59,58,51,44}, {47,53,61,60,52,46},
                             {56,63,67,66,62,55}, {58,64,69,68,63,57}, {60,65,71,70,64,59}
};

Board::Board() {
    settlements.resize(54);
    for (unsigned int i = 0; i < 54; i++)
        settlements[i] = std::make_unique<Settlement>();

    initRoads();
    initTiles();
}

void Board::initRoads() {
    roads.resize(72);
    vector<unsigned int> ends = {6,4,8,5,10,6,10,5,8,4,6};
    unsigned int row = 0;
    unsigned int col = 0;
    unsigned int sign = 0;
    for (unsigned int i = 0; i < 72; i++) {
        if (row % 2 == 0 && col % 2 == sign) {
            roads[i] = std::make_unique<Road>(Oriention::DiagonalRight);
            col++;
        } else if (row % 2 == 0 && col % 2 == 1-sign) {
            roads[i] = std::make_unique<Road>(Oriention::DiagonalLeft);
            col++;
        } else {
            roads[i] = std::make_unique<Road>(Oriention::Vertical);
            col++;
        }
        if (ends[row] == col) {
            row++;
            col = 0;
            if (row == 5) sign = 1;
        }
    }
}

void Board::initTiles() {
    tiles.resize(19);

    int numField = 4;
    int numForest = 4;
    int numMountain = 3;
    int numMine = 3;
    int numPasture = 4;
    for (unsigned int i = 0; i < tiles.size(); i++) {
        vector<Settlement*> currSet(6);
        vector<Road*> currRoads(6);
        for (unsigned int j = 0; j < 6; j++) {
            currSet[j] = settlements[TILES_SETTELEMENTS[i][j]].get();
            currRoads[j] = roads[TILES_ROADS[i][j]].get();
        }

        if (i == 9) {
            tiles[i] = std::move(make_unique<Tile>(currSet,currRoads));
            continue;
        }
        int r = rand() % 5;
        if (r == 0 && numField > 0) {
            tiles[i] = std::move(make_unique<Field>(TILES_NUMBERS[i],currSet,currRoads));
            numField--;
        } else if (r == 1 && numForest > 0) {
            tiles[i] = std::move(std::make_unique<Forest>(TILES_NUMBERS[i],currSet,currRoads));
            numForest--;
        } else if (r == 2 && numMountain > 0) {
            tiles[i] = std::move(std::make_unique<Mountains>(TILES_NUMBERS[i],currSet,currRoads));
            numMountain--;
        } else if (r == 3 && numMine > 0) {
            tiles[i] = std::move(std::make_unique<Mine>(TILES_NUMBERS[i],currSet,currRoads));
            numMine--;
        } else if (r == 4 && numPasture > 0) {
            tiles[i] = std::move(std::make_unique<Pasture>(TILES_NUMBERS[i],currSet,currRoads));
            numPasture--;
        } else {
            i--;
        }
    }
}

Tile* Board::getTile(char c) const {
    unsigned int index = (unsigned int)(c-'a');
    return tiles[index].get();
}

void Board::placeSettlement(Player& p, char c, Direction direction) {
    tiles[(unsigned int)(c-'a')]->placeSettlement(direction, p);
}

void Board::upgradeSettlement(Player& p, char c, Direction direction) {
    tiles[(unsigned int)(c-'a')]->upgradeSettlement(direction,p);
}

void Board::placeRoad(Player& p, char c, Direction direction) {
    tiles[(unsigned int)(c-'a')]->placeRoad(direction, p);
}

void Board::drawTop(unsigned int index, vector<vector<string>>& mat, unsigned int topI, unsigned int topJ) const {
    mat[topI][topJ] = tiles[index]->getSettlement(Direction::North)->toString();
    if (tiles[index]->getSettlement(Direction::North)->isBuilt()) { mat[topI][topJ+1] = ""; mat[topI][topJ-1] = ""; }
    mat[topI+2][topJ+2] = tiles[index]->getSettlement(Direction::NorthEast)->toString();
    if (tiles[index]->getSettlement(Direction::NorthEast)->isBuilt()) { mat[topI+2][topJ+3]=""; mat[topI+2][topJ+1]=""; }

    mat[topI+1][topJ-1] = tiles[index]->getRoad(Direction::NorthWest)->toString();
    mat[topI+1][topJ+1] = tiles[index]->getRoad(Direction::NorthEast)->toString();
    mat[topI+3][topJ+2] = tiles[index]->getRoad(Direction::East)->toString();

    mat[topI+2][topJ] = (char)(index+'a');
    mat[topI+3][topJ] = tiles[index]->toString();
    mat[topI+3][topJ-1] = "";
    if (TILES_NUMBERS[index] < 10) {
        mat[topI+4][topJ] = std::to_string(TILES_NUMBERS[index]);
    }
    else {
        mat[topI+4][topJ] = std::to_string(TILES_NUMBERS[index]);
        mat[topI+4][topJ+1] = "";
    }

}

void Board::drawLeft(unsigned int index, vector<vector<string>>& mat, unsigned int topI, unsigned int topJ) const {
   mat[topI][topJ] = tiles[index]->getSettlement(Direction::NorthWest)->toString();
   if (tiles[index]->getSettlement(Direction::NorthWest)->isBuilt()) { mat[topI][topJ+1]=""; mat[topI][topJ-1]=""; }
   mat[topI+1][topJ] = tiles[index]->getRoad(Direction::West)->toString();
}

void Board::drawBottom(unsigned int index, vector<vector<string>>& mat, unsigned int botI, unsigned int botJ) const {
    mat[botI][botJ] = tiles[index]->getSettlement(Direction::South)->toString();
    if (tiles[index]->getSettlement(Direction::South)->isBuilt()) { mat[botI][botJ+1]=""; mat[botI][botJ-1]=""; }
    mat[botI-2][botJ+2] = tiles[index]->getSettlement(Direction::SouthEast)->toString();
    if (tiles[index]->getSettlement(Direction::SouthEast)->isBuilt()) { mat[botI-2][botJ+3]=""; mat[botI-2][botJ+1]=""; }
    mat[botI-2][botJ-2] = tiles[index]->getSettlement(Direction::SouthWest)->toString();
    if (tiles[index]->getSettlement(Direction::SouthWest)->isBuilt()) { mat[botI-2][botJ-1]=""; mat[botI-2][botJ-3]=""; }

    mat[botI-1][botJ-1] = tiles[index]->getRoad(Direction::SouthWest)->toString();
    mat[botI-1][botJ+1] = tiles[index]->getRoad(Direction::SouthEast)->toString();
}

string Board::toString() const {
    vector<vector<string>> rows(23, vector<string>(21, " "));

    vector<vector<unsigned int>> tops = {
            {0,6},{0,10},{0,14},{4,4},{4,8},{4,12},{4,16},{8,2},{8,6},{8,10},{8,14},{8,18},{12,4},{12,8},{12,12},{12,16},{16,6},{16,10},{16,14}
    };
    for (unsigned int i = 0; i < tops.size(); i++) {
        drawTop(i, rows, tops[i][0], tops[i][1]);
    }

    vector<vector<unsigned int>> lefts = {{2,4,0},{6,2,3},{10,0,7},{14,2,12},{18,4,16}};
    for (unsigned int i = 0; i < lefts.size(); i++) {
        drawLeft(lefts[i][2], rows, lefts[i][0], lefts[i][1]);
    }

    vector<vector<unsigned int>> bottoms = {{22,6,16},{22,10,17},{22,14,18}};
    for (unsigned int i = 0; i < bottoms.size(); i++) {
        drawBottom(bottoms[i][2], rows, bottoms[i][0], bottoms[i][1]);
    }

    rows[12][0] = tiles[7]->getSettlement(Direction::SouthWest)->toString();
    if (tiles[7]->getSettlement(Direction::SouthWest)->isBuilt()) { rows[12][1] = ""; }
    rows[13][1] = tiles[7]->getRoad(Direction::SouthWest)->toString();

    rows[16][2] = tiles[12]->getSettlement(Direction::SouthWest)->toString();
    if (tiles[12]->getSettlement(Direction::SouthWest)->isBuilt()) { rows[16][3] = ""; rows[16][1] = ""; }
    rows[17][3] = tiles[12]->getRoad(Direction::SouthWest)->toString();

    rows[16][18] = tiles[15]->getSettlement(Direction::SouthEast)->toString();
    if (tiles[15]->getSettlement(Direction::SouthEast)->isBuilt()) { rows[16][19] = ""; rows[16][17] = ""; }
    rows[17][17] = tiles[15]->getRoad(Direction::SouthEast)->toString();

    rows[12][20] = tiles[11]->getSettlement(Direction::SouthEast)->toString();
    if (tiles[11]->getSettlement(Direction::SouthEast)->isBuilt()) { rows[12][21] = ""; rows[12][19] = ""; }
    rows[13][19] = tiles[11]->getRoad(Direction::SouthEast)->toString();

    string s = "";
    for (unsigned int i = 0; i < rows.size(); i++) {
        for (unsigned int j = 0; j < rows[i].size(); j++) {
            s.append(rows[i][j]).append(" ");
        }
        s.append("\n");
    }
    return s;
}

const vector<vector<char>> DIRECTION_TILES = {
        {},                                                                            // north
        {'x','x','x','a','b','c','x','d','e','f','g','x','i','j','k','l','n','o','p'}, // north east
        {'b','c','x','e','f','g','x','i','j','k','l','x','n','o','p','x','r','s','x'}, // east
        {'e','f','g','i','j','k','l','m','n','o','p','x','q','r','s','x','x','x','x'}, // south east
        {},                                                                            // south
        {'d','e','f','h','i','j','k','x','m','n','o','p','x','q','r','s','x','x','x'}, // south west
        {'x','a','b','x','d','e','f','x','h','i','j','k','x','m','n','o','x','r','s'}, // west
        {'x','x','x','x','a','b','c','x','d','e','f','g','h','i','j','k','m','n','o'}  // north west
};

bool Board::distanceRule(char tile, Direction direction) const {
    unsigned int index = (unsigned int)(tile-'a');
    if (tiles[index]->getSettlement(direction)->isBuilt())
        return false;

    if (tiles[index]->getSettlement(Directions::sumSet(direction,1))->isBuilt() ||
        tiles[index]->getSettlement(Directions::sumSet(direction,-1))->isBuilt())
        return false;
    return true;
}

bool Board::canPlaceSettlement(Player& p, char tile, Direction direction) const {
    if (!canPlaceFirstSettlement(tile, direction))
        return false;

    unsigned int index = (unsigned int)(tile-'a');
    vector<Direction> nearRoads = Directions::nearestRoads(direction);
    char tile2 = DIRECTION_TILES[(unsigned int)(int)(nearRoads[0])][index];
    Direction d2 = Directions::sumSet(Directions::opposite(direction),-1);
    char tile3 = DIRECTION_TILES[(unsigned int)(int)(nearRoads[1])][index];
    Direction d3 = Directions::sumSet(Directions::opposite(direction),1);

    if (tiles[index]->getRoad(nearRoads[0])->getOwner() != &p &&
        tiles[index]->getRoad(nearRoads[1])->getOwner() != &p) {
        if (tile2=='x' && tile3=='x') return false;
        if (tile2!='x') {
            unsigned int index2 = (unsigned int)(tile2-'a');
            vector<Direction> nearRoads2 = Directions::nearestRoads(d2);
            if (tiles[index2]->getRoad(nearRoads2[0])->getOwner() != &p &&
                tiles[index2]->getRoad(nearRoads2[1])->getOwner() != &p)
                return false;
        } else {
            unsigned int index3 = (unsigned int)(tile3-'a');
            vector<Direction> nearRoads3 = Directions::nearestRoads(d3);
            if (tiles[index3]->getRoad(nearRoads3[0])->getOwner() != &p &&
                tiles[index3]->getRoad(nearRoads3[1])->getOwner() != &p)
                return false;
        }
    }

    return true;
}

bool Board::canUpgradeSettlement(Player& p, char tile, Direction d) const {
    return tiles[(unsigned int)(tile-'a')]->getSettlement(d)->getLevel() == 1 &&
        tiles[(unsigned int)(tile-'a')]->getSettlement(d)->getOwner() == &p;
}

bool Board::canPlaceRoad(Player& p, char tile, Direction d) const {
    unsigned int index = (unsigned int)(tile-'a');
    if (tiles[index]->getRoad(d)->isBuilt())
        return false;

    vector<Direction> nearest = Directions::nearestSettlements(d);
    if (tiles[index]->getSettlement(nearest[0])->getOwner() == &p ||
        tiles[index]->getSettlement(nearest[1])->getOwner() == &p)
        return true;

    if (isThereRoad(p,tile,nearest[0]) || isThereRoad(p,tile,nearest[1]))
        return true;

    char tile2 = DIRECTION_TILES[(unsigned int)(int)d][index];
    Direction d2 = Directions::opposite(d);
    vector<Direction> nearest2 = Directions::nearestSettlements(d2);
    if (tile2 != 'x' && (isThereRoad(p,tile2,nearest2[0]) || isThereRoad(p,tile2,nearest2[1])))
        return true;

    char tile3 = DIRECTION_TILES[(unsigned int)(int)Directions::sumRoad(d,1)][index];
    Direction d3 = Directions::opposite(Directions::sumRoad(d,1));
    vector<Direction> nearest3 = Directions::nearestSettlements(d3);
    if (tile3 != 'x' && isThereRoad(p,tile3,nearest3[1]))
        return true;

    char tile4 = DIRECTION_TILES[(unsigned int)(int)Directions::sumRoad(d,-1)][index];
    Direction d4 = Directions::opposite(Directions::sumRoad(d,-1));
    vector<Direction> nearest4 = Directions::nearestSettlements(d4);
    return tile4 != 'x' && isThereRoad(p,tile4,nearest4[0]);
}

bool Board::isThereRoad(Player& p, char tile, Direction direction) const {
    unsigned int index = (unsigned int)(tile-'a');
    vector<Direction> nearest = Directions::nearestRoads(direction);
    return tiles[index]->getRoad(nearest[0])->getOwner() == &p || tiles[index]->getRoad(nearest[1])->getOwner() == &p;
}

bool Board::canPlaceFirstSettlement(char tile, Direction direction) const {
    unsigned int index = (unsigned int)(tile-'a');
    if (tiles[index]->getSettlement(direction)->isBuilt())
        return false;
    if (!distanceRule(tile,direction))
        return false;

    vector<Direction> nearRoads = Directions::nearestRoads(direction);

    char tile2 = DIRECTION_TILES[(unsigned int)(int)(nearRoads[0])][index];
    Direction d2 = Directions::sumSet(Directions::opposite(direction),-1);
    if (tile2 != 'x' && !distanceRule(tile2,d2))
        return false;

    char tile3 = DIRECTION_TILES[(unsigned int)(int)(nearRoads[1])][index];
    Direction d3 = Directions::sumSet(Directions::opposite(direction),1);
    if (tile3 != 'x' && !distanceRule(tile3,d3))
        return false;
    return true;
}

void Board::produce(unsigned int diceNum) {
    if (diceNum < 1 || diceNum > 12)
        throw std::invalid_argument("Invalid dice number");
    for (unsigned int i = 0; i < TILES_NUMBERS.size(); i++) {
        if (TILES_NUMBERS[i] == diceNum)
            tiles[i]->produce();
    }
}

// 326627635 | adi.peisach@gmail.com

//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Board/Board.hpp"

TEST_CASE("Placing and upgrading settlements") {

    Board board;
    Player p1("1",Constants::RED);
    Player p2("2",Constants::BLUE);
    Player p3("3",Constants::GREEN);
    Player p4("4",Constants::YELLOW);

    board.placeSettlement(p1, 'a', Direction::South);
    CHECK(board.getTile('a')->getSettlement(Direction::South)->toString() == p1.getColor()+"🏘"+Constants::RESET);
    board.upgradeSettlement(p1,'a', Direction::South);
    CHECK(board.getTile('a')->getSettlement(Direction::South)->toString() == p1.getColor()+"🏙"+Constants::RESET);

    CHECK_THROWS(board.placeSettlement(p2, 'd', Direction::NorthEast));
    CHECK_THROWS(board.placeSettlement(p1, 'e', Direction::NorthWest));

    board.placeSettlement(p2, 'd', Direction::SouthWest);
    CHECK(board.getTile('d')->getSettlement(Direction::SouthWest)->toString() == p2.getColor()+"🏘"+Constants::RESET);
    board.upgradeSettlement(p2,'d', Direction::SouthWest);
    CHECK(board.getTile('d')->getSettlement(Direction::SouthWest)->toString() == p2.getColor()+"🏙"+Constants::RESET);
    CHECK_THROWS(board.upgradeSettlement(p1,'d', Direction::SouthWest));
    CHECK_THROWS(board.upgradeSettlement(p2,'d', Direction::South));

}

TEST_CASE("Placing roads") {

    Board board;
    Player p1("1",Constants::RED);
    Player p2("2",Constants::BLUE);
    Player p3("3",Constants::GREEN);
    Player p4("4",Constants::YELLOW);

    board.placeRoad(p3, 'a', Direction::NorthEast);
    CHECK(board.getTile('a')->getRoad(Direction::NorthEast)->toString() == p3.getColor()+"\\"+Constants::RESET);
    board.placeRoad(p4, 'a', Direction::NorthWest);
    CHECK(board.getTile('a')->getRoad(Direction::NorthWest)->toString() == p4.getColor()+"/"+Constants::RESET);
    board.placeRoad(p3, 'a', Direction::SouthWest);
    CHECK(board.getTile('a')->getRoad(Direction::SouthWest)->toString() == p3.getColor()+"\\"+Constants::RESET);
    board.placeRoad(p4, 'a', Direction::SouthEast);
    CHECK(board.getTile('a')->getRoad(Direction::SouthEast)->toString() == p4.getColor()+"/"+Constants::RESET);
    board.placeRoad(p3, 'r', Direction::East);
    CHECK(board.getTile('r')->getRoad(Direction::East)->toString() == p3.getColor()+"|"+Constants::RESET);
    board.placeRoad(p4, 'o', Direction::West);
    CHECK(board.getTile('o')->getRoad(Direction::West)->toString() == p4.getColor()+"|"+Constants::RESET);

    CHECK_THROWS(board.placeRoad(p3, 'a', Direction::NorthEast));
    CHECK_THROWS(board.placeRoad(p3, 'a', Direction::NorthEast));
    CHECK_THROWS(board.placeRoad(p4, 'a', Direction::NorthWest));

}

TEST_CASE("Can place settlement") {

    Board board;
    Player p1("1",Constants::RED);
    Player p2("2",Constants::BLUE);

    CHECK(board.canPlaceFirstSettlement('a', Direction::South));
    board.placeSettlement(p1, 'a', Direction::South);
    board.placeRoad(p1,'a',Direction::SouthEast);
    board.placeRoad(p1,'b',Direction::SouthWest);

    CHECK_FALSE(board.canPlaceFirstSettlement('a', Direction::South));
    CHECK_FALSE(board.canPlaceFirstSettlement('a', Direction::SouthEast));
    CHECK_FALSE(board.canPlaceFirstSettlement('a', Direction::SouthWest));
    CHECK_FALSE(board.canPlaceFirstSettlement('d',Direction::NorthEast));
    CHECK_FALSE(board.canPlaceFirstSettlement('d',Direction::North));
    CHECK_FALSE(board.canPlaceFirstSettlement('d',Direction::SouthEast));
    CHECK_FALSE(board.canPlaceFirstSettlement('e',Direction::NorthWest));
    CHECK_FALSE(board.canPlaceFirstSettlement('e',Direction::North));
    CHECK_FALSE(board.canPlaceFirstSettlement('e',Direction::SouthWest));

    CHECK(board.canPlaceFirstSettlement('a',Direction::NorthEast));
    CHECK(board.canPlaceFirstSettlement('a',Direction::NorthWest));
    for (char tile = 'b'; tile <= 's'; tile++) {
        CHECK(board.canPlaceFirstSettlement(tile,Direction::South));
    }

    CHECK(board.canPlaceSettlement(p1, 'b',Direction::South));
    board.placeSettlement(p1,'b',Direction::South);
    CHECK_FALSE(board.canPlaceSettlement(p1,'b',Direction::SouthWest));
    for (char tile = 'a'; tile <= 's'; tile++) {
        CHECK_FALSE(board.canPlaceSettlement(p1,tile,Direction::South));
    }
    board.placeRoad(p1,'b',Direction::West);
    CHECK(board.canPlaceSettlement(p1,'b',Direction::NorthWest));
    CHECK_FALSE(board.canPlaceSettlement(p2,'b',Direction::NorthWest));
    board.placeSettlement(p1,'b',Direction::NorthWest);

    CHECK(board.canUpgradeSettlement(p1,'a',Direction::South));
    CHECK_FALSE(board.canUpgradeSettlement(p1,'a',Direction::SouthEast));
    CHECK(board.canUpgradeSettlement(p1,'b',Direction::NorthWest));
    CHECK_FALSE(board.canUpgradeSettlement(p2,'b',Direction::NorthWest));
    board.upgradeSettlement(p2,'b',Direction::NorthWest);
    CHECK_FALSE(board.canUpgradeSettlement(p1,'b',Direction::NorthWest));

}

TEST_CASE("Can place roads") {

    Board board;
    Player p1("1",Constants::RED);
    Player p2("2",Constants::BLUE);

    board.placeSettlement(p1,'a',Direction::South);
    CHECK(board.canPlaceRoad(p1,'a',Direction::SouthEast));
    CHECK(board.canPlaceRoad(p1,'a',Direction::SouthWest));
    board.placeRoad(p1,'a',Direction::SouthWest);
    CHECK_FALSE(board.canPlaceRoad(p1,'a',Direction::SouthWest));
    CHECK_FALSE(board.canPlaceRoad(p1,'a',Direction::NorthEast));
    CHECK_FALSE(board.canPlaceRoad(p2,'a',Direction::West));
    CHECK(board.canPlaceRoad(p1,'a',Direction::West));
    CHECK_FALSE(board.canPlaceRoad(p2,'a',Direction::NorthWest));
    CHECK_FALSE(board.canPlaceRoad(p2,'d',Direction::East));
    board.placeRoad(p1,'a',Direction::East);
    board.placeRoad(p2,'q',Direction::West);
    CHECK(board.canPlaceRoad(p2,'m',Direction::SouthWest));
    CHECK(board.canPlaceRoad(p2,'m',Direction::SouthEast));

}

TEST_CASE("Test producing") {

    Board board;
    Player red("1",Constants::RED);
    Player blue("2",Constants::BLUE);
    Player green("3",Constants::GREEN);
    Player yellow("4",Constants::YELLOW);

    board.placeSettlement(red,'a',Direction::South);
    board.placeSettlement(blue,'c',Direction::South);
    board.placeSettlement(green,'e',Direction::South);
    board.placeSettlement(yellow,'g',Direction::South);

    board.produce(6);
    CHECK(red.walletEquals({0,0,1,0,0}));
    CHECK(blue.walletEquals({0,0,0,0,0}));
    CHECK(green.walletEquals({0,0,1,0,0}));
    CHECK(yellow.walletEquals({0,0,0,0,0}));

    board.placeSettlement(red,'n',Direction::South);

    board.produce(6);
    CHECK(red.walletEquals({1,0,2,0,0}));
    CHECK(blue.walletEquals({0,0,0,0,0}));
    CHECK(green.walletEquals({0,0,2,0,0}));
    CHECK(yellow.walletEquals({0,0,0,0,0}));

    board.placeSettlement(green,'d',Direction::South);
    board.upgradeSettlement(green,'d',Direction::South);
    board.upgradeSettlement(blue,'c',Direction::South);

    board.produce(9);
    CHECK(red.walletEquals({1,0,2,0,0}));
    CHECK(blue.walletEquals({0,0,0,2,0}));
    CHECK(green.walletEquals({0,0,4,0,0}));
    CHECK(yellow.walletEquals({0,0,0,0,0}));

    board.placeSettlement(yellow,'s',Direction::South);
    board.produce(11);
    CHECK(red.walletEquals({1,0,2,0,0}));
    CHECK(blue.walletEquals({0,0,0,2,0}));
    CHECK(green.walletEquals({0,3,4,0,0}));
    CHECK(yellow.walletEquals({1,0,0,0,0}));

}

TEST_CASE("Adding points") {

    Board board;
    Player red("1",Constants::RED);
    Player blue("2",Constants::BLUE);
    Player green("3",Constants::GREEN);
    Player yellow("4",Constants::YELLOW);

    board.placeSettlement(red,'a',Direction::South);
    CHECK(red.getPoints() == 1);
    board.placeSettlement(blue,'c',Direction::South);
    CHECK(blue.getPoints() == 1);
    board.placeSettlement(green,'e',Direction::South);
    CHECK(green.getPoints() == 1);
    board.placeSettlement(yellow,'g',Direction::South);
    CHECK(yellow.getPoints() == 1);

    board.placeSettlement(red,'n',Direction::South);
    CHECK(red.getPoints() == 2);

    board.placeSettlement(green,'d',Direction::South);
    board.upgradeSettlement(green,'d',Direction::South);
    board.upgradeSettlement(blue,'c',Direction::South);

    CHECK((red.getPoints() == 2));
    CHECK((blue.getPoints() == 2));
    CHECK((green.getPoints() == 3));
    CHECK((yellow.getPoints() == 1));

    board.placeSettlement(yellow,'s',Direction::South);
    CHECK(yellow.getPoints() == 2);

}
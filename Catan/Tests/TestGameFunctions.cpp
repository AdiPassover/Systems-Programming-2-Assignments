// 326627635 | adi.peisach@gmail.com

#include "doctest.h"
#include "../Game.hpp"

TEST_CASE("Test placing and upgrading payments") {

    Game game({"p1", "p2", "p3"}, false, "TestInputs/inputPlace1.txt");
    Player& p1 = game.getPlayer(0);

    game.placeSettlement(p1, true);
    CHECK(game.isSettlementBuilt('a',Direction::South));
    game.placeRoad(p1, true);
    CHECK(game.isRoadBuilt('a',Direction::SouthEast));

    p1.receiveResources({2,2,1,1,0});
    game.placeRoad(p1);
    CHECK(p1.walletEquals({1,1,1,1,0}));
    CHECK(game.isRoadBuilt('a',Direction::East));
    game.placeSettlement(p1);
    CHECK(p1.walletEquals({0,0,0,0,0}));
    CHECK(game.isSettlementBuilt('a',Direction::NorthEast));

    p1.receiveResources({3,3,1,1,0});
    CHECK_THROWS(game.placeRoad(p1));
    CHECK_THROWS(game.placeRoad(p1));
    CHECK_FALSE(game.isRoadBuilt('d',Direction::SouthEast));
    CHECK(p1.walletEquals({3,3,1,1,0}));

    game.placeRoad(p1);
    game.placeRoad(p1);
    CHECK(p1.walletEquals({1,1,1,1,0}));
    CHECK(game.isRoadBuilt('d',Direction::SouthEast));
    CHECK(game.isRoadBuilt('d',Direction::East));

    CHECK_THROWS(game.placeSettlement(p1));
    CHECK_THROWS(game.placeSettlement(p1));
    CHECK_FALSE(game.isSettlementBuilt('i',Direction::South));
    CHECK(p1.walletEquals({1,1,1,1,0}));

    game.placeSettlement(p1);
    CHECK(p1.walletEquals({0,0,0,0,0}));
    CHECK(game.isSettlementBuilt('d',Direction::South));

    p1.receiveResources({0,0,0,2,3});
    game.upgradeSettlement(p1);
    CHECK(p1.walletEquals({0,0,0,0,0}));
    CHECK(game.isCityBuilt('d',Direction::South));

    p1.receiveResources({0,0,0,2,2});
    CHECK_THROWS(game.upgradeSettlement(p1));
    CHECK(p1.walletEquals({0,0,0,2,2}));
    CHECK_FALSE(game.isCityBuilt('a',Direction::South));

}

TEST_CASE("Test rolled 7") {
    Game game({"Blue", "Red", "Green"}, false, "TestInputs/inputRoll7.txt");
    Player& green = game.getPlayer(0);
    Player& red = game.getPlayer(1);
    Player& blue = game.getPlayer(2);

    green.receiveResources({2,0,3,0,2});
    red.receiveResources({2,4,2,0,0});
    blue.receiveResources({0,0,0,2,4});

    game.startTurn(green, 7);
    CHECK(green.walletEquals({1,0,2,0,1}));
    CHECK(red.walletEquals({2,0,2,0,0}));
    CHECK(blue.walletEquals({0,0,0,2,4}));

    red.receiveResources({2,4,2,0,0});
    game.startTurn(red, 7);
    CHECK(red.walletEquals({0,2,4,0,0}));
}


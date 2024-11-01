// 326627635 | adi.peisach@gmail.com

//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../Player.hpp"
#include "doctest.h"

TEST_CASE("Using knights and points") {

    Game game({"Blue", "Red", "Green"}, false);
    Player& blue = game.getPlayer(0);
    Player& red = game.getPlayer(1);

    unique_ptr<Card> knightCard1 = make_unique<KnightCard>();
    unique_ptr<Card> pointsCard1 = make_unique<PointsCard>();

    red.receiveCard(knightCard1.get());
    red.receiveCard(pointsCard1.get());

    CHECK(red.getPoints() == 0);
    red.playCard(1,game);
    CHECK(red.getPoints() == 1);

    red.playCard(0,game);
    CHECK(red.getPoints() == 1);
    CHECK(red.getKnights() == 1);

    unique_ptr<Card> knightCard2 = make_unique<KnightCard>();
    unique_ptr<Card> knightCard3 = make_unique<KnightCard>();

    red.receiveCard(knightCard2.get());
    red.receiveCard(knightCard3.get());
    red.playCard(0,game);
    red.playCard(0,game);
    CHECK(red.getPoints() == 3);
    CHECK(red.getKnights() == 3);

    red.loseKnight();
    CHECK(red.getPoints() == 1);
    CHECK(red.getKnights() == 2);

    unique_ptr<Card> knightCard4 = make_unique<KnightCard>();
    red.receiveCard(knightCard4.get());
    red.playCard(0,game);
    CHECK(red.getPoints() == 3);
    CHECK(red.getKnights() == 3);

    red.loseKnight();
    blue.addKnight();
    red.loseKnight();
    blue.addKnight();
    red.loseKnight();
    blue.addKnight();
    CHECK_THROWS(red.loseKnight());
    CHECK(red.getPoints() == 1);
    CHECK(red.getKnights() == 0);
    CHECK(blue.getPoints() == 2);
    CHECK(blue.getKnights() == 3);

}

TEST_CASE("Using monopol") {

    Game game({"Blue", "Red", "Green", "Yellow"}, false, "TestInputs/inputCards1.txt");
    Player &blue = game.getPlayer(0);
    Player &red = game.getPlayer(1);
    Player &green = game.getPlayer(2);
    Player &yellow = game.getPlayer(3);

    red.receiveResources({1, 2, 3, 4, 5});
    blue.receiveResources({1, 2, 3, 4, 5});
    green.receiveResources({1, 2, 3, 4, 5});
    yellow.receiveResources({1, 2, 3, 4, 5});

    unique_ptr<Card> monopolCard1 = make_unique<MonopolCard>();
    red.receiveCard(monopolCard1.get());
    red.playCard(0, game); // monopol on 0
    CHECK(red.walletEquals({4, 2, 3, 4, 5}));
    CHECK(blue.walletEquals({0, 2, 3, 4, 5}));
    CHECK(green.walletEquals({0, 2, 3, 4, 5}));
    CHECK(yellow.walletEquals({0, 2, 3, 4, 5}));

    unique_ptr<Card> monopolCard2 = make_unique<MonopolCard>();
    blue.receiveCard(monopolCard2.get());
    blue.playCard(0, game); // monopol on 1
    CHECK(red.walletEquals({4, 0, 3, 4, 5}));
    CHECK(blue.walletEquals({0, 8, 3, 4, 5}));
    CHECK(green.walletEquals({0, 0, 3, 4, 5}));
    CHECK(yellow.walletEquals({0, 0, 3, 4, 5}));

    unique_ptr<Card> monopolCard3 = make_unique<MonopolCard>();
    green.receiveCard(monopolCard3.get());
    green.playCard(0, game); // monopol on 2
    CHECK(red.walletEquals({4, 0, 0, 4, 5}));
    CHECK(blue.walletEquals({0, 8, 0, 4, 5}));
    CHECK(green.walletEquals({0, 0, 12, 4, 5}));
    CHECK(yellow.walletEquals({0, 0, 0, 4, 5}));

    unique_ptr<Card> monopolCard4 = make_unique<MonopolCard>();
    yellow.receiveCard(monopolCard4.get());
    yellow.playCard(0, game); // monopol on 4
    CHECK(red.walletEquals({4, 0, 0, 4, 0}));
    CHECK(blue.walletEquals({0, 8, 0, 4, 0}));
    CHECK(green.walletEquals({0, 0, 12, 4, 0}));
    CHECK(yellow.walletEquals({0, 0, 0, 4, 20}));

}

TEST_CASE("Using year of plenty") {

    Game game({"Blue", "Red", "Green"}, false, "TestInputs/inputCards2.txt");
    Player &blue = game.getPlayer(0);
    Player &red = game.getPlayer(1);
    Player &green = game.getPlayer(2);

    unique_ptr<Card> yearOfPlentyCard1 = make_unique<YearOfPlenty>();
    red.receiveCard(yearOfPlentyCard1.get());
    red.playCard(0, game); // 1 1
    CHECK(red.walletEquals({0, 2, 0, 0, 0}));

    unique_ptr<Card> yearOfPlentyCard2 = make_unique<YearOfPlenty>();
    blue.receiveCard(yearOfPlentyCard2.get());
    blue.playCard(0, game); // 2 3
    CHECK(blue.walletEquals({0, 0, 1, 1, 0}));

    unique_ptr<Card> yearOfPlentyCard3 = make_unique<YearOfPlenty>();
    green.receiveCard(yearOfPlentyCard3.get());
    green.playCard(0, game); // 4 0
    CHECK(green.walletEquals({1, 0, 0, 0, 1}));

    unique_ptr<Card> yearOfPlentyCard4 = make_unique<YearOfPlenty>();
    red.receiveCard(yearOfPlentyCard4.get());
    red.playCard(0, game); // 0 4
    CHECK(red.walletEquals({1, 2, 0, 0, 1}));

}

TEST_CASE("Using roads card") {

    Game game({"Blue", "Red"}, false, "TestInputs/inputCards3.txt");
    Player &blue = game.getPlayer(0);
    Player &red = game.getPlayer(1);

    game.placeSettlement(red, true);
    game.placeSettlement(blue, true);

    unique_ptr<Card> roadsCard1 = make_unique<RoadsCard>();
    red.receiveCard(roadsCard1.get());
    CHECK_FALSE(game.isRoadBuilt('a', Direction::SouthEast));
    CHECK_FALSE(game.isRoadBuilt('a', Direction::East));
    red.playCard(0, game);
    CHECK(game.isRoadBuilt('a', Direction::SouthEast));
    CHECK(game.isRoadBuilt('a', Direction::East));

    unique_ptr<Card> roadsCard2 = make_unique<RoadsCard>();
    red.receiveCard(roadsCard2.get());
    CHECK_FALSE(game.isRoadBuilt('b', Direction::NorthWest));
    CHECK_FALSE(game.isRoadBuilt('b', Direction::NorthEast));
    red.playCard(0, game);
    CHECK(game.isRoadBuilt('b', Direction::NorthWest));
    CHECK(game.isRoadBuilt('b', Direction::NorthEast));


    unique_ptr<Card> roadsCard3 = make_unique<RoadsCard>();
    blue.receiveCard(roadsCard3.get());
    CHECK_FALSE(game.isRoadBuilt('n', Direction::NorthEast));
    CHECK_FALSE(game.isRoadBuilt('o', Direction::NorthWest));
    blue.playCard(0, game);
    CHECK(game.isRoadBuilt('n', Direction::NorthEast));
    CHECK(game.isRoadBuilt('o', Direction::NorthWest));

}
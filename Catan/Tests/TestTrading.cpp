// 326627635 | adi.peisach@gmail.com

#include "doctest.h"
#include "../Game.hpp"

TEST_CASE("Test resource trading") {
    Game game({"Blue", "Red", "Green"}, false,"TestInputs/inputTrading1.txt");
    Player& green = game.getPlayer(0);
    Player& red = game.getPlayer(1);
    Player& blue = game.getPlayer(2);
    blue.receiveResources({0,0,0,1,1});
    red.receiveResources({2,2,2,0,0});
    green.receiveResources({2,0,2,0,2});

    game.tradeResources(blue);
    CHECK(blue.walletEquals({2,0,0,0,0}));
    CHECK(red.walletEquals({0,2,2,1,1}));

    CHECK(green.walletEquals({2,0,2,0,2}));
    game.tradeResources(red);
    CHECK(red.walletEquals({0,1,0,1,3}));
    CHECK(green.walletEquals({2,1,4,0,0}));

    CHECK_THROWS(game.tradeResources(green));
    CHECK_THROWS(game.tradeResources(green));
    CHECK_THROWS(game.tradeResources(green));
}

TEST_CASE("Test cards and knight trading") {

    Game game({"Blue", "Red", "Green"}, false,"TestInputs/inputTrading2.txt");
    Player& green = game.getPlayer(0);
    Player& red = game.getPlayer(1);
    Player& blue = game.getPlayer(2);

    unique_ptr<Card> knight1 = make_unique<KnightCard>();
    unique_ptr<Card> knight2 = make_unique<KnightCard>();
    unique_ptr<Card> knight3 = make_unique<KnightCard>();
    unique_ptr<Card> roads1 = make_unique<RoadsCard>();
    unique_ptr<Card> points1 = make_unique<PointsCard>();

    green.receiveCard(knight1.get());
    green.receiveCard(knight2.get());
    green.receiveCard(knight3.get());
    CHECK(green.getPoints() == 0);
    CHECK(green.getKnights() == 0);

    blue.receiveCard(roads1.get());
    red.receiveCard(points1.get());
    CHECK(red.getPoints() == 0);

    game.tradeCards(green);
    CHECK(green.cardName(0) == Constants::KNIGHT_CARD);
    CHECK(green.cardName(1) == Constants::KNIGHT_CARD);
    CHECK(green.cardName(2) == Constants::POINTS_CARD);
    CHECK(red.cardName(0) == Constants::KNIGHT_CARD);
    CHECK(green.numCards() == 3);
    CHECK(red.numCards() == 1);

    game.tradeCards(red);
    game.tradeCards(red);
    CHECK(red.cardName(0) == Constants::ROADS_CARD);
    CHECK(blue.cardName(0) == Constants::KNIGHT_CARD);

    game.tradeCards(blue);
    CHECK(blue.cardName(0) == Constants::POINTS_CARD);
    CHECK(blue.numCards() == 1);
    CHECK(green.cardName(0) == Constants::KNIGHT_CARD);
    CHECK(green.cardName(1) == Constants::KNIGHT_CARD);
    CHECK(green.cardName(2) == Constants::KNIGHT_CARD);
    CHECK(green.numCards() == 3);
    CHECK(green.getPoints() + red.getPoints() + blue.getPoints() == 0);

    green.playCard(0,game);
    green.playCard(0,game);
    green.playCard(0,game);
    CHECK(green.getPoints() == 2);
    CHECK(green.getKnights() == 3);
    CHECK(green.numCards() == 0);
    CHECK_THROWS(green.playCard(0,game));

    cout << "before" << endl;
    green.printWallet();
    green.printCards();
    game.tradeKnight(green);
    cout << "after" << endl;
    green.printWallet();
    green.printCards();

    CHECK(green.getKnights() == 2);
    CHECK(red.getKnights() == 1);
    CHECK(blue.getKnights() == 0);
    CHECK(green.getPoints() == 0);
    CHECK(red.getPoints() == 0);
    CHECK(blue.getPoints() == 0);
    CHECK(green.numCards() == 1);
    CHECK(green.cardName(0) == Constants::ROADS_CARD);

    game.tradeKnight(red);
    CHECK(green.getKnights() == 3);
    CHECK(red.getKnights() == 0);
    CHECK(green.getPoints() == 2);
    CHECK(red.getPoints() == 0);

}
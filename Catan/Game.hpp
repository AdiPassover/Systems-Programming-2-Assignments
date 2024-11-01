// 326627635 | adi.peisach@gmail.com

#ifndef CATAN_GAME_HPP
#define CATAN_GAME_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include "Board/Board.hpp"

class Player;
class Card;
class Board;

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::unique_ptr;


enum class Turn {
    BuildSettlement,
    BuildRoad,
    UpgradeSettlement,

    TradeResource,
    TradeCard,
    TradeKnight,

    BuyCard,
    PlayCard,

    EndTurn
};

class Game {
    vector<Player> players;
    vector<unique_ptr<Card>> deck;
    unique_ptr<Board> board;
    unsigned int currentPlayer = 0;
    unsigned int currentCard = 0;
    bool isRandom = true;
    unique_ptr<std::istream> input;

private:
    unsigned int rollDice(unsigned int res = 0);
    vector<unsigned int> namePrice() const;
    void loseResource();
    void initDeck();
    Player* isOver();

public:
    explicit Game(vector<string> names, bool random = true, const string& inputPath = "");

    string start();
    void startTurn(Player&, unsigned int overrideDiceNum = 0);

    Turn chooseTurn();
    void makeTurn(Player&, Turn);

    void placeSettlement(Player&, bool first = false);
    void upgradeSettlement(Player&);
    void placeRoad(Player&, bool first = false);

    void tradeResources(Player&);
    void tradeCards(Player&);
    void tradeKnight(Player&);

    void buyCard(Player&);
    void playCard(Player&);

    void print() const;
    std::istream* getInput() const { return input.get(); }
    bool isCityBuilt(char tile, Direction dir) const;
    bool isSettlementBuilt(char tile, Direction dir) const;
    bool isRoadBuilt(char tile, Direction dir) const;

    unsigned int numPlayers() const;
    Player& getPlayer(unsigned int i);
};


#endif //CATAN_GAME_HPP

// 326627635 | adi.peisach@gmail.com
#include "Game.hpp"
#include "Board/Board.hpp"

unsigned int Game::rollDice(unsigned int res) {
    if (res != 0) return res;
    return (unsigned int)(rand()%6 + rand()%6 + 2);
}

void Game::placeSettlement(Player& p, bool first) {
    cout << p.getName() << " is placing a settlement. Enter tile and direction (the direction in one word)" << endl;
    string line;
    char tile;
    *input >> tile >> line;

    if (tile < 'a' || tile > 's') throw std::invalid_argument("Invalid tile letter");
    Direction dire = Directions::stringToDirection(line);

    if (!first && !p.canAfford(Constants::SETTLEMENT_COST))
        throw std::invalid_argument("Player cannot afford to place settlement");


    if (!first && board->canPlaceSettlement(p, tile, dire)) {
        p.pay(Constants::SETTLEMENT_COST);
        board->placeSettlement(p, tile, dire);
    }
    else if (first && board->canPlaceFirstSettlement(tile, dire))
        board->placeSettlement(p, tile, dire);
    else throw std::invalid_argument("Cannot place settlement");
}

void Game::upgradeSettlement(Player& p) {
    cout << p.getName() << " is upgrading a settlement. Enter tile and direction (the direction in one word)" << endl;
    string line;
    char tile;
    *input >> tile >> line;

    if (tile < 'a' || tile > 's') throw std::invalid_argument("Invalid tile letter");
    Direction dire = Directions::stringToDirection(line);

    if (!p.canAfford(Constants::CITY_COST))
        throw std::invalid_argument("Player cannot afford to upgrade settlement");

    if (board->canUpgradeSettlement(p, tile, dire)) {
        p.pay(Constants::CITY_COST);
        board->upgradeSettlement(p, tile, dire);
    }
    else throw std::invalid_argument("Cannot upgrade settlement");
}

void Game::placeRoad(Player& p, bool first) {
    cout << p.getName() <<  " is placing a road. Enter tile and direction (the direction in one word)" << endl;
    string line;
    char tile;
    *input >> tile >> line;

    if (tile < 'a' || tile > 's') throw std::invalid_argument("Invalid tile letter");
    Direction dire = Directions::stringToDirection(line);

    if (!first && !p.canAfford(Constants::ROAD_COST))
        throw std::invalid_argument("Player cannot afford to place road");

    if (board->canPlaceRoad(p, tile, dire)) {
        if (!first) p.pay(Constants::ROAD_COST);
        board->placeRoad(p, tile, dire);
    }
    else throw std::invalid_argument("Cannot place road");
}

vector<unsigned int> Game::namePrice() const {
    cout << "Enter price" << endl;
    cout << Constants::RESOURCES_ICONS << endl;
    vector<unsigned int> price(5,0);
    *input >> price[0] >> price[1] >> price[2] >> price[3] >> price[4];
    return price;
}

void Game::tradeResources(Player& p) {
    string line;
    cout << "You are selling: " << endl;
    vector<unsigned int> sell = namePrice();
    if (!p.canAfford(sell)) throw std::invalid_argument("Player cannot afford to sell");
    cout << "You are buying: " << endl;
    vector<unsigned int> buy = namePrice();

    cout << "Enter player name" << endl;
    string name;
    *input >> name;
    for (unsigned int i = 0; i < numPlayers(); i++) {
        if (players[i].getName() == name) {
            players[i].printWallet();
            if (!players[i].canAfford(buy)) throw std::invalid_argument("Player cannot afford to buy");
            cout << players[i].getName() << " do you agree? (y/n)" << endl;
            *input >> line;
            if (line != "y") {
                cout << "Trade declined" << endl;
                return;
            }
            p.pay(sell);
            p.receiveResources(buy);
            players[i].pay(buy);
            players[i].receiveResources(sell);
            return;
        }
    }
    throw std::invalid_argument("Player not found");
}

void Game::buyCard(Player& p) {
    if (currentCard == deck.size())
        throw std::invalid_argument("No more cards to buy");
    if (!p.canAfford(Constants::CARD_COST))
        throw std::invalid_argument("Player cannot afford to buy card");
    p.pay(Constants::CARD_COST);
    cout << "You received: " << deck[currentCard]->toString() << endl;
    p.receiveCard(deck[currentCard++].get());
}

void Game::playCard(Player& p) {
    if (p.numCards() == 0) {
        cout << "No cards to play" << endl;
        return;
    }

    p.printCards();
    cout << "Enter card index" << endl;
    unsigned int index;
    *input >> index;
    p.playCard(index, *this);
}

Turn Game::chooseTurn() {
    cout << "Choose turn:" << endl;
    string line = "";

    while (true) {
        cout << "build | trade | card | end" << endl;
        *input >> line;
        if (line == "build") {
            cout << "settlement | road | city" << endl;
            *input >> line;
            if (line == "settlement") return Turn::BuildSettlement;
            if (line == "road") return Turn::BuildRoad;
            if (line == "city") return Turn::UpgradeSettlement;
        } else if (line == "trade") {
            cout << "resource | card | knight" << endl;
            *input >> line;
            if (line == "resource") return Turn::TradeResource;
            if (line == "card") return Turn::TradeCard;
            if (line == "knight") return Turn::TradeKnight;
        } else if (line == "card") {
            cout << "buy | play" << endl;
            *input >> line;
            if (line == "buy") return Turn::BuyCard;
            if (line == "play") return Turn::PlayCard;
        } else if (line == "end") {
            return Turn::EndTurn;
        }
    }
}

void Game::makeTurn(Player& p, Turn t) {
    try {
        switch (t) {
            case Turn::BuildSettlement:
                placeSettlement(p);
                break;
            case Turn::BuildRoad:
                placeRoad(p);
                break;
            case Turn::UpgradeSettlement:
                upgradeSettlement(p);
                break;
            case Turn::TradeResource:
                tradeResources(p);
                break;
            case Turn::TradeCard:
                tradeCards(p);
                break;
            case Turn::TradeKnight:
                tradeKnight(p);
                break;
            case Turn::BuyCard:
                buyCard(p);
                break;
            case Turn::PlayCard:
                playCard(p);
                break;
            case Turn::EndTurn:
                break;
        }
    } catch (std::invalid_argument e) {
        cout << e.what() << endl;
    }
}

string Game::start() {
    for (unsigned int i = 0; i < numPlayers(); i++) {
        while (true) {
            try {
                placeSettlement(players[i],true);
                break;
            } catch (std::invalid_argument e) {
                cout << e.what() << endl;
            }
        }
        print();
        while (true) {
            try {
                placeRoad(players[i],true);
                break;
            } catch (std::invalid_argument e) {
                cout << e.what() << endl;
            }
        }
        print();
    }
    for (unsigned int i = numPlayers()-1; true; i--) {
        while (true) {
            try {
                placeSettlement(players[i],true);
                break;
            } catch (std::invalid_argument e) {
                cout << e.what() << endl;
            }
        }
        print();
        while (true) {
            try {
                placeRoad(players[i],true);
                break;
            } catch (std::invalid_argument e) {
                cout << e.what() << endl;
            }
        }
        print();
        if (i == 0) break;
    }

    for (unsigned int i = 2; i <= 12; i++) {
        board->produce(i);
    }

    while (true) {
        startTurn(players[currentPlayer]);
        currentPlayer++;
        currentPlayer %= numPlayers();
        Player* p = isOver();
        if (p != nullptr) return p->getName();
    }
}

void Game::loseResource() {
    for (unsigned int i = 0; i < numPlayers(); i++) {
        unsigned int num = players[i].numResources();
        if (num < 7) continue;
        cout << players[i].getName() << " must lose half their resources: " << num/2 << endl;
        players[i].printWallet();

        while (true) {
            try {
                vector<unsigned int> loss = namePrice();
                if (!players[i].canAfford(loss))
                    throw std::invalid_argument("Player cannot afford to lose resources");
                unsigned int sum = 0;
                for (unsigned int j = 0; j < loss.size(); j++) sum += loss[j];
                if (sum < num/2) throw std::invalid_argument("Must lose half resources");

                players[i].pay(loss);
                break;
            } catch (std::invalid_argument e) {
                cout << e.what() << endl;
            }
        }
    }
}

void Game::startTurn(Player& p, unsigned int overrideDiceNum) {
    cout << p.getName() << "'s turn" << endl;
    unsigned int roll = rollDice(overrideDiceNum);
    cout << "Rolled " << roll << endl;
    if (roll != 7) board->produce(roll);
    else loseResource();

    while (true) {
        p.printWallet();
        Turn t = chooseTurn();
        if (t == Turn::EndTurn) break;
        makeTurn(p, t);
    }
    print();
}

Player* Game::isOver() {
    for (unsigned int i = 0; i < numPlayers(); i++) {
        if (players[i].getPoints() >= 10) {
            cout << players[i].getName() << " wins!" << endl;
            return &players[i];
        }
    }
    return nullptr;
}

Game::Game(vector<string> names, bool random, const string& inputPath) : players(), deck(), isRandom(random) {
    if (names.size() < 2) throw std::invalid_argument("Not enough players");
    if (names.size() > 4) throw std::invalid_argument("Too many players");

    if (inputPath.empty()) {
        input = std::make_unique<std::istream>(cin.rdbuf());
    } else {
        auto fileStream = std::make_unique<std::ifstream>(inputPath);
        if (!fileStream->is_open()) {
            throw std::runtime_error("Unable to open file: " + inputPath);
        }
        input = std::move(fileStream);
    }

    board = std::make_unique<Board>();
    if (isRandom)
        srand(time(nullptr));
    else srand(0);

    for (unsigned int i = 0; i < names.size(); i++) {
        Player p(names[i], Constants::COLORS[i]);
        unsigned int index = (unsigned int)rand()%(players.size()+1);
        players.insert(players.begin() + index, p);
    }
    print();
    initDeck();
}

void Game::print() const {
    board->print();
}

void Game::initDeck() {
    unsigned int numKnights = 3;
    unsigned int numRoads = 3;
    unsigned int numMonopolies = 4;
    unsigned int numYears = 4;
    unsigned int numPoints = 4;
    unsigned int sum = numKnights+numRoads+numMonopolies+numYears+numPoints;
    deck.resize(sum);
    for (unsigned int i = 0; i < sum; i++) {
        int r = rand()%5;
        if (r == 0 && numKnights > 0) {
            deck[i] = std::make_unique<KnightCard>();
            numKnights--;
        } else if (r == 1 && numRoads > 0) {
            deck[i] = std::make_unique<RoadsCard>();
            numRoads--;
        } else if (r == 2 && numMonopolies > 0) {
            deck[i] = std::make_unique<MonopolCard>();
            numMonopolies--;
        } else if (r == 3 && numYears > 0) {
            deck[i] = std::make_unique<YearOfPlenty>();
            numYears--;
        } else if (r == 4 && numPoints > 0) {
            deck[i] = std::make_unique<PointsCard>();
            numPoints--;
        } else i--;
    }
}

void Game::tradeCards(Player& p) {
    p.printCards();
    cout << "Enter card index for selling" << endl;
    unsigned int sellIndex;
    *input >> sellIndex;
    cout << "Enter player name" << endl;
    string name;
    *input >> name;
    for (unsigned int i = 0; i < numPlayers(); i++) {
        if (players[i].getName() == name) {
            if (players[i].numCards() == 0) {
                cout << "No cards to buy" << endl;
                return;
            }
            players[i].printCards();
            cout << "Enter card index for buying" << endl;
            unsigned int buyIndex;
            *input >> buyIndex;
            cout << p.getName() << " do you agree? (y/n)" << endl;
            string line;
            *input >> line;
            if (line != "y") {
                cout << "Trade declined" << endl;
                return;
            }
            Card* sell = p.loseCard(sellIndex);
            Card* buy = players[i].loseCard(buyIndex);
            players[i].receiveCard(sell);
            p.receiveCard(buy);
            return;
        }
    }
}

unsigned int Game::numPlayers() const {
    return players.size();
}

Player &Game::getPlayer(unsigned int i) {
    return players[i];
}

void Game::tradeKnight(Player& p) {
    if (p.getKnights() == 0) {
        cout << "No knights to trade" << endl;
        return;
    }

    cout << "Enter player name" << endl;
    string name;
    *input >> name;

    for (unsigned int i = 0; i < numPlayers(); i++) {
        if (players[i].getName() == name) {
            if (players[i].numCards() == 0)
                throw std::invalid_argument("No cards to trade");
            players[i].printCards();
            cout << "Enter card index for buying" << endl;
            unsigned int buyIndex;
            *input >> buyIndex;
            cout << p.getName() << " do you agree? (y/n)" << endl;
            string line;
            *input >> line;
            if (line != "y") {
                cout << "Trade declined" << endl;
                return;
            }
            p.loseKnight();
            Card* card = players[i].loseCard(buyIndex);
            players[i].addKnight();
            p.receiveCard(card);
            return;
        }
    }
}

bool Game::isCityBuilt(char tile, Direction dir) const {
    return board->getTile(tile)->getSettlement(dir)->getLevel() == 2;
}

bool Game::isSettlementBuilt(char tile, Direction dir) const {
    return board->getTile(tile)->getSettlement(dir)->isBuilt();
}

bool Game::isRoadBuilt(char tile, Direction dir) const {
    return board->getTile(tile)->getRoad(dir)->isBuilt();
}

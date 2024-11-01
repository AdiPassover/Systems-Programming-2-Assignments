// 326627635 | adi.peisach@gmail.com

#ifndef CATAN_PLAYER_HPP
#define CATAN_PLAYER_HPP
#include <string>
#include <utility>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "Constants.hpp"
#include "Cards/KnightCard.hpp"
#include "Cards/PointsCard.hpp"
#include "Cards/RoadsCard.hpp"
#include "Cards/MonopolCard.hpp"
#include "Cards/YearOfPlenty.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::unique_ptr;

class Player {
private:
    string name;
    unsigned int id;
    vector<unsigned int> wallet;
    vector<Card*> cards;
    string color;
    unsigned int points;
    unsigned int numKnights;

    static unsigned int playerNum;

public:
    Player(string n, string color) : name(std::move(n)), wallet(5,0), points(0), numKnights(0), color(std::move(color)), cards() {
        id = playerNum;
        playerNum++;
    }

    string getName() const { return name; }
    unsigned int getId() const { return id; }
    string getColor() const { return color; }
    unsigned int getPoints() const { return points; }
    unsigned int getKnights() const { return numKnights; }
    void printWallet() const;

    void addPoints(unsigned int p) { points += p; }
    void losePoints(unsigned int p) { if (points < p) throw std::invalid_argument("No points"); points -= p; }

    void addKnight();
    void loseKnight();

    bool canAfford(vector<unsigned int> resources) const;
    bool walletEquals(vector<unsigned int> resources) const;
    void pay(vector<unsigned int> resources);
    void pay(unsigned int product, unsigned int amount) { wallet[product] -= amount; }

    unsigned int numProducts(unsigned int product) const { return wallet[product]; }
    unsigned int numResources() const;
    void receiveProduct(unsigned int product, unsigned int amount) { wallet[product] += amount; }
    void receiveResources(vector<unsigned int> resources);

    void printCards() const;
    void playCard(unsigned int i, Game& g)
    { if (i >= numCards()) throw std::invalid_argument("Invalid index"); cards[i]->play(*this, g); loseCard(i); }
    void receiveCard(Card* c) { cards.push_back(c); }
    Card* loseCard(unsigned int i);
    unsigned int numCards() const { return cards.size(); }
    string cardName(unsigned int i)
        { if (i >= numCards()) throw std::invalid_argument("Invalid index"); return cards[i]->toString(); }

};

#endif
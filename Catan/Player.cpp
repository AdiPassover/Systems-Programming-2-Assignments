// 326627635 | adi.peisach@gmail.com
#include "Player.hpp"

unsigned int Player::playerNum = 0;

bool Player::canAfford(vector<unsigned int> resources) const {
    for (size_t i = 0; i < resources.size(); i++)
        if (wallet[i] < resources[i]) return false;
    return true;
}

void Player::pay(vector<unsigned int> resources) {
    if (!canAfford(resources)) throw std::invalid_argument("Player cannot afford to pay");
    for (size_t i = 0; i < resources.size(); i++)
        wallet[i] -= resources[i];
}

void Player::receiveResources(vector<unsigned int> resources) {
    for (size_t i = 0; i < resources.size(); i++)
        wallet[i] += resources[i];
}

unsigned int Player::numResources() const {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < wallet.size(); i++) sum += wallet[i];
    return sum;
}

void Player::printWallet() const {
    cout << color << "Points: " << points << " Knights: " << numKnights << " Cards: " << numCards() << Constants::RESET << endl;
    cout << Constants::RESOURCES_ICONS << endl;
    cout << color;
    for (size_t i = 0; i < wallet.size(); i++)
        cout << wallet[i] << "  ";
    cout << Constants::RESET << endl;
}

void Player::printCards() const {
    cout << "Cards: " << endl;
    for (size_t i = 0; i < cards.size(); i++)
        cout << i << ": " << cards[i]->toString() << " ";
    cout << endl;
}

Card* Player::loseCard(unsigned int i) {
    if (i >= cards.size()) throw std::invalid_argument("Invalid card index");
    Card* ret = cards[i];
    cards.erase(cards.begin() + i);
    return ret;
}

void Player::addKnight() {
    numKnights++;
    if (numKnights == 3) points += 2;
}

void Player::loseKnight() {
    if (numKnights == 0) throw std::invalid_argument("No knights to lose");
    if (numKnights == 3) points -= 2;
    numKnights--;
}

bool Player::walletEquals(vector<unsigned int> resources) const {
    for (size_t i = 0; i < resources.size(); i++)
        if (wallet[i] != resources[i]) return false;
    return true;
}

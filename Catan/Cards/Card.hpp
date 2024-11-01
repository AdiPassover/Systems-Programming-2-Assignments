// 326627635 | adi.peisach@gmail.com

#ifndef CATAN_CARD_HPP
#define CATAN_CARD_HPP
#include <string>
using std::string;
class Game;
class Player;

class Card {

public:
    virtual void play(Player&, Game&) = 0;
    virtual string toString() const = 0;
    virtual ~Card() = default;

};

#endif //CATAN_CARD_HPP
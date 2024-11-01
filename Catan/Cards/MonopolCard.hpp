// 326627635 | adi.peisach@gmail.com
#ifndef CATAN_MONOPOLCARD_HPP
#define CATAN_MONOPOLCARD_HPP
#include "Card.hpp"
#include "../Game.hpp"

class MonopolCard : public Card {
public:
    void play(Player&, Game&) override;
    string toString() const override;

};


#endif //CATAN_MONOPOLCARD_HPP

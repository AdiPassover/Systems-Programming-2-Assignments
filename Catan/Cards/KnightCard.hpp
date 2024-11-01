// 326627635 | adi.peisach@gmail.com

#ifndef CATAN_KNIGHTCARD_HPP
#define CATAN_KNIGHTCARD_HPP
#include "Card.hpp"
#include "../Player.hpp"

class KnightCard : public Card {
public:
    void play(Player&, Game&) override;
    string toString() const override;
};


#endif //CATAN_KNIGHTCARD_HPP

// 326627635 | adi.peisach@gmail.com

#ifndef CATAN_ROADSCARD_HPP
#define CATAN_ROADSCARD_HPP
#include "Card.hpp"
#include "../Game.hpp"

class RoadsCard : public Card {
public:
    void play(Player&, Game&) override;
    string toString() const override;
};


#endif //CATAN_ROADSCARD_HPP

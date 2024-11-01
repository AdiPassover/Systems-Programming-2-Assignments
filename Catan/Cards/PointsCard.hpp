// 326627635 | adi.peisach@gmail.com

#ifndef CATAN_POINTSCARD_HPP
#define CATAN_POINTSCARD_HPP
#include "Card.hpp"
#include "../Player.hpp"

class PointsCard : public Card {
public:
    void play(Player&, Game&) override;
    string toString() const override;
};

#endif //CATAN_POINTSCARD_HPP
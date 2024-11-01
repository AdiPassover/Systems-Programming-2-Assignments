// 326627635 | adi.peisach@gmail.com
#include "PointsCard.hpp"

void PointsCard::play(Player& p, Game& g) {
    p.addPoints(1);
}

string PointsCard::toString() const {
    return Constants::POINTS_CARD;
}
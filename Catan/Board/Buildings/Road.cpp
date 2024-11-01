// 326627635 | adi.peisach@gmail.com
#include "Road.hpp"

string Road::orientationString() const {
    if (orientation == Oriention::Vertical)
        return "|";
    if (orientation == Oriention::DiagonalLeft)
        return "\\";
    return "/";
}

string Road::toString() const {
    if (isBuilt())
        return player->getColor() + orientationString() + Constants::RESET;
    return orientationString();
}

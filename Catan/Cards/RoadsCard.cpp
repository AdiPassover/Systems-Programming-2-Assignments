// 326627635 | adi.peisach@gmail.com
#include "RoadsCard.hpp"

void RoadsCard::play(Player &player, Game &game) {
    game.print();
    while (true) {
        try {
            game.placeRoad(player,true);
            break;
        } catch (const std::exception& e) {
            cout << e.what() << endl;
        }
    }
    while (true) {
        try {
            game.placeRoad(player,true);
            break;
        } catch (const std::exception& e) {
            cout << e.what() << endl;
        }
    }
}

string RoadsCard::toString() const {
    return Constants::ROADS_CARD;
}
// 326627635 | adi.peisach@gmail.com

#ifndef CATAN_YEAROFPLENTY_HPP
#define CATAN_YEAROFPLENTY_HPP
#include <iostream>
#include "Card.hpp"
#include "../Player.hpp"
#include "../Constants.hpp"

using std::cout;
using std::cin;
using std::endl;

class YearOfPlenty : public Card {
public:
    void play(Player&, Game&) override;
    string toString() const override;
};


#endif //CATAN_YEAROFPLENTY_HPP

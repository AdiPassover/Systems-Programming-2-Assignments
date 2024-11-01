// 326627635 | adi.peisach@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Game.hpp"

TEST_CASE("Test full game") {
    Game game({"Blue", "Red", "Green"}, false, "TestInputs/inputGame.txt");
    CHECK(game.start() == "Blue");
}
// 326627635 | adi.peisach@gmail.com
#include "Game.hpp"

int main() {
    srand(time(nullptr));
    vector<string> players = {"Blue", "Red", "Green"};
    Game game(players);
    game.start();

    return 0;
}

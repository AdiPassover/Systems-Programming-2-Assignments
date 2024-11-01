// 326627635 | adi.peisach@gmail.com
#include "Direction.hpp"

Direction Directions::stringToDirection(string s) {
    for (char& c : s) {
        if (c >= 'A' && c <= 'Z') c = c + 'a' - 'A';
    }
    if (s == "north") return Direction::North;
    else if (s == "northeast") return Direction::NorthEast;
    else if (s == "east") return Direction::East;
    else if (s == "southeast") return Direction::SouthEast;
    else if (s == "south") return Direction::South;
    else if (s == "southwest") return Direction::SouthWest;
    else if (s == "west") return Direction::West;
    else if (s == "northwest") return Direction::NorthWest;
    throw std::invalid_argument("Invalid direction string");
}

Direction Directions::sum(Direction d, int i) {
    return static_cast<Direction>((static_cast<int>(d) + i + 8) % 8);
}

Direction Directions::sumSet(Direction d, int i) {
    int sign = i / std::abs(i);
    Direction ans = sum(d,i);
    if (ans == Direction::West || ans == Direction::East)
        ans = sum(ans,sign);
    return ans;
}

Direction Directions::sumRoad(Direction d, int i) {
    int sign = i / std::abs(i);
    Direction ans = sum(d,i);
    if (ans == Direction::North || ans == Direction::South)
        ans = sum(ans,sign);
    return ans;
}

vector<Direction> Directions::nearestRoads(Direction d) {
    vector<Direction> ans(2);
    if (d == Direction::North || d == Direction::South) {
        ans[0] = sum(d,-1);
        ans[1] = sum(d,1);
    } else if (d == Direction::NorthEast || d == Direction::SouthWest) {
        ans[0] = d;
        ans[1] = sum(d,1);
    } else {
        ans[0] = sum(d,-1);
        ans[1] = d;
    }
    return ans;
}

vector<Direction> Directions::nearestSettlements(Direction d) {
    vector<Direction> ans(2);
    if (d == Direction::East || d == Direction::West) {
        ans[0] = sum(d,-1);
        ans[1] = sum(d,1);
    } else if (d == Direction::NorthEast || d == Direction::SouthWest) {
        ans[0] = sum(d,-1);
        ans[1] = d;
    } else {
        ans[0] = d;
        ans[1] = sum(d,1);
    }
    return ans;

}

Direction Directions::opposite(Direction d) {
    return sum(d, 4);
}

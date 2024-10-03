#include <iostream>
#include <cassert>
#include "Pos.h"
#include "Room.h"
#include "Enemy.h"
#include "Player.h"
#include "animations.h"
#include "nums.h"

int main() {
    Pos::unittest();
    Room::unittest();
    Enemy::unittest();
    Player::unittest();
    aniunittest();
    std::cout << "All Tests Are Done!";

    return 0;
}

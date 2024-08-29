#include <iostream>
#include <cassert>
#include "Pos.h"
#include "Room.h"
#include "Enemy.h"
#include "Player.h"

int main() {
    Pos::unittest();
    Room::unittest();
    // Enemy::unittest();
    // Player::unittest();
    std::cout << "All Tests Are Done!";

    return 0;
}

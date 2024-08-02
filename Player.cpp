#include "Player.h"
#include <iostream>

int Player::getHealth() {
    return health;
}

Point Player::getPos() {
    return currentLocation;
}

void Player::getDisplay() {
    std::cout << display << std::endl;
}

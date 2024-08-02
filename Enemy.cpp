#include "Enemy.h"
#include <iostream>

Point Enemy::getPos() {
    return position;
}

int Enemy::getHealth() {
    return health;
}

void Enemy::getDisplay() {
    std::cout << display << std::endl;
}

int Enemy::getDifficulty() {
    return difficulty;
}

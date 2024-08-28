#include "Enemy.h"
#include "Pos.h"
#include <cassert>


// Constructor with Pos, skin, and difficulty
Enemy::Enemy(Pos pos, char skin, int difficulty) : Position(pos), skin(skin), difficulty(difficulty) {
    health = 100; // Example default value
}

// Constructor with skin and health
Enemy::Enemy(char skin, int health) : skin(skin), health(health) {
    // Other initialization
}

// Getters
int Enemy::getHealth() {
    return health;
}

Pos Enemy::getPos() {
    return Position;
}

int Enemy::getX() {
    return Position.getX();
}

int Enemy::getY() {
    return Position.getY();
}

char Enemy::getSkin() {
    return skin;
}

int Enemy::getDifficulty() {
    return difficulty;
}

// Setters
void Enemy::setHealth(int health) {
    this->health = health;
}

void Enemy::setPos(Pos pos) {
    this->Position = pos;
}

void Enemy::setX(int x) {
    this->Position.setX(x);
}

void Enemy::setY(int y) {
    this->Position.setY(y);
}

void Enemy::setSkin(char skin) {
    this->skin = skin;
}

void Enemy::setDifficulty(int difficulty) {
    this->difficulty = difficulty;
}

void Enemy::unittest() {
    // Test constructor with skin and health
    Enemy enemyTest('P', 20);
    assert(enemyTest.getSkin() == 'P');
    assert(enemyTest.getHealth() == 20);

    // Test setters and getters for skin and health
    enemyTest.setSkin('A');
    enemyTest.setHealth(5);
    assert(enemyTest.getSkin() == 'A');
    assert(enemyTest.getHealth() == 5);

    // Test constructor with Pos, skin, and difficulty
    Pos pos(2, 3);
    Enemy enemyTestExpanded(pos, 'M', 2);
    assert(enemyTestExpanded.getPos().getX() == 2);
    assert(enemyTestExpanded.getPos().getY() == 3);
    assert(enemyTestExpanded.getSkin() == 'M');
    assert(enemyTestExpanded.getHealth() == 100);  // Default health is 100
    assert(enemyTestExpanded.getDifficulty() == 2);

    // Test setters and getters for Position, difficulty, and skin
    enemyTestExpanded.setSkin('B');
    enemyTestExpanded.setHealth(7);
    enemyTestExpanded.setDifficulty(3);
    enemyTestExpanded.setPos(Pos(4, 5));
    assert(enemyTestExpanded.getSkin() == 'B');
    assert(enemyTestExpanded.getHealth() == 7);
    assert(enemyTestExpanded.getDifficulty() == 3);
    assert(enemyTestExpanded.getPos().getX() == 4);
    assert(enemyTestExpanded.getPos().getY() == 5);

    // Test setting and getting X and Y coordinates
    enemyTestExpanded.setX(6);
    enemyTestExpanded.setY(7);
    assert(enemyTestExpanded.getX() == 6);
    assert(enemyTestExpanded.getY() == 7);
}

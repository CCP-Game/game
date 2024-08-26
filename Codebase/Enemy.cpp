#include "Enemy.h"
#include <cassert>
#include "Player.h"



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

void Enemy::unittest(){
    Enemy enemytest = Enemy('P', 20);
    assert(enemytest.getSkin() == 'P');
    assert(enemytest.getHealth() == 20);
    enemytest.setSkin('A');
    enemytest.setHealth(5);
    assert(enemytest.getSkin() == 'A');
    assert(enemytest.getHealth() == 5);

    Enemy enemytestExpaned = Enemy(Pos(2,3), 'M', 2);
    //assert(enemytestExpaned.getPos().equals(Pos(2, 3)));
    assert(enemytestExpaned.getSkin() == 'M');
    assert(enemytestExpaned.getHealth() == 100);
    assert(enemytestExpaned.getDifficulty() == 2);
    enemytestExpaned.setSkin('B');
    enemytestExpaned.setHealth(7);
    enemytestExpaned.setDifficulty(3);
    assert(enemytestExpaned.getSkin() == 'B');
    assert(enemytestExpaned.getHealth() == 7);
    assert(enemytestExpaned.getDifficulty() == 3);
}

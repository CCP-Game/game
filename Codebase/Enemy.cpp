#include "Enemy.h"
#include "Pos.h"
#include "Pos.cpp"

// Constructor
Enemy::Enemy(Pos pos, char skin, int difficulty) : Position(pos), skin(skin), difficulty(difficulty)
{
    health = 100; // Example default value
}

// construct just skin and difficulty
Enemy::Enemy(char skin, int difficulty) : skin(skin), difficulty(difficulty)
{
    health = 100; // Example default value
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

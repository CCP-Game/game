#include "Enemy.h"
#include "Pos.h"
#include <cassert>
#include <iostream>

/*!
 * @brief Constructs an Enemy with a given position, skin, and difficulty.
 * 
 * @param pos The position of the enemy.
 * @param skin The character representing the enemy's appearance.
 * @param difficulty The difficulty level of the enemy.
 */
Enemy::Enemy(Pos pos, char skin, int difficulty) : Position(pos), skin(skin), difficulty(difficulty) {
    health = 100; // Example default value
}

/*!
 * @brief Constructs an Enemy with a given skin and health.
 * 
 * @param skin The character representing the enemy's appearance.
 * @param health The health of the enemy.
 */
Enemy::Enemy(char skin, int health) : skin(skin), health(health), difficulty(1) {
    // Other initialization
}

/*!
 * @brief Gets the health of the enemy.
 * 
 * @return int The current health of the enemy.
 */
int Enemy::getHealth() {
    return health;
}

/*!
 * @brief Gets the position of the enemy.
 * 
 * @return Pos The current position of the enemy.
 */
Pos Enemy::getPos() {
    return Position;
}

/*!
 * @brief Gets the X-coordinate of the enemy's position.
 * 
 * @return int The X-coordinate.
 */
int Enemy::getX() {
    return Position.getX();
}

/*!
 * @brief Gets the Y-coordinate of the enemy's position.
 * 
 * @return int The Y-coordinate.
 */
int Enemy::getY() {
    return Position.getY();
}

/*!
 * @brief Gets the character representing the enemy's appearance.
 * 
 * @return char The character representing the skin.
 */
char Enemy::getSkin() {
    return skin;
}

/*!
 * @brief Gets the difficulty level of the enemy.
 * 
 * @return int The difficulty level.
 */
int Enemy::getDifficulty() {
    return difficulty;
}

/*!
 * @brief Sets the health of the enemy.
 * 
 * @param health The new health value.
 */
void Enemy::setHealth(int health) {
    this->health = health;
}

/*!
 * @brief Sets the position of the enemy.
 * 
 * @param pos The new position.
 */
void Enemy::setPos(Pos pos) {
    this->Position = pos;
}

/*!
 * @brief Sets the X-coordinate of the enemy's position.
 * 
 * @param x The new X-coordinate.
 */
void Enemy::setX(int x) {
    this->Position.setX(x);
}

/*!
 * @brief Sets the Y-coordinate of the enemy's position.
 * 
 * @param y The new Y-coordinate.
 */
void Enemy::setY(int y) {
    this->Position.setY(y);
}

/*!
 * @brief Sets the character representing the enemy's appearance.
 * 
 * @param skin The new character representing the skin.
 */
void Enemy::setSkin(char skin) {
    this->skin = skin;
}

/*!
 * @brief Sets the difficulty level of the enemy.
 * 
 * @param difficulty The new difficulty level.
 */
void Enemy::setDifficulty(int difficulty) {
    this->difficulty = difficulty;
}

/*!
 * @brief Unit test for the Enemy class.
 * 
 * This function tests the constructors, getters, and setters of the Enemy class
 * to ensure correct functionality.
 */
void Enemy::unittest() {
    std::cout << "Running Enemy unit test..." << std::endl;

    // Test constructor with skin and health
    Enemy enemyTest1('P', 20);
    assert(enemyTest1.getSkin() == 'P');
    assert(enemyTest1.getHealth() == 20);

    // Test setters and getters for skin and health
    enemyTest1.setSkin('A');
    enemyTest1.setHealth(50);
    assert(enemyTest1.getSkin() == 'A');
    assert(enemyTest1.getHealth() == 50);

    enemyTest1.setX(8);
    enemyTest1.setY(15);
    assert(enemyTest1.getX() == 8);
    assert(enemyTest1.getY() == 15);

    // Test difficulty level setter and getter
    enemyTest1.setDifficulty(4);
    assert(enemyTest1.getDifficulty() == 4);

    std::cout << "Enemy unit test passed!" << std::endl;
}


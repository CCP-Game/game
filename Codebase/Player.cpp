#include "Player.h"
#include "Pos.h"
#include "Room.h"
#include <cassert>
#include <iostream>

/*!
 * @brief Constructs a Player with specified skin and color.
 * 
 * @param skin The character representing the player's appearance.
 * @param colour The color code associated with the player.
 */
Player::Player(char skin, int colour) : skin(skin), colour(colour) {
    health = 100;  // Initialize health to 100
    currentLocation = Pos(0, 0);  // Initialize Position to (0,0)
}

/*!
 * @brief Default constructor for Player.
 * 
 * Constructs a Player with default values for skin ('P') and color (7).
 */
Player::Player() : Player('P', 7) {  // Default skin 'P' and color 7
}

/*!
 * @brief Gets the player's current health.
 * 
 * @return int The current health of the player.
 */
int Player::getHealth() {
    return health;
}

/*!
 * @brief Gets the player's skin (character representation).
 * 
 * @return char The character representing the player's appearance.
 */
char Player::getSkin() {
    return skin;
}

/*!
 * @brief Gets the player's current room.
 * 
 * @return Room The room the player is currently in.
 */
Room Player::getCurrentRoom() {
    return currentRoom;
}

/*!
 * @brief Gets the player's current position.
 * 
 * @return const Pos& The current position of the player.
 */
const Pos& Player::getPos() const {
    return currentLocation;
}

/*!
 * @brief Sets the player's position to the specified coordinates.
 * 
 * @param x The X-coordinate to set the player's position.
 * @param y The Y-coordinate to set the player's position.
 */
void Player::setPosition(int x, int y) {
    currentLocation = Pos(x, y);
}

/*!
 * @brief Sets the player's health.
 * 
 * @param health The new health value for the player.
 */
void Player::setHealth(int health) {
    this->health = health;
}

/*!
 * @brief Unit test for the Player class.
 * 
 * This function tests the constructors, getters, and setters of the Player class
 * to ensure correct functionality.
 */
void Player::unittest() {
    std::cout << "Player unittest called!" << std::endl;

    // Test constructor with parameters
    Player testPlayer('A', 5);
    assert(testPlayer.getSkin() == 'A');

    // Test setHealth and getHealth
    testPlayer.setHealth(75);
    assert(testPlayer.getHealth() == 75);

    std::cout << "All Player tests passed!" << std::endl;
}

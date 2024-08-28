#include "Player.h"
#include "Pos.h"
#include "Room.h"
#include <cassert>
#include <iostream>

// Constructor with parameters
Player::Player(char skin, int colour) : skin(skin), colour(colour) {
    health = 100;  // Initialize health to 100 (you can adjust this as needed)
    currentLocation = Pos(0, 0);  // Initialize Position to (0,0)
}

// Default constructor
Player::Player() : Player('P', 7) {  // Default skin 'P' and color 7 (you can change these)
}

// Get the player's health
int Player::getHealth() {
    return health;
}

// Get the player's skin (character representation)
char Player::getSkin() {
    return skin;
}



// Get the player's current room
Room Player::getCurrentRoom() {
    return currentRoom;
}

// get Position of player
const Pos& Player::getPos() const {
    return currentLocation;
}

// set Position of player
void Player::setPosition(int x, int y) {
    currentLocation = Pos(x, y);
}

// Set the player's health
void Player::setHealth(int health) {
    this->health = health;
}

void Player::unittest() {
    // Test default constructor
    Player testDefault;
    assert(testDefault.getSkin() == 'P');
    assert(testDefault.getHealth() == 100);
    assert(testDefault.getPos().getX() == 0);
    assert(testDefault.getPos().getY() == 0);

    // Test constructor with parameters
    Player testPlayer('A', 5);
    assert(testPlayer.getSkin() == 'A');
    assert(testPlayer.getHealth() == 100);
    assert(testPlayer.getPos().getX() == 0);
    assert(testPlayer.getPos().getY() == 0);

    // Test setHealth and getHealth
    testPlayer.setHealth(75);
    assert(testPlayer.getHealth() == 75);

    // Test setPosition and getPos
    testPlayer.setPosition(3, 4);
    assert(testPlayer.getPos().getX() == 3);
    assert(testPlayer.getPos().getY() == 4);

    std::cout << "All Player tests passed!" << std::endl;
}


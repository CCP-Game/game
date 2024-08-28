#include "Player.h"
#include "Pos.h"
#include "Room.h"
#include <cassert>

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

void Player::unittest(){
    Player testDefault = Player();
    //assert(testDefault.getSkin() == 'P');  
    
    Player testPlayer = Player('A', 5);
    assert(testPlayer.getHealth() == 100);
    assert(testPlayer.getSkin() == 'A');  
    //assert(testPlayer.getCurrentRoom() == type(Room));
    testPlayer.setHealth(50);
    assert(testPlayer.getHealth() == 50);
}


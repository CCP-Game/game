#include "Player.h"
#include "Point.h"
#include "Room.h"

// Constructor with parameters
Player::Player(char skin, int colour) : skin(skin), colour(colour) {
    health = 100;  // Initialize health to 100 (you can adjust this as needed)
    currentLocation = Point(0, 0);  // Initialize position to (0,0)
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

// get position of player
const Point& Player::getPos() const {
    return currentLocation;
}

// set position of player
void Player::setPosition(int x, int y) {
    currentLocation = Point(x, y);
}
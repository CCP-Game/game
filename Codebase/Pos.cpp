#include "Pos.h"

// default constructor
Pos::Pos() : x(0), y(0) {}

// Constructor
Pos::Pos(int x, int y) : x(x), y(y) {}

// Get X coordinate
int Pos::getX() const {
    return this->x;
}

// Get Y coordinate
int Pos::getY() const {
    return this->y;
}

// get Pos
Pos Pos::getPos() {
    return Pos(x, y);
}   

// Set both X and Y coordinates
void Pos::setXY(int x, int y) {
    this->x = x;
    this->y = y;
}

// Set X coordinate
void Pos::setX(int x) {
    this->x = x;
}

// Set Y coordinate
void Pos::setY(int y) {
    this->y = y;
}

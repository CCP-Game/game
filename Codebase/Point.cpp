#include "Point.h"

// default constructor
Point::Point() : x(0), y(0) {}

// Constructor
Point::Point(int x, int y) : x(x), y(y) {}

// Get X coordinate
int Point::getX() const {
    return this->x;
}

// Get Y coordinate
int Point::getY() const {
    return this->y;
}

// get pos
Point Point::getPos() {
    return Point(x, y);
}   

// Set both X and Y coordinates
void Point::setXY(int x, int y) {
    this->x = x;
    this->y = y;
}

// Set X coordinate
void Point::setX(int x) {
    this->x = x;
}

// Set Y coordinate
void Point::setY(int y) {
    this->y = y;
}

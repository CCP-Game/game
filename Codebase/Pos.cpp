#include "Pos.h"
#include <cassert>
#include <iostream>

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

void Pos::unittest() {
    std::cout << "Pos unittest called!" << std::endl;

    // Test default constructor
    Pos defaultPos;
    assert(defaultPos.getX() == 0);
    assert(defaultPos.getY() == 0);

    // Test parameterized constructor
    Pos testPos(5, 10);
    assert(testPos.getX() == 5);
    assert(testPos.getY() == 10);

    // Test setX and setY methods
    testPos.setX(3);
    testPos.setY(6);
    assert(testPos.getX() == 3);
    assert(testPos.getY() == 6);

    // Test setXY method
    testPos.setXY(7, 8);
    assert(testPos.getX() == 7);
    assert(testPos.getY() == 8);

    // Test getPos method
    Pos newPos = testPos.getPos();
    assert(newPos.getX() == 7);
    assert(newPos.getY() == 8);

    std::cout << "All tests passed!" << std::endl;
}


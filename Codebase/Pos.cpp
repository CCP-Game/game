#include "Pos.h"
#include <cassert>
#include <iostream>

/*!
 * @brief Default constructor for Pos.
 * 
 * Initializes the position to (0, 0).
 */
Pos::Pos() : x(0), y(0) {}

/*!
 * @brief Constructor for Pos with specified coordinates.
 * 
 * @param x The X-coordinate of the position.
 * @param y The Y-coordinate of the position.
 */
Pos::Pos(int x, int y) : x(x), y(y) {}
/*!
 * @brief Constructor utilised for nodes, storing the distance at this XY Pos to some other position.
 * @param x - the x coord
 * @param y - the y coord
 * @param distance - the distance from xy to some other x_1 y_1 point
 * 
*/
Pos::Pos(int x, int y, double dist): x(x),y(y),distance(dist){}
/*!
 * @brief Gets the X-coordinate of the position.
 * 
 * @return int The X-coordinate.
 */
int Pos::getX() const {
    return this->x;
}

/*!
 * @brief Gets the Y-coordinate of the position.
 * 
 * @return int The Y-coordinate.
 */
int Pos::getY() const {
    return this->y;
}
/**
 * @brief gets the distance from our XY to some othe XY 
 * 
 * @return the distance from our XY to some othe XY
*/
double Pos::getDistance()const{
    return this->distance;
}
/*!
*  @brief This method gets a pointer to our Pos's parent
*/
Pos* Pos::getParent(){
    return this->parent;
}
/*!
 * @brief Gets the current position.
 * 
 * @return Pos A Pos object representing the current coordinates.
 */
Pos Pos::getPos() {
    return Pos(x, y);
}

/*!
 * @brief Sets both the X and Y coordinates of the position.
 * 
 * @param x The new X-coordinate.
 * @param y The new Y-coordinate.
 */
void Pos::setXY(int x, int y) {
    this->x = x;
    this->y = y;
}

/*!
 * @brief Sets the X-coordinate of the position.
 * 
 * @param x The new X-coordinate.
 */
void Pos::setX(int x) {
    this->x = x;
}

/*!
 * @brief Sets the Y-coordinate of the position.
 * 
 * @param y The new Y-coordinate.
 */
void Pos::setY(int y) {
    this->y = y;
}
/*!
* @brief sets the the distance from our xy to some other xy coord
* @param distance - a double dictating how far away the othe rxy is.
*/
void Pos::setDistance(double d){
    this->distance = d;
}
/*!
* @brief This method sets the Pos's parent useful for the enemy search/
* @param parent - a pointer to the parent Pos
*/
void Pos::setParent(Pos* nparent){
    this->parent=nparent;
}
/*!
 * @brief Unit test for the Pos class.
 * 
 * This function tests the constructors, getters, and setters of the Pos class
 * to ensure correct functionality.
 */
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

    std::cout << "All Pos tests passed!" << std::endl;
}

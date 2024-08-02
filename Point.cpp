#include "Point.h"

Point Point::getX() {
    return x;
}

Point Point::getY() {
    return y;
}

void Point::get() {
    // This function could return both x and y or print them
    // For simplicity, we'll just print the coordinates
    std::cout << "Point(" << x << ", " << y << ")" << std::endl;
}

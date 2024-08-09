#include "Point.h"
#include "Point.cpp"
#include "Room.h"
#include "Player.h"
#include <iostream>
int main(){
    Point p1(10,10);
    std::cout<< p1.getX()<< "\n";
    return 0; 
}
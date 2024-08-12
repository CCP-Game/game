#include "Pos.h"
#include "Pos.cpp"
#include "Room.h"
#include "Player.h"
#include <iostream>
int main(){
    Pos p1(10,10);
    std::cout<< p1.getX()<< "\n";
    return 0; 
}
#include "Pos.h"
#include "Pos.cpp"
#include "Room.h"
#include "Player.h"
#include <iostream>
#include <cassert>
int main(){
    Pos p1(10,10);
    assert(p1.getX() == 10);
    assert(p1.getY() == 10);
    return 0; 
}
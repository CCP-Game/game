#include <iostream>
#include <cassert>
#include "Pos.h"
#include "Room.h"

int main() {
    Pos::unittest();
    //Room::unittest();
    Enemy::unittest();
    
    
    
    std::cout << "Test Done!";
    return 0;
}

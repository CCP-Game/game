#include "Room.h"
#include <iostream>

void Room::getDisplay() {
    std::cout << ptrToDisplay << std::endl;
}

Room* Room::getNextRoom() {
    return ptrNextRoom;
}

Room* Room::getPrevRoom() {
    return ptrPrevDoor;
}

int Room::getLevel() {
    return roomLevel;
}

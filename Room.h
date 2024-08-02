#ifndef ROOM_H
#define ROOM_H

#include "Point.h"

class Room {
public:
    int id;
    char* ptrToDisplay;
    Point newDoor;
    Room* ptrNextRoom;
    Room* ptrPrevDoor;
    Room* pointerToNextRoom;
    Room* pointerToPrevRoom;
    int roomLevel;

    void getDisplay();
    Room* getNextRoom();
    Room* getPrevRoom();
    int getLevel();
};

#endif // ROOM_H

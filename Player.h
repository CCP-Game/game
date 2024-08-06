#ifndef PLAYER_H
#define PLAYER_H
#include "Room.h"
#include <vector>
class Player{
    public:
    int getHealth();
    char getSkin();
    Point getPos();
    Room getCurrentRoom();

    private:
    int health;
    Point currentLocation;
    Room currentRoom;
    char skin;
    std::vector<int> colour; 
};

#endif
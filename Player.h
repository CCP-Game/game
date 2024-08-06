#ifndef PLAYER_H
#define PLAYER_H
#include "Room.h"
#include <vector>
class Player{
    public:

    Player(char skin, int colour);
    Player();
    int getHealth();
    char getSkin();
    Point getPos();
    Room getCurrentRoom();

    private:
    
    int health;
    Point currentLocation;
    Room currentRoom;
    char skin;
    //to be changed
    
    int colour;

};

#endif
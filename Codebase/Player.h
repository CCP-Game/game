#ifndef PLAYER_H
#define PLAYER_H
#include "Room.h"
#include "Point.h"
#include <vector>

class Player{
    public:

    Player(char skin, int colour);
    Player();
    int getHealth();
    char getSkin();
    Point getPos();
    Room getCurrentRoom();

    const Point &getPos() const;

    void setPosition(int x, int y);

private:
    
    int health;
    Point currentLocation;
    Room currentRoom;
    char skin;
    //to be changed
    
    int colour;

};

#endif
#ifndef PLAYER_H
#define PLAYER_H
#include "Room.h"
#include "Pos.h"
#include <vector>

class Player{
    public:

    Player(char skin, int colour);
    Player();
    int getHealth();
    char getSkin();
    // Pos getPos();
    Room getCurrentRoom();
    const Pos& getPos() const;
    void setPosition(int x, int y);

private:
    
    int health;
    Pos currentLocation;
    Room currentRoom;
    char skin;
    //to be changed
    
    int colour;

};

#endif
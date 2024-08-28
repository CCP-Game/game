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
    void setHealth(int health);
    static void unittest();

private:
    
    int health = 100;
    Pos currentLocation;
    Room currentRoom;
    char skin;
    //to be changed
    
    int colour;

};

#endif
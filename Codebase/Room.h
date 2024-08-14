#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include "Enemy.h"

// height and width of the room
#define WIDTH 22
#define HEIGHT 12

class Room
{
private:
    int id;
    int depth;
    char **grid;
    int colour;
    Pos nextDoorPos;
    Pos prevDoorPos;
    Room *nextRoom;
    Room *prevRoom;
    std::vector<Enemy> enemies;

public:
    Room();
    Room(int id, int depth, int width, int height);
    ~Room();
    // For the final room.
    char **display();
    Room *getNextRoom();
    Room *getPrevRoom();
    void setNextRoom(Room *nextRoom);
    void setPrevRoom(Room *prevRoom);
    int getLevel();
    void printRoom();
    char getCharAt(int x, int y) const;
    void setCharAt(int x, int y, char c);
    void setColour(int colour);
    int getColour();
};

#endif

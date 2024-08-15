#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include "Enemy.h"

// height and width of the room
#define WIDTH 30
#define HEIGHT 12

class Room
{
private:
    int id;
    int depth;
    char **grid;
    int width;
    int height;
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
    Room(const Room& other); // Copy constructor
    Room& operator=(const Room& other); // Assignment operator
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

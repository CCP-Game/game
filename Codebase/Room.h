#ifndef ROOM_H
#define ROOM_H
#include <unordered_map>
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
    Pos playerPos;
    std::vector<Enemy> enemies;
    std::vector<Pos> doorPos;
    std::vector<Room*> doorRooms;
    //std::unordered_map<Pos,Room,Pos::HashFunction> doorMap;

public:
    Room();
    ~Room();
    Room(int id,int depth, int width, int height);
    Room(const Room& other); // Copy constructor
    Room& operator=(const Room& other); // Assignment operator
    void initializeRoom(int NUM_COINS, char type);
    char **getDisplay();
    int getLevel();
    void updatePlayerPos(int x, int y);
    void setDoor(Pos dPos, Room* room);
    Room *getRoom(int x, int y) const;
    char getCharAt(int x, int y) const;
    void setCharAt(int x, int y, char c);
    int getID();
    bool validMove(int newX, int newY);
    bool isDoorMove(int newX, int newY);

 
};

#endif

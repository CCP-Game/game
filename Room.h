#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include "Enemy.h"
class Room{
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

    private:
    //unsure whether we need an ID kept anyway.
    int id;
    int depth;
    char **grid;
    //Ignore these warnings. The Point class will be included in the Cavern class.
    Point nextDoorPos;
    Point prevDoorPos;
    Room *nextRoom;
    Room *prevRoom;
    std::vector<Enemy> enemies;
};

#endif



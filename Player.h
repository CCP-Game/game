#ifndef PLAYER_H
#define PLAYER_H

#include "Point.h"

class Player {
public:
    int health;
    Point currentLocation;
    char display;

    int getHealth();
    Point getPos();
    void getDisplay();
};

#endif // PLAYER_H

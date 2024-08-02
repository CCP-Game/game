#ifndef ENEMY_H
#define ENEMY_H

#include "Point.h"

class Enemy {
public:
    Point position;
    char display;
    int difficulty;
    int health;

    Point getPos();
    int getHealth();
    void getDisplay();
    int getDifficulty();
};

#endif // ENEMY_H

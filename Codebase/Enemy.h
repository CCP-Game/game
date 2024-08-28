#ifndef ENEMY_H
#define ENEMY_H

#include "Pos.h"

class Enemy {
private:
    Pos Position;
    char skin;
    int health;
    int difficulty;

public:
    // Constructors
    static void unittest();
    Enemy(Pos pos, char skin, int difficulty);
    Enemy(char skin, int health);
    
    // Getters
    int getHealth();
    Pos getPos();
    int getX();
    int getY();
    char getSkin();
    int getDifficulty();

    // Setters
    void setHealth(int health);
    void setPos(Pos pos);
    void setX(int x);
    void setY(int y);
    void setSkin(char skin);
    void setDifficulty(int difficulty);

    static void unittest();
};

#endif // ENEMY_H

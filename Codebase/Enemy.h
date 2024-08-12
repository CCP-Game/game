#ifndef ENEMY_H
#define ENEMY_H

class Enemy{
    public:
    
    int getHealth();
    char** getAttackScreen();
    Pos getPos();
    int getDifficulty();
    
    private:

    Pos Position;
    char skin;
    int difficulty;
    int health;
    //In need of a way for storing/accessing questions
};
#endif
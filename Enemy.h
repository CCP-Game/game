#ifndef ENEMY_H
#define ENEMY_H

class Enemy{
    public:
    
    int getHealth();
    char** getAttackScreen();
    Point getPos();
    int getDifficulty();
    
    private:

    Point position;
    char skin;
    int difficulty;
    int health;
    //In need of a way for storing/accessing questions
};
#endif
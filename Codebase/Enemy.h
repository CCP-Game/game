#ifndef ENEMY_H
#define ENEMY_H

class Enemy{
    public:
    
    Enemy(Pos pos, char skin, int difficulty);

    Enemy(char skin, int difficulty);

    // getters
    int getHealth();
    char** getAttackScreen();
    Pos getPos();
    int getX();
    int getY();
    char getSkin();
    int getDifficulty();

    // setters
    void setHealth(int health);
    void setPos(Pos pos);
    void setX(int x);
    void setY(int y);
    void setSkin(char skin);
    void setDifficulty(int difficulty);

    
    private:
    Pos Position;
    char skin;
    int difficulty;
    int health;
};
#endif
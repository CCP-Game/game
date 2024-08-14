#ifndef Pos_H
#define Pos_H
class Pos{
    public:
    Pos(int x,int y);
    int getX() const;
    int getY() const;
    Pos getPos();
    Pos();
    void setXY(int x, int y);
    void setX(int x);
    void setY(int y);
    private:
    int x;
    int y;
};



#endif 
#ifndef POINT_H
#define POINT_H
class Point{
    public:
    Point(int x,int y);
    Point();
    int getX();
    int getY();
    void setXY(int x, int y);
    void setX(int x);
    void setY(int y);
    private:
    int x;
    int y;
};



#endif 
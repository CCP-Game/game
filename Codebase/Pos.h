#ifndef Pos_H
#define Pos_H
class Pos
{
public:
    static void unittest();
    Pos(int x, int y);
    Pos(int x, int y, double distance);
    double getDistance() const;
    int getX() const;
    int getY() const;
    Pos* getParent();
    Pos getPos();
    Pos();
    void setXY(int x, int y);
    void setX(int x);
    void setY(int y);
    void setDistance(double dist);
    void setParent(Pos* parent);
private:
    int x;
    int y;
    double distance;
    Pos* parent;
};
#endif
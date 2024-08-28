#ifndef Pos_H
#define Pos_H

/*!
    @file
    @brief Class to represent the position of another object.
    @authors CCP
    @copyright CCP
*/
class Pos
{
public:
    static void unittest();
    Pos(int x, int y);
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
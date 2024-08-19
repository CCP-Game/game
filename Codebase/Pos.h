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

      // Equality operator
    bool operator==(const Pos& other) const {
        return this->getX() == other.getX() && this->getY() == other.getY();
    }

    // Hash function (see step 2)
    struct HashFunction {
        std::size_t operator()(const Pos& p) const {
            // Compute individual hash values for x and y and combine them
            std::size_t h1 = std::hash<int>{}(p.getX());
            std::size_t h2 = std::hash<int>{}(p.getY());
            return h1 ^ (h2 << 1); // or use boost::hash_combine
        }
    };

    private:
    int x;
    int y;
};





#endif 
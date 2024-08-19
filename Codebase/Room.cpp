#include "Room.h"
#include "Pos.h"
#include <iostream>

/**
 * Room (Default Constructor)
 * - Simple default constructor initalises values to 0.
 */
Room::Room() : Room(0, 0, WIDTH, HEIGHT)
{
}
/**
 * ~Room
 * Simple deconstructor for Room. Simply deletes the grid.
 */
// Destructor
Room::~Room()
{
    // Free allocated memory for grid
    for (int i = 0; i < height; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;
}
/**
 * 
 */
Room::Room(int id, int depth, int width, int height)
    : id(id), depth(depth), width(width), height(height)
{
    // Initialize grid
    grid = new char *[height];
    for (int i = 0; i < height; ++i)
    {
        grid[i] = new char[width];
        for (int j = 0; j < width; ++j)
        {
            grid[i][j] = ' ';
        }
    }
    // Initialize Posers
    playerPos = Pos(0,0);
}
/**
 * 
 * 
 */
Room::Room(const Room &other)
    : id(other.id), depth(other.depth), width(other.width), height(other.height)
{
    grid = new char *[height];
    for (int i = 0; i < height; ++i)
    {
        grid[i] = new char[width];
        for (int j = 0; j < width; ++j)
        {
            grid[i][j] = other.grid[i][j];
        }
    }

    // Copy other member
    playerPos = Pos(0,0);
}
/**
 * Room::operator= 
 * This method overrides the operator =, copying all contents of the "other" room into this one.
 * @param - Takes the address of the Room we want to copy contents from
 * @return
 */
Room& Room::operator=(const Room& other) {
    if (this != &other) {
        // Delete old grid
        for (int i = 0; i < height; ++i) {
            delete[] grid[i];
        }
        delete[] grid;

        // Copy new data
        id = other.id;
        depth = other.depth;
        width = other.width;
        height = other.height;

        grid = new char*[height];
        for (int i = 0; i < height; ++i) {
            grid[i] = new char[width];
            for (int j = 0; j < width; ++j) {
                grid[i][j] = other.grid[i][j];
            }
        }
        // Copy other members
    }
    return *this;
}
/**
 * initalizeRoom
 * Method initalizes a Room. Including the walls, doors and a sprinkling of coins
 * @param NUM_COINS - this is the number of coins you want in this room. 
 */
void Room::initializeRoom(int NUM_COINS)
{
    // Create walls
    for (int x = 0; x < WIDTH; x++)
    {
        setCharAt(x, 0, '#');
        setCharAt(x, HEIGHT - 1, '#');
    }
    for (int y = 0; y < HEIGHT; y++)
    {
        setCharAt(0, y, '#');
        setCharAt(WIDTH - 1, y, '#');
    }

    // Scatter coi
    for (int i = 0; i < NUM_COINS; i++)
    {
        int coinX, coinY;
        do
        {
            coinX = rand() % (WIDTH - 2) + 1;
            coinY = rand() % (HEIGHT - 2) + 1;
        } while (getCharAt(coinX, coinY) != ' ');
        setCharAt(coinX, coinY, 'C');
    }

}
/**
 * updatePlayerPos
 * This method updates the Rooms view of the player position
 * @param x - the x coord
 * @param y - the y coord
 */
void Room::updatePlayerPos(int x, int y){
    playerPos.setXY(x,y);
}
/**
 * validMove
 * This method checks whether a move is valid or not within this room.
 * @param newx - x -coord
 * @param newy - y - coord
 * @return a true or false whether this move will be registered.
 */
bool Room::validMove(int newx, int newy){
    if(this->getCharAt(newx,newy) !='#'){
        return true;
    }
    return false;
}
/**
 * 
 */
bool Room::isDoorMove(int newx, int newy){
    if(this->getCharAt(newx,newy)=='D'){
        return true;
    }
    return false;
}
/**
 * 
 */
void Room::setDoor(Pos dPos, Room &room){
    this->setCharAt(dPos.getX(),dPos.getY(),'D');
    //Inserting this into our map.
    this->doorMap[dPos]= room;
}

Room& Room::getRoom(int x, int y){
       return this->doorMap.at(Pos(x,y));
}
/**
 * getDisplay
 * This method returns the current display for a room. Whether it's the room's grid or in combat with an enemy.
 * @return - A 2D Char array, dictating the stuff to display.
 */
char** Room::getDisplay()
{
    return grid;
}

int Room::getLevel()
{
    return depth;
}

char Room::getCharAt(int x, int y) const
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        return grid[y][x];
    }
    return ' ';
}

void Room::setCharAt(int x, int y, char c)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        grid[y][x] = c;
    }
}

int Room::getID(){
    return this->id;
}

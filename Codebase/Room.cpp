#include "Room.h"
#include "Pos.h"
#include <iostream>
#include <string>

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
 * initializeRoom
 * Method initializes a Room, including the walls, doors, and a sprinkling of coins.
 * @param NUM_COINS - this is the number of coins you want in this room.
 * @param type - this is the type of room you want to create.
 * 'b' = Big Room
 * 'v' = Vertical Hallway
 * 'h' = Horizontal Hallway
 */
void Room::initializeRoom(int NUM_COINS, char type)
{
    // Clear the room first
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            setCharAt(x, y, ' ');
        }
    }

    int minX, maxX, minY, maxY;

    // Create walls
    if (type == 'b') // Big Room
    {
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
        minX = 1;
        maxX = WIDTH - 2;
        minY = 1;
        maxY = HEIGHT - 2;
    }
    else if (type == 'h') // Horizontal Hallway
    {
        int hallwayHeight = 5; // Set the height of the hallway
        int centerY = HEIGHT / 2; // Find the center of the room vertically
        int startY = centerY - hallwayHeight / 2; // Start 2 units above the center

        // Create top and bottom walls
        for (int x = 0; x < WIDTH; x++)
        {
            setCharAt(x, startY, '#');
            setCharAt(x, startY + hallwayHeight - 1, '#');
        }

        // Create end walls
        for (int y = startY + 1; y < startY + hallwayHeight - 1; y++)
        {
            setCharAt(0, y, '#');
            setCharAt(WIDTH - 1, y, '#');
        }
        
        minX = 1;
        maxX = WIDTH - 2;
        minY = startY + 1;
        maxY = startY + hallwayHeight - 2;
    }
    else if (type == 'v') // Vertical Hallway
    {
        int hallwayWidth = 9; // Set the width of the hallway
        int centerX = WIDTH / 2; // Find the center of the room horizontally
        int startX = centerX - hallwayWidth / 2; // Start 2 units left of the center

        // Create left and right walls
        for (int y = 0; y < HEIGHT; y++)
        {
            setCharAt(startX, y, '#');
            setCharAt(startX + hallwayWidth - 1, y, '#');
        }

        // Create end walls
        for (int x = startX + 1; x < startX + hallwayWidth - 1; x++)
        {
            setCharAt(x, 0, '#');
            setCharAt(x, HEIGHT - 1, '#');
        }

        minX = startX + 1;
        maxX = startX + hallwayWidth - 2;
        minY = 1;
        maxY = HEIGHT - 2;
    }
    else
    {
        // Handle invalid room type if necessary
        std::cerr << "Invalid room type!" << std::endl;
        return;
    }

    // Scatter coins
    for (int i = 0; i < NUM_COINS; i++)
    {
        int coinX, coinY;
        do
        {
            coinX = rand() % (maxX - minX + 1) + minX;
            coinY = rand() % (maxY - minY + 1) + minY;
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
void Room::setDoor(Pos dPos, Room* room){
    this->setCharAt(dPos.getX(),dPos.getY(),'D');
    //Inserting this into our arrays
    this->doorPos.push_back(dPos);
    this->doorRooms.push_back(room);
}

void Room::setEnemy(Pos p, Enemy e){
    this->setCharAt(p.getX(),p.getY(),e.getSkin());
    e.setPos(p);
    this->enemies.push_back(e);

    // Set the enemy in the grid
    
}

Room* Room::getRoom(int x, int y) const {
        for (size_t i = 0; i < doorPos.size(); ++i) {
            if (doorPos[i].getX() == x && doorPos[i].getY() == y) {
                return doorRooms[i];
            }
        }
        return nullptr; // Return nullptr if not found
    }
/**
 * 
 */

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

// get enemies
std::vector<Enemy> Room::getEnemies(){
    return this->enemies;
}

// enemiesToString
std::string Room::enemiesToString(){
    std::string result = "";
    for (size_t i = 0; i < enemies.size(); ++i) {
        result += "Enemy " + std::to_string(i) + ": " + "Skin: " + enemies[i].getSkin() + " Pos: " + std::to_string(enemies[i].getX()) + "," + std::to_string(enemies[i].getY()) + "\n";
    }
    return result;
}
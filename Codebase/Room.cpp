#include "Room.h"
#include "Pos.h"
#include <iostream>

/**
 * 
 * 
 */
Room::Room() : Room(0, 0, WIDTH, HEIGHT)
{
}
/**
 * 
 * 
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
 * 
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
    nextRoom = nullptr;
    prevRoom = nullptr;
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

    // Copy other members
    nextRoom = other.nextRoom;
    prevRoom = other.prevRoom;
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
        nextRoom = other.nextRoom;
        prevRoom = other.prevRoom;
    }
    return *this;
}
/**
 * initalizeRoom
 * Method w
 * 
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
    // Place doors
    setCharAt(WIDTH / 2, 0, 'D');
    setCharAt(WIDTH / 2, HEIGHT - 1, 'D');
    setCharAt(0, HEIGHT / 2, 'D');
    setCharAt(WIDTH - 1, HEIGHT / 2, 'D');
}

char **Room::GetDisplay()
{
    return grid;
}

Room* Room::getNextRoom()
{
    return nextRoom;
}

Room* Room::getPrevRoom()
{
    return prevRoom;
}

void Room::setNextRoom(Room *next)
{
    nextRoom = next;
}

void Room::setPrevRoom(Room *prev)
{
    prevRoom = prev;
}

int Room::getLevel()
{
    return depth;
}

// Method to print the entire room
void Room::printRoom()
{
    int height = sizeof(grid) / sizeof(grid[0]);
    int width = sizeof(grid[0]) / sizeof(grid[0][0]);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
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

// Getter for Colour
// int Room::getColour() {
//     return colour;
// }

// // Setter for Colour
// void Room::setColour(int colour) {
//     this->colour = colour;
// }
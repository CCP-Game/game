#include "Room.h"
#include "Pos.h"
#include <iostream>

// Default constructor
Room::Room() : Room(0, 0, WIDTH, HEIGHT)
{
}

// Constructor
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

char **Room::display()
{
    return grid;
}

Room *Room::getNextRoom()
{
    return nextRoom;
}

Room *Room::getPrevRoom()
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
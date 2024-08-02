#include "Room.h"
#include "Player.h"
#include "Point.h"
#include "Enemy.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

#define WIDTH 22
#define HEIGHT 12
#define NUM_COINS 10
#define NUM_DOORS 2

char grid[HEIGHT][WIDTH];
char previousGrid[HEIGHT][WIDTH];
int score = 0;
char lastDirection;

Player player;
Room currentRoom;
Room previousRoom;

void copyGrid(char dest[HEIGHT][WIDTH], char src[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            dest[y][x] = src[y][x];
        }
    }
}

void placeDoors() {
    int doorsPlaced = 0;
    while (doorsPlaced < NUM_DOORS) {
        int wall = rand() % 4; // 0 = top, 1 = bottom, 2 = left, 3 = right
        int pos;

        switch (wall) {
            case 0: // top wall
                pos = rand() % (WIDTH - 2) + 1; // Avoid corners
                if (grid[1][pos] != 'D') {
                    grid[0][pos] = 'D';
                    doorsPlaced++;
                }
                break;
            case 1: // bottom wall
                pos = rand() % (WIDTH - 2) + 1;
                if (grid[HEIGHT-2][pos] != 'D') {
                    grid[HEIGHT-1][pos] = 'D';
                    doorsPlaced++;
                }
                break;
            case 2: // left wall
                pos = rand() % (HEIGHT - 2) + 1;
                if (grid[pos][1] != 'D') {
                    grid[pos][0] = 'D';
                    doorsPlaced++;
                }
                break;
            case 3: // right wall
                pos = rand() % (HEIGHT - 2) + 1;
                if (grid[pos][WIDTH-2] != 'D') {
                    grid[pos][WIDTH-1] = 'D';
                    doorsPlaced++;
                }
                break;
        }
    }
}

void displayGrid() {
    system("cls");  // Clear the console (Windows-specific, use "clear" for Unix-based systems)
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            std::cout << grid[y][x];
        }
        std::cout << "\n";
    }
    std::cout << "Move (WASD) or Q to quit: ";
}

void initializeGrid(char entryDirection) {
    // Save the current grid and player position to allow returning
    copyGrid(previousGrid, grid);
    previousRoom = currentRoom;

    // Fill the grid with empty spaces
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = ' ';
        }
    }

    // Create walls around the edges
    for (int x = 0; x < WIDTH; x++) {
        grid[0][x] = '#';
        grid[HEIGHT-1][x] = '#';
    }
    for (int y = 0; y < HEIGHT; y++) {
        grid[y][0] = '#';
        grid[y][WIDTH-1] = '#';
    }

    // Scatter coins randomly
    for (int i = 0; i < NUM_COINS; i++) {
        int coinX, coinY;
        do {
            coinX = rand() % WIDTH;
            coinY = rand() % HEIGHT;
        } while (grid[coinY][coinX] != ' '); // Ensure the coin is placed in an empty spot
        grid[coinY][coinX] = 'C';
    }

    // Place doors in the walls
    placeDoors();

    // Position player based on lastDirection
    switch (entryDirection) {
        case 'w':
            player.setPosition(WIDTH / 2, HEIGHT - 2);
            break;
        case 's':
            player.setPosition(WIDTH / 2, 1);
            break;
        case 'a':
            player.setPosition(WIDTH - 2, HEIGHT / 2);
            break;
        case 'd':
            player.setPosition(1, HEIGHT / 2);
            break;
        default:
            player.setPosition(WIDTH / 2, HEIGHT / 2);
            break;
    }

    Point playerPos = player.getPos();
    grid[playerPos.getY()][playerPos.getX()] = 'P';
    displayGrid();
}

// Method to move cursor to a new position on the screen
void setCursorPosition(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void updatePlayer(int oldX, int oldY, int newX, int newY) {
    setCursorPosition(oldX, oldY);
    std::cout << ' ';
    setCursorPosition(newX, newY);
    std::cout << 'P';
    // Hide the console cursor
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void movePlayer(char direction) {
    Point currentPos = player.getPos();
    int newX = currentPos.getX();
    int newY = currentPos.getY();

    switch (direction) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
    }

    // Check if the new position is not a wall before moving
    if (grid[newY][newX] != '#') {
        if (grid[newY][newX] == 'C') {
            score++; // Collect coin and increment score
        } else if (grid[newY][newX] == 'D') { // If a door is reached, regenerate the map
            lastDirection = direction;
            initializeGrid(direction); // Regenerate the map if player moves through a door
        } else if (grid[newY][newX] == 'P') {
            // Return to the previous grid and position
            copyGrid(grid, previousGrid);
            player.setPosition(previousRoom.ptrToDisplay.getX(), previousRoom.ptrToDisplay.getY());
        }

        grid[currentPos.getY()][currentPos.getX()] = ' ';
        player.setPosition(newX, newY);
        Point newPos = player.getPos();
        grid[newPos.getY()][newPos.getX()] = 'P';

        updatePlayer(currentPos.getX(), currentPos.getY(), newPos.getX(), newPos.getY());
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    char input;
    initializeGrid(0); // Initial grid setup

    while (true) {
        input = _getch();  // Get a single character input without pressing Enter
        if (input == 'q' || input == 'Q') break;
        movePlayer(input);
        setCursorPosition(0, 14);
    }

    return 0;
}

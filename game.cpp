#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iostream>
#include <windows.h>

#define WIDTH 22
#define HEIGHT 12
#define NUM_COINS 10
#define NUM_DOORS 2

char grid[HEIGHT][WIDTH];
char previousGrid[HEIGHT][WIDTH];
int playerX, playerY;
int previousPlayerX, previousPlayerY;
int score = 0;
char lastDirection;

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
    //if(firstRun){
        system("cls");  // Clear the console (Windows-specific, use "clear" for Unix-based systems)
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                std::cout << grid[y][x];
            }
            std::cout << "\n";
        }
    // }else{

    // }
    //std::cout << "Score: " << score << "\n";
    std::cout << "Move (WASD) or Q to quit: ";
}

void initializeGrid(char entryDirection) {
    // Save the current grid and player position to allow returning
    copyGrid(previousGrid, grid);
    previousPlayerX = playerX;
    previousPlayerY = playerY;

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
            playerX = WIDTH / 2;
            playerY = HEIGHT - 2;
            break;
        case 's':
            playerX = WIDTH / 2;
            playerY = 1;
            break;
        case 'a':
            playerX = WIDTH - 2;
            playerY = HEIGHT / 2;
            break;
        case 'd':
            playerX = 1;
            playerY = HEIGHT / 2;
            break;
        default:
            playerX = WIDTH / 2;
            playerY = HEIGHT / 2;
            break;
    }

    grid[playerY][playerX] = 'P';
    displayGrid(); 
}
//Method to move cursor to a new position on the screen
//https://stackoverflow.com/questions/8285568/c-setconsolecursorposition-getstdhandlestd-output-handle-c-2-arguments
void setCursorPosition(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void updatePlayer(int oldX, int oldY, int newX, int newY){
    
        setCursorPosition(oldX, oldY);
        std::cout << ' ';
        setCursorPosition(newX, newY);
        std::cout << 'P';
        //https://learn.microsoft.com/en-us/windows/console/setconsolecursorinfo
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(consoleHandle, &cursorInfo);
        cursorInfo.bVisible = false; // Set the cursor visibility to false
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
        // setCursorPosition(oldX, oldY);
        // std::cout << ' ';
        //std::cout << "Score: " << score << "\n";

}


void movePlayer(char direction) {
    int newX = playerX;
    int newY = playerY;
    int tempX = playerX;
    int tempY = playerY;

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
            playerX = previousPlayerX;
            playerY = previousPlayerY;
        }

        
        grid[playerY][playerX] = ' ';
        playerX = newX;
        playerY = newY;
        grid[playerY][playerX] = 'P';


        updatePlayer(tempX, tempY, newX, newY);
    }
    //displayGrid(false);
    //updatePlayer(tempX, tempY, newX, newY);
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    char input;
    initializeGrid(0); // Initial grid setup

    while (true) {
        //displayGrid(false);
        //std::cout << "Move (WASD) or Q to quit: ";
        input = _getch();  // Get a single character input without pressing Enter
        if (input == 'q' || input == 'Q') break;
        movePlayer(input);
        setCursorPosition(0, 14); //13 seems to break this for now
        std::cout << "Score: " << score << "\n";
        //displayGrid(false);
    }

    return 0;
}

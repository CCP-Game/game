#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#pragma comment(lib, "User32.lib")
#include "Pos.h"
#include "Pos.cpp"
#include "Room.h"
#include "Room.cpp"
#include "Player.h"
#include "Player.cpp"
// #include "Enemy.h"
// #include "Enemy.cpp"

#define WIDTH 30
#define HEIGHT 12

void setCursorPosition(int x, int y)
{
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void resetConsoleAttributes()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default color
}

//
void printToConsole(char** display)
{
    system("cls");            // Clear the console
    resetConsoleAttributes(); // Reset to default console attributes
    setCursorPosition(0, 0);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            std::cout << display[y][x];
        }
        std::cout << '\n';
    }
}

bool isKeyPressed(int key)
{
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

void updatePlayerPosition(Room &room, Player &player, int newX, int newY)
{
    const Pos &currentPos = player.getPos();

    // Clear the old player position in the room matrix
    room.setCharAt(currentPos.getX(), currentPos.getY(), ' ');

    // Clear the old player position on the screen
    setCursorPosition(currentPos.getX(), currentPos.getY());
    std::cout << ' ';

    // Update the player's position
    player.setPosition(newX, newY);

    // Set the new player position in the room matrix
    room.setCharAt(newX, newY, player.getSkin());

    // Draw the new player position on the screen
    setCursorPosition(newX, newY);
    std::cout << player.getSkin();
}

int main()
{
    srand(static_cast<unsigned>(time(0)));
    Room currentRoom(1, 1, WIDTH, HEIGHT);
    currentRoom.initializeRoom(10);


    Player player('P', 7);

    player.setPosition(WIDTH / 2, HEIGHT / 2);
    currentRoom.setCharAt(player.getPos().getX(), player.getPos().getY(), player.getSkin());
    printToConsole(currentRoom.getDisplay());
    hideCursor();
    int score = 0;
    bool gameRunning = true;
    DWORD lastMoveTime = GetTickCount();
    const DWORD moveDelay = 100; // Adjust this value to change movement speed (lower = faster)
    int newX =0;
    int newY =0;
    while (gameRunning)
    {
        DWORD currentTime = GetTickCount();
        if (currentTime - lastMoveTime >= moveDelay)
        {
            const Pos &currentPos = player.getPos();
            newX = currentPos.getX();
            newY = currentPos.getY();

            if (isKeyPressed('W')) newY--;
            if (isKeyPressed('S')) newY++;
            if (isKeyPressed('A')) newX--;
            if (isKeyPressed('D')) newX++;

            char nextChar = currentRoom.getCharAt(newX, newY);
            if (nextChar != '#'){
                if (nextChar == 'C')
                {
                    score++;
                }
                else if (nextChar == 'D')
                {
                    // Generate a new room
                    currentRoom = Room(currentRoom.getLevel() + 1, currentRoom.getLevel() + 1, WIDTH, HEIGHT);
                    currentRoom.initializeRoom(10);

                    // Place player on the opposite side of the new room
                    if (newX == 0)
                        newX = WIDTH - 2;
                    else if (newX == WIDTH - 1)
                        newX = 1;
                    else if (newY == 0)
                        newY = HEIGHT - 2;
                    else if (newY == HEIGHT - 1)
                        newY = 1;

                    // Update player position in the new room
                    player.setPosition(newX, newY);
                    currentRoom.setCharAt(newX, newY, player.getSkin());

                    printToConsole(currentRoom.getDisplay());
                }
                updatePlayerPosition(currentRoom, player, newX, newY);
            }
            lastMoveTime = currentTime;
        }
        // Display score and check for quit
        setCursorPosition(0, HEIGHT + 1);
        std::cout << "Score: " << score << " | Press Q to quit";

        if (isKeyPressed('Q'))
        {
            gameRunning = false;
        }

        Sleep(10); // Small delay to prevent excessive CPU usage
    }

    return 0;
}
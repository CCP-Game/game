#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "Room.h"
#include "Player.h"
#include "Point.h"

#define WIDTH 22
#define HEIGHT 12
#define NUM_COINS 10

void setCursorPosition(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void initializeRoom(Room& room) {
    // Create walls
    for (int x = 0; x < WIDTH; x++) {
        room.setCharAt(x, 0, '#');
        room.setCharAt(x, HEIGHT - 1, '#');
    }
    for (int y = 0; y < HEIGHT; y++) {
        room.setCharAt(0, y, '#');
        room.setCharAt(WIDTH - 1, y, '#');
    }

    // Scatter coins
    for (int i = 0; i < NUM_COINS; i++) {
        int coinX, coinY;
        do {
            coinX = rand() % (WIDTH - 2) + 1;
            coinY = rand() % (HEIGHT - 2) + 1;
        } while (room.getCharAt(coinX, coinY) != ' ');
        room.setCharAt(coinX, coinY, 'C');
    }

    // Place doors
    room.setCharAt(WIDTH / 2, 0, 'D');
    room.setCharAt(WIDTH / 2, HEIGHT - 1, 'D');
    room.setCharAt(0, HEIGHT / 2, 'D');
    room.setCharAt(WIDTH - 1, HEIGHT / 2, 'D');
}


void displayRoom(const Room& room) {
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            std::cout << room.getCharAt(x, y);
        }
        std::cout << '\n';
    }
}

void updatePlayerPosition(Room& room, Player& player, int newX, int newY) {
    const Point& currentPos = player.getPos();
    room.setCharAt(currentPos.getX(), currentPos.getY(), ' ');
    player.setPosition(newX, newY);
    room.setCharAt(newX, newY, player.getSkin());

    setCursorPosition(currentPos.getX(), currentPos.getY());
    std::cout << ' ';
    setCursorPosition(newX, newY);
    std::cout << player.getSkin();
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    Room currentRoom(1, 1, WIDTH, HEIGHT);
    initializeRoom(currentRoom);
    
    Player player('P', 7);
    player.setPosition(WIDTH / 2, HEIGHT / 2);
    currentRoom.setCharAt(player.getPos().getX(), player.getPos().getY(), player.getSkin());
    displayRoom(currentRoom);
    hideCursor();

    int score = 0;
    char input;
    while (true) {
        setCursorPosition(0, HEIGHT + 1);
        std::cout << "Score: " << score << " | Move (WASD) or Q to quit: ";
        
        input = _getch();
        if (input == 'q' || input == 'Q') break;

        const Point& currentPos = player.getPos();
        int newX = currentPos.getX();
        int newY = currentPos.getY();

        switch (input) {
            case 'w': newY--; break;
            case 's': newY++; break;
            case 'a': newX--; break;
            case 'd': newX++; break;
        }

        char nextChar = currentRoom.getCharAt(newX, newY);
        if (nextChar != '#') {
            if (nextChar == 'C') {
                score++;
            } else if (nextChar == 'D') {
                // Generate a new room
                currentRoom = Room(currentRoom.getLevel() + 1, currentRoom.getLevel() + 1, WIDTH, HEIGHT);
                initializeRoom(currentRoom);
                
                // Place player on the opposite side of the new room
                if (newX == 0) newX = WIDTH - 2;
                else if (newX == WIDTH - 1) newX = 1;
                else if (newY == 0) newY = HEIGHT - 2;
                else if (newY == HEIGHT - 1) newY = 1;
                
                displayRoom(currentRoom);
            }
            updatePlayerPosition(currentRoom, player, newX, newY);
        }
    }

    return 0;
}
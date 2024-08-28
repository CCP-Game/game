#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#pragma comment(lib, "User32.lib")
#include <conio.h> // For _kbhit() and _getch()
#include "Pos.h"
#include "Room.h"
#include "Player.h"
#include "Enemy.h"
#include "Pos.cpp"
#include "Room.cpp"
#include "Player.cpp"
#include "Enemy.cpp"

#define WIDTH 25
#define HEIGHT 13
#define worldMap =
/**
 * setCursorPosition
 * Method sets the cursors position.
 */
void setCursorPosition(int x, int y)
{
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/**
 * hideCursor
 * Method hides the cursor from the user (stops the annoying flickering.)
 */
void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
/**
 * resetConsoleAttributes
 */
void resetConsoleAttributes()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default color
}
/**
 * isKeyPressed
 * method checks whether a given key was pressed.
 * @param - the key to be checked
 * @return - Returns true if the key pressed == key param.
 */
bool isKeyPressed(int key)
{
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}
/**
 * updatePlayerPosition
 * Method takes the current room, player and new x,y coords updating the players position in Room.
 * @param &room - the current room of Room class
 * @param &player- the current player of Player class
 * @param newX - this is an integer representing the new movement of our player along x-axis
 * @param newy - this is an integer representing the new movement of our player along y-axis
 */
void updatePlayerPosition(Room *room, Player &player, int newX, int newY)
{
    const Pos &currentPos = player.getPos();
    // Clear the old player position in the room matrix
    room->setCharAt(currentPos.getX(), currentPos.getY(), ' ');
    // Clear the old player position on the screen
    setCursorPosition(currentPos.getX(), currentPos.getY());
    std::cout << ' ';
    // Update the player's position
    player.setPosition(newX, newY);
    // Set the new player position in the room matrix
    room->setCharAt(newX, newY, player.getSkin());
    // update Rooms player position
    room->updatePlayerPos(newX, newY);
    // Draw the new player position on the screen
    setCursorPosition(newX, newY);
    std::cout << player.getSkin();
}
/**
 * getDoorsOpposite
 * This method returns the starting position when traversing between two rooms. Getting the alternate door pos
 * With a simple case assuming all rooms have the same dimensions.
 * @param  oldPos - a Pos of the old door
 * @return newPos - the invrese of the new door
 */
Pos getDoorsOpposite(Pos oldPos)
{
    int x = oldPos.getX();
    int y = oldPos.getY();

    if (x == 0)
    {
        // Door on the left edge, return one step inside on the right edge
        return Pos(WIDTH - 2, y);
    }
    else if (y == 0)
    {
        // Door on the top edge, return one step inside on the bottom edge
        return Pos(x, HEIGHT - 2);
    }
    else if (x == WIDTH - 1)
    {
        // Door on the right edge, return one step inside on the left edge
        return Pos(1, y);
    }
    else if (y == HEIGHT - 1)
    {
        // Door on the bottom edge, return one step inside on the top edge
        return Pos(x, 1);
    }
    else
    {
        // For other cases, you might want to handle unexpected conditions
        // For example, returning a default or invalid position
        return Pos(-1, -1); // Indicating an invalid position
    }
}
/**
 * setFGColor
 * This method uses ANSI escape codes to set the output color to console for the foreground.
 * @param int textColor - this is the color we want has to be > 1
 */
void setFGColour(int textColour = 255)
{
    std::cout << "\x1b[38;5;";
    if (textColour != -1)
    {
        std::cout << textColour;
    }

    std::cout << "m";
}
/**
 * setBGColour
 * This method, using ASNI escape codes, sets the Background Colour in the console
 * @param int bgColour
 */
void setBGColour(int textColour = 255)
{
    std::cout << "\x1b[48;5;";
    if (textColour != -1)
    {
        std::cout << textColour;
    }

    std::cout << "m";
}
/**
 * resetColor
 * This method resets the output to it's default Colour
 */
void resetColour()
{
    std::cout << "\033[0m";
}
/**
 * printToConsole
 * - This method takes a 2d char array (a display) printing it to the console
 * @param display - the inputted 2d char array.
 */
/**
 * initalizeTutorialMap
 * Method implements a simple "linked-list-style" 1D map of rooms. Returning the first room.
 * @param roomSize
 * @return the first room in the linked list.
 */

// left = Pos(0, HEIGHT/2)
// right = Pos(WIDTH-1, HEIGHT/2)
// top = Pos(WIDTH/2, 0)
// bottom = Pos(WIDTH/2, HEIGHT-1)

Room *initalizeTutorialMap(int roomLength)
{
    Room *room1 = new Room(1, 1, WIDTH, HEIGHT);
    Room *room2 = new Room(2, 1, WIDTH, HEIGHT);
    Room *room3 = new Room(3, 1, WIDTH, HEIGHT);
    Room *room4 = new Room(4, 1, WIDTH, HEIGHT);
    Room *room5 = new Room(5, 1, WIDTH, HEIGHT);
    Room *room6 = new Room(6, 1, WIDTH, HEIGHT);
    Room *room7 = new Room(7, 1, WIDTH, HEIGHT);
    Room *room8 = new Room(8, 1, WIDTH, HEIGHT);
    Room *room9 = new Room(9, 1, WIDTH, HEIGHT);
    Room *room10 = new Room(10, 1, WIDTH, HEIGHT);
    Room *end = new Room(11, 1, WIDTH, HEIGHT);

    Enemy *e1 = new Enemy('+', 20);
    Enemy *e2 = new Enemy('+', 30);
    Enemy *e3 = new Enemy('+', 50);
    Enemy *e4 = new Enemy('*', 20);
    Enemy *e5 = new Enemy('*', 30);
    Enemy *e6 = new Enemy('*', 50);
    Enemy *e7 = new Enemy('/', 20);
    Enemy *e8 = new Enemy('/', 30);
    Enemy *e9 = new Enemy('/', 50);

    // Initalise the rooms grid
    room1->initializeRoom(5, 'b');
    room2->initializeRoom(5, 'h');
    room3->initializeRoom(5, 'b');
    room4->initializeRoom(5, 'v');
    room5->initializeRoom(5, 'b');
    room6->initializeRoom(5, 'h');
    room7->initializeRoom(5, 'b');
    room8->initializeRoom(5, 'h');
    room9->initializeRoom(5, 'b');
    room10->initializeRoom(5, 'v');
    end->initializeRoom(5, 'b');

    // Add Information to each room.
    room1->setRoomINFO("USE W A S D to move!\nThe \"D\" refers to a Door! ");
    // Set door positions for each room
    room1->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room2); // Right to Room 2
                                                       // Enemy to the side of the room

    room2->setDoor(Pos(0, HEIGHT / 2), room1);         // Left to Room 1
    room2->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room3); // Right to Room 3
    room2->setEnemy(Pos(7, 5), e1);
    room2->setRoomINFO("Run into enemies to fight them!");

    room3->setDoor(Pos(0, HEIGHT / 2), room2);         // Left to Room 2
    room3->setDoor(Pos(WIDTH / 2, 0), room7);          // Top to Room 7
    room3->setDoor(Pos(WIDTH / 2, HEIGHT - 1), room4); // Bottom to Room 4
    room3->setEnemy(Pos(7, HEIGHT / 2), e2);           // Enemy to the side of the room
    room3->setEnemy(Pos(9, HEIGHT / 2), e3); 
    room3->setRoomINFO("Which door to take? So many choices!");

    // room3->setEnemy(Pos(WIDTH / 2, HEIGHT / 2), e1);    // Enemy in the middle of the room

    room4->setDoor(Pos(WIDTH / 2, 0), room3);          // Top to Room 3
    room4->setDoor(Pos(WIDTH / 2, HEIGHT - 1), room5); // Bottom to Room 5
    room4->setEnemy(Pos(WIDTH / 2, HEIGHT / 2), e4);   // Enemy in the middle of the room
    room4->setRoomINFO("Enemies will get harder as you progress!");

    room5->setDoor(Pos(WIDTH / 2, 0), room4);          // Top to Room 4
    room5->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room6); // Right to Room 6
    room5->setEnemy(Pos(WIDTH / 2, HEIGHT / 2), e5);   // Enemy in the middle of the room
    room5->setRoomINFO("You're doing great!");

    room6->setDoor(Pos(0, HEIGHT / 2), room5); // Left to Room 5
    room6->setRoomINFO("Oops, looks like a dead end!");

    room7->setDoor(Pos(WIDTH / 2, HEIGHT - 1), room3); // Bottom to Room 3
    room7->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room8); // Right to Room 8
    room7->setEnemy(Pos(WIDTH / 2, HEIGHT / 2), e6);   // Enemy in the middle of the room
    room7->setRoomINFO("Good choice!");

    room8->setDoor(Pos(0, HEIGHT / 2), room7);         // Left to Room 7
    room8->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room9); // Right to Room 9
    room8->setEnemy(Pos(WIDTH / 2, HEIGHT / 2), e7);   // Enemy in the middle of the room
    room8->setRoomINFO("You're almost there!");

    room9->setDoor(Pos(0, HEIGHT / 2), room8);          // Left to Room 8
    room9->setDoor(Pos(WIDTH / 2, HEIGHT - 1), room10); // Bottom to Room 10
    room9->setEnemy(Pos(WIDTH / 2, 6), e8);    // Enemy in the middle of the room
    room9->setEnemy(Pos(4, HEIGHT / 2), e9);    // Enemy in the middle of the room
    room9->setRoomINFO("LOTS OF ENEMIES!");

    room10->setDoor(Pos(WIDTH / 2, 0), room9); // Top to Room 9
    // Room 10 has a staircase to another room
    room10->setDoor(Pos(WIDTH / 2, HEIGHT - 2), end); // Stairway to new room
    room10->setRoomINFO("Congratulations! You've reached the end of the tutorial!");

    return room1; // Game starts in room 1
}

void printToConsole(char **display)
{
    system("cls");            // Clear the console
    resetConsoleAttributes(); // Reset to default console attributes
    setCursorPosition(0, 0);  // Sets the cursor position..
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            setFGColour(124);

            if (display[y][x] == 'D')
            {
                std::cout << "\033[1m";
                setFGColour(130);
            }
            if (display[y][x] == '#')
            {
                setFGColour(65);
                setBGColour(236);
            }
            if (display[y][x] == 'C')
            {
                setFGColour(226);
            }

            std::cout << display[y][x];
            resetColour();
        }
        std::cout << '\n';
    }
}

boolean touchingEnemy(Room *room, Player player)
{
    Pos playerPos = player.getPos();
    for (size_t i = 0; i < room->getEnemies().size(); i++)
    {
        if (room->getEnemies()[i]->getX() == playerPos.getX() && room->getEnemies()[i]->getY() == playerPos.getY())
        {
            return true;
        }
    }
    return false;
}

void clearInputBuffer()
{
    while (_kbhit())
    {
        _getch(); // Read any characters left in the input buffer
    }
}

int generateMathProblem()
{
    int num1 = rand() % 10 + 1;
    int num2 = rand() % 10 + 1;
    int operation = rand() % 3; // 0 = addition, 1 = subtraction, 2 = multiplication

    switch (operation)
    {
    case 0:
        std::cout << num1 << " + " << num2 << " = ?\n";
        return num1 + num2;
    case 1:
        std::cout << num1 << " - " << num2 << " = ?\n";
        return num1 - num2;
    case 2:
        std::cout << num1 << " * " << num2 << " = ?\n";
        return num1 * num2;
    default:
        return 0;
    }
}

bool fightEnemy(Player &player, Enemy *enemy)
{
    system("cls");
    clearInputBuffer();
    std::cout << "You are in combat with an enemy!\n";

    int enemyHealth = enemy->getHealth();

    while (enemyHealth > 0 && player.getHealth() > 0)
    {
        std::cout << "Player Health: " << player.getHealth() << " | Enemy Health: " << enemyHealth << "\n";
        std::cout << "Enter your answer or type 'run' to attempt escape: ";
        int correctAnswer = generateMathProblem();
        std::string userInput;
        std::cin >> userInput;

        if (userInput == "run")
        {
            if (rand() % 2 == 0) // 50% chance to escape
            {
                std::cout << "You successfully escaped!\n";
                Sleep(2000);
                return true;
            }
            else
            {
                std::cout << "Escape failed! The enemy attacks you for 3 damage.\n";
                player.setHealth(player.getHealth() - 3);
            }
        }
        else
        {
            int userAnswer;
            try
            {
                userAnswer = std::stoi(userInput);
            }
            catch (const std::invalid_argument &)
            {
                std::cout << "Invalid input. The enemy attacks you for 3 damage.\n";
                player.setHealth(player.getHealth() - 3);
                Sleep(2000);
                continue;
            }

            if (userAnswer == correctAnswer)
            {
                std::cout << "Correct! You dealt 10 damage to the enemy!\n";
                enemyHealth -= 10;
            }
            else
            {
                std::cout << "Incorrect! You have taken 5 damage!\n";
                player.setHealth(player.getHealth() - 5);
            }
        }

        Sleep(1500);   // Pause for 2 seconds between rounds
        system("cls"); // Clear the screen for the next round
    }

    if (player.getHealth() <= 0)
    {
        std::cout << "You have been defeated!\n";
        Sleep(2000);
        return false;
    }
    else
    {
        std::cout << "You have defeated the enemy!\n";
        Sleep(2000);
        return true;
    }
}

void updateEnemyPosition(Room *room, Enemy *enemy, int newX, int newY)
{
    const Pos &currentPos = enemy->getPos();
    // Clear the old enemy position in the room matrix
    room->setCharAt(currentPos.getX(), currentPos.getY(), ' ');
    // Clear the old enemy position on the screen
    setCursorPosition(currentPos.getX(), currentPos.getY());
    std::cout << ' ';
    room->removeEnemyAt(currentPos.getX(), currentPos.getY());
    // Update the enemy's position
    enemy->setX(newX);
    enemy->setY(newY);
    // Set the new enemy position in the room matrix
    room->setCharAt(newX, newY, enemy->getSkin());
    room->setEnemyAt(newX, newY, enemy);
    // Draw the new enemy position on the screen
    setCursorPosition(newX, newY);
    std::cout << enemy->getSkin();
}

void moveEnemies(Room *room)
{
    for (auto &enemy : room->getEnemies())
    {
        const Pos &currentPos = enemy->getPos();
        int newX = currentPos.getX();
        int newY = currentPos.getY();

        // Move towards the player
        int playerX = room->getPlayerPos().getX();
        int playerY = room->getPlayerPos().getY();

        // set the direction to move based on the player's position
        if (playerX < newX)
            newX--;
        else if (playerX > newX)
            newX++;
        else if (playerY < newY)
            newY--;
        else if (playerY > newY)
            newY++;

        // Ensure the move is valid
        if (room->validMove(newX, newY))
        {
            updateEnemyPosition(room, enemy, newX, newY);
        }
    }
}

int main()
{
    int score = 0;
    bool gameRunning = true;

    DWORD lastMoveTime = GetTickCount();
    DWORD lastEnemyMoveTime = GetTickCount();

    const DWORD enemyMoveDelay = 500; // Adjust this value to change enemy movement speed (lower = faster)
    const DWORD moveDelay = 100;      // Adjust this value to change movement speed (lower = faster)
    int newX = 0;
    int newY = 0;
    srand(static_cast<unsigned>(time(0)));
    Room *currentRoom = initalizeTutorialMap(1);

    Player player('P', 100); // Increased initial health to 100
    player.setPosition(WIDTH / 2, HEIGHT / 2);
    currentRoom->setCharAt(player.getPos().getX(), player.getPos().getY(), player.getSkin());
    printToConsole(currentRoom->getDisplay());
    hideCursor();

    while (gameRunning)
    {
        DWORD currentTime = GetTickCount();
        if (currentTime - lastMoveTime >= moveDelay)
        {
            const Pos &currentPos = player.getPos();
            newX = currentPos.getX();
            newY = currentPos.getY();

            if (isKeyPressed('W'))
                newY--;
            if (isKeyPressed('S'))
                newY++;
            if (isKeyPressed('A'))
                newX--;
            if (isKeyPressed('D'))
                newX++;

            char nextChar = currentRoom->getCharAt(newX, newY);

            if (currentRoom->validMove(newX, newY))
            {
                if (currentRoom->isDoorMove(newX, newY))
                {
                    currentRoom->removePlayer();
                    Room *tempRoom = currentRoom->getRoom(newX, newY);

                    if (tempRoom)
                        currentRoom = tempRoom;

                    if (currentRoom->getID() == 11) // End of the tutorial. clear and say congrats
                    {
                        system("cls");
                        std::cout << "Congratulations! You have completed the tutorial!\n";
                        Sleep(2000);
                        gameRunning = false;
                    }

                    Pos newPos = getDoorsOpposite(Pos(newX, newY));
                    updatePlayerPosition(currentRoom, player, newPos.getX(), newPos.getY());
                    printToConsole(currentRoom->getDisplay());
                }
                else if (nextChar == 'C')
                {
                    score += 10;
                    currentRoom->setCharAt(newX, newY, ' ');
                    updatePlayerPosition(currentRoom, player, newX, newY);
                }
                else if (touchingEnemy(currentRoom, player))
                {
                    Enemy *enemy = currentRoom->getEnemyAt(newX, newY);
                    if (enemy)
                    {
                        bool playerWon = fightEnemy(player, enemy);
                        if (playerWon)
                        {
                            currentRoom->removeEnemyAt(newX, newY);
                            score += 50;
                            updatePlayerPosition(currentRoom, player, newX, newY);
                        }
                        else
                        {
                            gameRunning = false;
                        }
                    }
                    printToConsole(currentRoom->getDisplay());
                }
                else
                {
                    updatePlayerPosition(currentRoom, player, newX, newY);
                }
            }

            if (currentTime - lastEnemyMoveTime >= enemyMoveDelay)
            {
                // moveEnemies(currentRoom);
                lastEnemyMoveTime = currentTime;
            }

            lastMoveTime = currentTime;

            // move enemies in this room
        }

        setCursorPosition(0, HEIGHT + 1);
        if (currentRoom->getRoomINFO().empty() == false)
        {
            std::cout << currentRoom->getRoomINFO() << "\n\n";
        }
        std::cout << "Health " << player.getHealth() << "\n";
        std::cout << "Score: " << score << " | Press Q to quit\n";
        std::cout << "Room: " << currentRoom->getID() << "\n";

        if (isKeyPressed('Q'))
            gameRunning = false;
        Sleep(10); // Small delay to prevent excessive CPU usage
    }

    std::cout << "Game Over! Final Score: " << score << "\n";
    return 0;
}

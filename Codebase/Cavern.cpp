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
#include "nums.cpp"
#include "nums.h"
#define WIDTH 25
#define HEIGHT 13
/*!
    @file 
    @brief Cavern is the main class for our game. It contains the game loop and the manner in which we display to the user.
    @author Sam Budgen, Ben Darlington, Ben Nicholson & Alex Poore.
    @copyright CCP 2024 
*/
/*!
    @brief The core methods for this file are the "main" method and initalizeTutorialMap
*/
/*!
    @brief Sets the cursor position
    @details This method takes a x and y position and sets the cursor to be at said position.
    @param x [in] the x-coord
    @param y [in] the y--coord
    @return void.
*/
void setCursorPosition(int x, int y)
{
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/*!
    @brief Method hides the cursor from the user.
    @details Method configures the console cursor so it doesn't display.
    @return void.
*/
void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
/*!
    @brief Determines whether a key is pressed.
    @param key [in] This is the Integer code for the key.
    @return Returns a true/false whether a key was pressed.
*/
bool isKeyPressed(int key)
{
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}
/*!
    @brief Method clears the console screen.
    @return void.
*/
void clearScreen() {
    std::system("cls");  // On Unix/Linux/OSX use "clear" instead of "cls"
}
/*!
    @brief Method acts as a delay of given miliseconds.
    @details Method runs a while loop for a given number of miliseconds delaying the code.
    @param miliseconds [in] this is the int representing the miliseconds we want the delay for.
    @return void.
*/
void delay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}
/*!
    @brief This method displays the "encounter" phase of combat an animation when we walk upto an enemy.
    @param playerPosition [in] this is the position to print the player. 
    @param enemyPosition [in] this is the position we want to print the enemy
    @param enemyHead [in] This is the enemies head. Whether it is a + - / or x type of enemy.
    @return void
*/
void displayScene(int playerPosition, int enemyPosition, char enemyHead) {
    // Print player head
    for (int i = 0; i < playerPosition; ++i) std::cout << ' ';
    std::cout << "  O  ";

    // Print spaces between the player and the skeleton
    for (int i = playerPosition + 5; i < enemyPosition; ++i) std::cout << ' ';

    // Skeleton head
    std::cout << "  " << enemyHead << "  " << std::endl;

    // Print player arms/torso
    for (int i = 0; i < playerPosition; ++i) std::cout << ' ';
    std::cout << " /|\\ ";

    // Print spaces between player arms and skeleton arms
    for (int i = playerPosition + 5; i < enemyPosition; ++i) std::cout << ' ';

    // Skeleton arms/torso
    std::cout << " /|\\ " << std::endl;

    // Print player legs
    for (int i = 0; i < playerPosition; ++i) std::cout << ' ';
    std::cout << " / \\ ";

    // Print spaces between player legs and skeleton legs
    for (int i = playerPosition + 5; i < enemyPosition; ++i) std::cout << ' ';

    // Skeleton legs
    std::cout << " / \\ " << std::endl;
}
/*!
    @brief This method animates the encounter between an enemy and a player.
    @details Calling displayScene, We use this to animate the frames as the enemy and player get closer together.
    @param enemyHead [in] Char, this is the type of enemy displayed as it's head.
    @return void.
*/
void animateEncounter(char enemyHead) {
    int playerPosition = 0;   // Start position of the player
    int enemyPosition = 20;   // Fixed position of the skeleton, closer to the player

    while (playerPosition < enemyPosition - 7) { // 7 is the total width of the player character
        clearScreen();
        displayScene(playerPosition, enemyPosition, enemyHead);
        delay(200);  // Adjust speed here
        playerPosition++;
    }

    // Final encounter, when the player is face-to-face with the skeleton
    clearScreen();
    displayScene(playerPosition, enemyPosition, enemyHead);

}
/**
 * setFGColor
 * This method uses ANSI escape codes to set the output color to console for the foreground.
 * @param int textColor - this is the color we want has to be > 1csc
 */
/*!
    @brief 
    @details 
    @param 
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
 * efefef
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
/*!
    @brief displays the enemy and player health bars in battle
    @param playerHealth [in] int, The players current health
    @param playerMaxHealth [in] int, the players max health
    @param enemyHealth [in] int, the enemies current health
    @param enemyMaxHealth [in] int, the enemies max health
    @param enemyName [in] String, this is the enemies name.
    @return void.
*/
void displayHealthBars(int playerHealth, int playerMaxHealth, int enemyHealth, int enemyMaxHealth, std::string enemyName) {
    const int barLength = 10;  // Length of the health bar
    int playerHealthBar = (playerHealth * barLength) / playerMaxHealth;
    int enemyHealthBar = (enemyHealth * barLength) / enemyMaxHealth;
    // Player Health Bar
    std::cout << "Player:   [";
    setFGColour(124);
    for (int i = 0; i < barLength; i++) {
        if (i < playerHealthBar) {
            std::cout << "=";
        } else {
            std::cout << " ";
        }
    }
    resetColour();
    std::cout << "] " << playerHealth << "/" << 100;
    // Enemy Health Bar on the same line
    std::cout << "   " << enemyName << ": [";
    setFGColour(124);
    for (int i = 0; i < barLength; i++) {
        if (i < enemyHealthBar) {
            std::cout << "=";
        } else {
            std::cout << " ";
        }
    }
    resetColour();
    std::cout << "] " << enemyHealth << "/" << enemyMaxHealth << std::endl;
}
/*!
    @brief  This is the game-loop for a battle between an enemy and a player.
    @param enemy [in] Enemy&, this the enemy we're fighting
    @param Player [in] Player&, this is our player object , containing our health etc.
    @return returns a boolean t/f whether we won or lost..
*/
bool battleScreen(Enemy &enemy, Player &Player) {
    char enemyHead = enemy.getSkin();

    animateEncounter(enemyHead);
    std::string enemyName;

    int encounterType = 0;

    if (enemyHead == '+') {
        enemyName = "Additor";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        encounterType = 1;



    } else if (enemyHead == '-') {
        enemyName = "Subraktor";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        encounterType = 2;


    } else if (enemyHead == '/') {

        enemyName = "Divisor";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        encounterType = 3;

    } else if (enemyHead == '*') {

        enemyName = "Multiplikator";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        encounterType = 4;

    } else {
        enemyName = "Additor";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;

        encounterType = 1;

    }
    delay(1000);

    int playerStartHealth = Player.getHealth();
    int enemyStartHealth = enemy.getHealth();

    int playerHealth = Player.getHealth();
    int enemyHealth = enemy.getHealth();

    bool outcome = false;
    clearScreen();


    while(playerHealth > 0 && enemyHealth > 0){

        displayScene(12, 50, enemyHead);
        std::cout <<" here";
        displayHealthBars(playerHealth, playerStartHealth, enemyHealth, enemyStartHealth, enemyName);


        if (encounterType == 1) {
            outcome = generateEquation();

        } else if (encounterType == 2) {
            outcome = generateSubtractionEquation();
        } else if (encounterType == 3) {
            outcome = generateDivisionEquation();
        } else if (encounterType == 4) {

            outcome = generateMultiplicationEquation();

        }

        if(outcome){
            enemyHealth -= 10;
            std::cout << "Effective attack" << std::endl;
        } else {
            playerHealth -= 10;
            std::cout << "Couldnt block incoming attack" << std::endl;

        }
        delay(750);
        clearScreen();



    }

    if(playerHealth <= 0){
        std::cout << "You have been defeated by " << enemyName << "." << std::endl;
    } else {
        std::cout << "You have defeated " << enemyName << "." << std::endl;

    }
    delay(750);

    Player.setHealth(playerHealth);
    return outcome;

}
/*!
    @brief The method updates the players postition within the map.
    @details taking the current room, player and the new x and y we plant the player within this new position assuming the newx and y are always valid.
    @param room [in] Room*, the current room.
    @param player [in] Player& the player object.
    @param newX [in] int, the new x-coord.
    @param newY [in] int, the new y-coord.
    @return void.
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
/*!
    @brief Method, given the oldposition gets the position you'd expect to be in going through a door to another room.
    @details Essentially returns a mirror of the position.
    @param oldPos [in] Pos, the old position before we hit a D
    @return Pos, returns the Pos (a position class) of the doors mirror position.
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

// bool fightEnemy(Player &player, Enemy *enemy)
// {
//     system("cls");
//     clearInputBuffer();
//     std::cout << "You are in combat with an enemy!\n";

//     int enemyHealth = enemy->getHealth();

//     while (enemyHealth > 0 && player.getHealth() > 0)
//     {
//         std::cout << "Player Health: " << player.getHealth() << " | Enemy Health: " << enemyHealth << "\n";
//         std::cout << "Enter your answer or type 'run' to attempt escape: ";
//         int correctAnswer = generateMathProblem();
//         std::string userInput;
//         std::cin >> userInput;

//         if (userInput == "run")
//         {
//             if (rand() % 2 == 0) // 50% chance to escape
//             {
//                 std::cout << "You successfully escaped!\n";
//                 Sleep(2000);
//                 return true;
//             }
//             else
//             {
//                 std::cout << "Escape failed! The enemy attacks you for 3 damage.\n";
//                 player.setHealth(player.getHealth() - 3);
//             }
//         }
//         else
//         {
//             int userAnswer;
//             try
//             {
//                 userAnswer = std::stoi(userInput);
//             }
//             catch (const std::invalid_argument &)
//             {
//                 std::cout << "Invalid input. The enemy attacks you for 3 damage.\n";
//                 player.setHealth(player.getHealth() - 3);
//                 Sleep(2000);
//                 continue;
//             }

//             if (userAnswer == correctAnswer)
//             {
//                 std::cout << "Correct! You dealt 10 damage to the enemy!\n";
//                 enemyHealth -= 10;
//             }
//             else
//             {
//                 std::cout << "Incorrect! You have taken 5 damage!\n";
//                 player.setHealth(player.getHealth() - 5);
//             }
//         }

//         Sleep(1500);   // Pause for 2 seconds between rounds
//         system("cls"); // Clear the screen for the next round
//     }

//     if (player.getHealth() <= 0)
//     {
//         std::cout << "You have been defeated!\n";
//         Sleep(2000);
//         return false;
//     }
//     else
//     {
//         std::cout << "You have defeated the enemy!\n";
//         Sleep(2000);
//         return true;
//     }
// }

bool fightEnemy(Player &player, Enemy *enemy){

    system("cls");

    clearInputBuffer();

    bool outcome = battleScreen(*enemy, player);

    return outcome;
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
                        std::cout << "You Win! You have reached the end of the Tutorial.\n";
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
        //Displays the players health.

        if (currentRoom->getRoomINFO().empty() == false)
        {
            std::cout << currentRoom->getRoomINFO() << "\n\n";
        }
               int playerHealthBar = (player.getHealth()* 10) /100;
         // Player Health Bar
        std::cout << "Health: [";
        setFGColour(124);
        for (int i = 0; i < 10; i++) {
            if (i < playerHealthBar) {
                std::cout << "=";
            } else {
                std::cout << " ";
            }
        }
        resetColour();
        std::cout << "] " << player.getHealth()<< "/" << 100<<"\n";
        std::cout << "\nScore: " << score << " | Press Q to quit\n";
        std::cout << "Room: " << currentRoom->getID() << "\n";
        if (isKeyPressed('Q'))
            gameRunning = false;
        Sleep(10); // Small delay to prevent excessive CPU usage
    }

    std::cout << "Game Over! Final Score: " << score << "\n";
    return 0;
}

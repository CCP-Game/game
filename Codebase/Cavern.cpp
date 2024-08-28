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
#include "nums.h"
#include "nums.cpp"



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

// Function to clear the screen
void clearScreen() {
    std::system("cls");  // On Unix/Linux/OSX use "clear" instead of "cls"
}

// Function to create a delay
void delay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}

/**
 * displayScene
 * prints the enemy and player on screen
 * @param playerPosition - psoition to print the player
 * @param enemyPosition - position to print the enemy
 * @param enemyHead - the enemy'skin
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


/**
 * animateEncounter
 * does first encounter animation
 * @param enemyHead - the enemy'skin
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
 * displayHealthBars
 * displays enemy and player health bars in battle
 * @param playerHealth - the playes current health
 * @param playerMaxHealth- player max health
 * @param playerHealth - the playes current health
 * @param playerMaxHealth- player max health
 */
void displayHealthBars(int playerHealth, int playerMaxHealth, int enemyHealth, int enemyMaxHealth, std::string enemyName) {
    const int barLength = 10;  // Length of the health bar

    int playerHealthBar = 100;
    int enemyHealthBar = (enemyHealth * barLength) / enemyMaxHealth;

    // Player Health Bar
    std::cout << "Player:   [";
    for (int i = 0; i < barLength; i++) {
        if (i < playerHealthBar) {
            std::cout << "=";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "] " << playerHealth << "/" << 100;

    // Enemy Health Bar on the same line
    std::cout << "   " << enemyName << ": [";
    for (int i = 0; i < barLength; i++) {
        if (i < enemyHealthBar) {
            std::cout << "=";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "] " << enemyHealth << "/" << enemyMaxHealth << std::endl;
}

/**
 * battleScreen
 * Method player and enemy and simulates a battle
 * @param &enemy - the enemy ran into
 * @param &player- the current player of Player class
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
 * setColor
 * This method uses ANSI escape codes to set the output color to console.
 * @param int textColor - this is the color we want has to be > 1
 * @param int bgColor - this is the background colour has to be > 1
 */
void setColour(int textColor, int bgColor = -1)
{
    std::cout << "\033[";
    if (textColor != -1)
    {
        std::cout << textColor;
    }
    if (bgColor != -1)
    {
        std::cout << ";" << bgColor;
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
 * initalize1DMap
 * Method implements a simple "linked-list-style" 1D map of rooms. Returning the first room.
 * @param roomSize
 * @return the first room in the linked list.
 */

// left = Pos(0, HEIGHT/2)
// right = Pos(WIDTH-1, HEIGHT/2)
// top = Pos(WIDTH/2, 0)
// bottom = Pos(WIDTH/2, HEIGHT-1)

Room *initalize1DMap(int roomLength)
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

    Enemy e1 = Enemy('*', 20);
    Enemy e2 = Enemy('/', 50);

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

    // Set door positions for each room
    room1->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room2); // Right to Room 2
    room1->setEnemy(Pos(3, 5), e1);                    // Enemy to the side of the room

    room2->setDoor(Pos(0, HEIGHT / 2), room1);         // Left to Room 1
    room2->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room3); // Right to Room 3
    room2->setEnemy(Pos(7, HEIGHT / 2), e2);           // Enemy to the side of the room

    room3->setDoor(Pos(0, HEIGHT / 2), room2);         // Left to Room 2
    room3->setDoor(Pos(WIDTH / 2, 0), room7);          // Top to Room 7
    room3->setDoor(Pos(WIDTH / 2, HEIGHT - 1), room4); // Bottom to Room 4

    // room3->setEnemy(Pos(WIDTH / 2, HEIGHT / 2), e1);    // Enemy in the middle of the room

    room4->setDoor(Pos(WIDTH / 2, 0), room3);          // Top to Room 3
    room4->setDoor(Pos(WIDTH / 2, HEIGHT - 1), room5); // Bottom to Room 5

    room5->setDoor(Pos(WIDTH / 2, 0), room4);          // Top to Room 4
    room5->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room6); // Right to Room 6

    room6->setDoor(Pos(0, HEIGHT / 2), room5); // Left to Room 5

    room7->setDoor(Pos(WIDTH / 2, HEIGHT - 1), room3); // Bottom to Room 3
    room7->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room8); // Right to Room 8

    room8->setDoor(Pos(0, HEIGHT / 2), room7);         // Left to Room 7
    room8->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room9); // Right to Room 9

    room9->setDoor(Pos(0, HEIGHT / 2), room8);          // Left to Room 8
    room9->setDoor(Pos(WIDTH / 2, HEIGHT - 1), room10); // Bottom to Room 10

    room10->setDoor(Pos(WIDTH / 2, 0), room9); // Top to Room 9
    // Room 10 has a staircase to another room
    room10->setDoor(Pos(WIDTH / 2, HEIGHT - 2), nullptr); // Stairway to new room

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
            setColour(31);

            if (display[y][x] == 'D')
            {
                setColour(32, 1);
            }
            if (display[y][x] == '#')
            {
                setColour(34);
            }
            if (display[y][x] == 'C')
            {
                setColour(33);
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
        if (room->getEnemies()[i].getX() == playerPos.getX() && room->getEnemies()[i].getY() == playerPos.getY())
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

bool fightEnemy(Player &player, Enemy &enemy)
{
    system("cls");
    clearInputBuffer();

    // Run the encounter animation and get the outcome (true = player wins, false = player loses)
    bool outcome = battleScreen(enemy, player);

    Sleep(2000);

    // Return true if the player is still alive (health > 0), otherwise false
    return outcome;
}


void updateEnemyPosition(Room *room, Enemy &enemy, int newX, int newY)
{
    const Pos &currentPos = enemy.getPos();
    // Clear the old enemy position in the room matrix
    room->setCharAt(currentPos.getX(), currentPos.getY(), ' ');
    // Clear the old enemy position on the screen
    setCursorPosition(currentPos.getX(), currentPos.getY());
    std::cout << ' ';
    room->removeEnemyAt(currentPos.getX(), currentPos.getY());
    // Update the enemy's position
    enemy.setX(newX);
    enemy.setY(newY);
    // Set the new enemy position in the room matrix
    room->setCharAt(newX, newY, enemy.getSkin());
    room->setEnemyAt(newX, newY, enemy);
    // Draw the new enemy position on the screen
    setCursorPosition(newX, newY);
    std::cout << enemy.getSkin();
}

void moveEnemies(Room *room)
{
    for (auto &enemy : room->getEnemies())
    {
        const Pos &currentPos = enemy.getPos();
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
    Room *currentRoom = initalize1DMap(1);

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
                    Room *tempRoom = currentRoom->getRoom(newX, newY);
                    if (tempRoom)
                        currentRoom = tempRoom;

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
                    Enemy *enemy = &currentRoom->getEnemyAt(newX, newY);
                    if (enemy)
                    {
                        bool playerWon = fightEnemy(player, *enemy);
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
                //moveEnemies(currentRoom);
                lastEnemyMoveTime = currentTime;
            }

            lastMoveTime = currentTime;

            // move enemies in this room
        }

        setCursorPosition(0, HEIGHT + 1);
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

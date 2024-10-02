#include <iostream>
#include <windows.h>
#include <cstdlib> // For random number generation
#include <ctime>   // To seed random generator
#include <map>
#include <stdexcept>
#include <conio.h> // For _kbhit() and _getch()
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Winmm.lib")
#include <algorithm>
#include "Pos.h"
#include "Room.h"
#include "Player.h"
#include "Enemy.h"
#include "nums.h"
#include "animations.h"
#include <random>
#include <string>
#define WIDTH 25
#define HEIGHT 13
/*!
    @file
    @brief Cavern is the main class for our game. It contains the game loop and the manner in which we display our game to the user.
    @author Sam Budgen, Ben Darlington, Ben Nicholson & Alex Poore.
    @copyright CCP 2024
*/

bool hasKey = false;
/*!
    @brief The core methods for this file are the "main" method and initalizeTutorialMap they initalize and run the game.
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
void clearScreen()
{
    std::cout << "\033cls";       // On Unix/Linux/OSX use "clear" instead of "cls"
}
/*!
    @brief Method acts as a delay of given miliseconds.
    @details Method runs a while loop for a given number of miliseconds delaying the code.
    @param miliseconds [in] this is the int representing the miliseconds we want the delay for.
    @return void.
*/
void delay(int milliseconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds)
        ;
}
/*!
    @brief This method displays the "encounter" phase of combat an animation when we walk upto an enemy.
    @param playerPosition [in] this is the position to print the player.
    @param enemyPosition [in] this is the position we want to print the enemy
    @param enemyHead [in] This is the enemies head. Whether it is a + - / or x type of enemy.
    @return void
*/
void displayScene(int playerPosition, int enemyPosition, char enemyHead)
{
    // Print player head
    for (int i = 0; i < playerPosition; ++i)
        std::cout << ' ';
    std::cout << "  O  ";

    // Print spaces between the player and the skeleton
    for (int i = playerPosition + 5; i < enemyPosition; ++i)
        std::cout << ' ';

    // Skeleton head
    std::cout << "  " << enemyHead << "  " << std::endl;

    // Print player arms/torso
    for (int i = 0; i < playerPosition; ++i)
        std::cout << ' ';
    std::cout << " /|\\ ";

    // Print spaces between player arms and skeleton arms
    for (int i = playerPosition + 5; i < enemyPosition; ++i)
        std::cout << ' ';

    // Skeleton arms/torso
    std::cout << " /|\\ " << std::endl;

    // Print player legs
    for (int i = 0; i < playerPosition; ++i)
        std::cout << ' ';
    std::cout << " / \\ ";

    // Print spaces between player legs and skeleton legs
    for (int i = playerPosition + 5; i < enemyPosition; ++i)
        std::cout << ' ';

    // Skeleton legs
    std::cout << " / \\ " << std::endl;
}
/*!
    @brief This method animates the encounter between an enemy and a player.
    @details Calling displayScene, We use this to animate the frames as the enemy and player get closer together.
    @param enemyHead [in] Char, this is the type of enemy displayed as it's head.
    @return void.
*/
void animateEncounter(char enemyHead)
{
    int playerPosition = 0; // Start position of the player
    int enemyPosition = 20; // Fixed position of the skeleton, closer to the player

    while (playerPosition < enemyPosition - 7)
    { // 7 is the total width of the player character
        clearScreen();
        displayScene(playerPosition, enemyPosition, enemyHead);
        delay(200); // Adjust speed here
        playerPosition++;
    }

    // Final encounter, when the player is face-to-face with the skeleton
    clearScreen();
    displayScene(playerPosition, enemyPosition, enemyHead);
}
/*!
    @brief Sets the foreground colour on the console output.
    @details Using ANSI escape codes we're able to change the output colour to console
    @param textColour [in] int, This is the text colur upto 255. Default is white 255
    @return void
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
/*!
   @brief This method sets the Background Colour for text being printed to console
   @details Utilizing ANSI escape codes we can set the background colour of text.
   @param textColour [in] int, this is the background colour we have chosen. Default is 255 (white)
   @return void.
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
/*!
    @brief
    @details
    @param
    @return
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
void displayHealthBars(int playerHealth, int playerMaxHealth, int enemyHealth, int enemyMaxHealth, const std::string enemyName)
{
    const int barLength = 10; // Length of the health bar
    int playerHealthBar = (playerHealth * barLength) / playerMaxHealth;
    int enemyHealthBar = (enemyHealth * barLength) / enemyMaxHealth;
    // Player Health Bar
    std::cout << "Player:   [";
    setFGColour(124);
    for (int i = 0; i < barLength; i++)
    {
        if (i < playerHealthBar)
        {
            std::cout << "=";
        }
        else
        {
            std::cout << " ";
        }
    }
    resetColour();
    std::cout << "] " << playerHealth << "/" << 100;
    // Enemy Health Bar on the same line
    std::cout << "   " << enemyName << ": [";
    setFGColour(124);
    for (int i = 0; i < barLength; i++)
    {
        if (i < enemyHealthBar)
        {
            std::cout << "=";
        }
        else
        {
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
bool battleScreen(Enemy &enemy, Player &Player)
{
    char enemyHead = enemy.getSkin();

    animateEncounter(enemyHead);
    PlaySound(TEXT("encounter.wav"), NULL, SND_FILENAME | SND_ASYNC);

    std::string enemyName;

    int encounterType = 0;

    if (enemyHead == '+')
    {
        enemyName = "Additor";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        encounterType = 1;
    }
    else if (enemyHead == '-')
    {
        enemyName = "Subraktor";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        encounterType = 2;
    }
    else if (enemyHead == '/')
    {

        enemyName = "Divisor";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        encounterType = 3;
    }
    else if (enemyHead == '*')
    {

        enemyName = "Multiplikator";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        encounterType = 4;
    }
    else if (enemyHead == 'B')
    {

        enemyName = "Boss";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        encounterType = 5;
    }
    else
    {
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

    while (playerHealth > 0 && enemyHealth > 0)
    {

        displayScene(12, 50, enemyHead);
        std::cout << " here";
        displayHealthBars(playerHealth, playerStartHealth, enemyHealth, enemyStartHealth, enemyName);

        if (encounterType == 1)
        {
            outcome = generateEquation();
        }
        else if (encounterType == 2)
        {
            outcome = generateSubtractionEquation();
        }
        else if (encounterType == 3)
        {
            outcome = generateDivisionEquation();
        }
        else if (encounterType == 4)
        {

            outcome = generateMultiplicationEquation();
        }
        else if (encounterType == 5)
        {
            //int firstChooser = rand() % 2 + 1;
            int firstChooser = 2;

            if (firstChooser == 1)
            {
                //generateComplexEquation();
            }
            else
            {
                int chooser = rand() % 4 + 1;

                if (chooser == 1)
                {
                    outcome = generateEquation();
                }
                else if (chooser == 2)
                {
                    outcome = generateSubtractionEquation();
                }
                else if (chooser == 3)
                {
                    outcome = generateDivisionEquation();
                }
                else if (chooser == 4)
                {
                    outcome = generateMultiplicationEquation();
                }
            }
        }

        if (outcome)
        {
            enemyHealth -= 10;

            PlaySound(TEXT("good.wav"), NULL, SND_FILENAME | SND_ASYNC);

            std::cout << "Effective attack" << std::endl;
        }
        else
        {
            playerHealth -= 10;

            PlaySound(TEXT("encounter.wav"), NULL, SND_FILENAME | SND_ASYNC);

            std::cout << "Couldnt block incoming attack" << std::endl;
        }
        delay(750);
        clearScreen();
    }

    if (playerHealth <= 0)
    {
        std::cout << "You have been defeated by " << enemyName << "." << std::endl;
    }
    else
    {
        PlaySound(TEXT("winfight.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
/*!
    @brief This method initalizes are Tutorial map.
    @details This method creates all the Rooms, enemies and links them together. Returning a pointer to the first room.
    @param roomLength [in] int, this is how many rooms we want.
    @return Room - Returns a pointer to the first room in the map.
*/
Room *initializeProceduralMap();

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
    Room *end = nullptr;

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
    // end->setFinal(true);

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
    room9->setEnemy(Pos(WIDTH / 2, 6), e8);             // Enemy in the middle of the room
    room9->setEnemy(Pos(4, HEIGHT / 2), e9);            // Enemy in the middle of the room
    room9->setRoomINFO("LOTS OF ENEMIES!");

    room10->setDoor(Pos(WIDTH / 2, 0), room9); // Top to Room 9
    // Room 10 has a staircase to another room
    room10->setDoor(Pos(WIDTH / 2, HEIGHT - 3), end); // Stairway to new room
    room10->setRoomINFO("Congratulations! You've reached the end of the tutorial!");

    return room1; // Game starts in room 1
}
/*!
    @brief This method takes a Room's display and displays it to the console
    @details This method takes a rooms char** array and displays it to the console.
    @param display [in] char**, this is the char array to be printed to the console.
    @return void.
*/
// Room position helper
struct Position
{
    int x, y;
    Position(int x, int y) : x(x), y(y) {}

    bool operator==(const Position &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Position &other) const
    {
        return !(*this == other);
    }
};

// Hash function for Position to use in map
struct PositionHash
{
    std::size_t operator()(const Position &pos) const
    {
        return std::hash<int>()(pos.x) ^ std::hash<int>()(pos.y);
    }
};

Position convertPosToPosition(Pos pos)
{
    return Position(pos.getX(), pos.getY());
}

Room *initializeProceduralMap();

bool hasPlacedKey = false;

Room *createRandomRoom(int id, bool isMainPath, bool isFinalRoom, bool isRedHerring)
{
    Room *room = new Room(id, 1, WIDTH, HEIGHT);
    room->initializeRoom(5, 'b'); // Always create big rooms
    // Set room information with id, isMainPath, isFinalRoom, and isRedHerring
    std::string roomInfo;
    // list of good adjectives
    std::string adjectives[] = {"Studry", "Solid", "Spacious", "Warm", "Inviting", "Glowing", "Strange", "Tidy", "Neat", "Large"};
    // list of bad adjectives
    std::string badAdjectives[] = {"Cold", "Dark", "Damp", "Old", "Ominous", "Dusty", "Uncanny", "Gloomy", "Creepy", "Small"};

    if (isMainPath)
    {
        std::string first = adjectives[rand() % 10];
        std::string second = adjectives[rand() % 10];
        while (first == second)
        {
            second = adjectives[rand() % 10];
        }
        roomInfo += "A ";
        roomInfo += first;
        roomInfo += " and ";
        roomInfo += second;
        roomInfo += " room";
    }
    if (isFinalRoom)
    {
        if (hasKey)
        {
            roomInfo = "A staircase to the next level";
        }
        else
        {
            roomInfo = "You need a key to unlock the staircase!";
        }
    }
    if (isRedHerring)
    {
        std::string first = badAdjectives[rand() % 10];
        std::string second = badAdjectives[rand() % 10];
        while (first == second)
        {
            second = badAdjectives[rand() % 10];
        }
        roomInfo += "A ";
        roomInfo += first;
        roomInfo += " and ";
        roomInfo += second;
        roomInfo += " room";
        if (!hasPlacedKey)
        {
            hasPlacedKey = true;
            room->setKey();
        }
    }
    room->setRoomINFO(roomInfo);

    // if final room add a door in the middle of the room that takes you to the next level
    if (isFinalRoom)
    {
        room->setFinal(true);
        room->setDoor(Pos(WIDTH / 2, HEIGHT / 2), nullptr);
        // if new room is final room, add boss enemy ('B')
        Enemy *boss = new Enemy('B', 100);
        room->setEnemy(Pos(WIDTH / 2, HEIGHT - 5), boss);
    }
    else
    {
        room->setFinal(false);
    }

    return room;
}

// Function to scatter enemies randomly in the room
void scatterEnemies(Room *room)
{
    

    Enemy *enemies[] = {
        new Enemy('+', 20), new Enemy('+', 30), new Enemy('+', 50),
        new Enemy('*', 20), new Enemy('*', 30), new Enemy('*', 50),
        new Enemy('/', 20), new Enemy('/', 30), new Enemy('/', 50)};
    int numEnemies = rand() % 3 + 1; // 1 to 3 enemies

//New for plus room
    if (room->getType() == 'x'){
        for (int i = 0; i < numEnemies; i++)
        {
        int xPos = rand() % (WIDTH - 14) + 7;  // Generate random x position within the inner ring
        int yPos = rand() % (HEIGHT - 10) + 5; // Generate random y position within the inner ring
        room->setEnemy(Pos(xPos, yPos), enemies[rand() % 9]);
        }
    }else{
        for (int i = 0; i < numEnemies; i++)
        {
            int xPos = rand() % (WIDTH - 2) + 1;  // Generate random x position within the inner ring
            int yPos = rand() % (HEIGHT - 2) + 1; // Generate random y position within the inner ring
            room->setEnemy(Pos(xPos, yPos), enemies[rand() % 9]);
        }
    }
}

// Function to get a random direction and avoid backtracking
Position getRandomDirection(const Position &currentPos, const std::unordered_map<Position, Room *, PositionHash> &placedRooms)
{
    std::vector<Position> possibleDirections = {
        Position(currentPos.x + 1, currentPos.y), // Right (east)
        Position(currentPos.x - 1, currentPos.y), // Left (west)
        Position(currentPos.x, currentPos.y + 1), // Down (south)
        Position(currentPos.x, currentPos.y - 1)  // Up (north)
    };

    // Shuffle the directions to randomize
    std::shuffle(possibleDirections.begin(), possibleDirections.end(), std::mt19937{std::random_device{}()});
    for (const auto &dir : possibleDirections)
    {
        if (placedRooms.find(dir) == placedRooms.end())
        {
            return dir; // Return a valid, unoccupied direction
        }
    }

    return currentPos; // In case of no valid direction, return current position
}

// Function to connect two rooms
void connectRooms(Room *room1, Room *room2, const Position &pos1, const Position &pos2)
{
    if (pos1.x < pos2.x)
    {
        // room2 is to the east of room1
        room1->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room2);
        room2->setDoor(Pos(0, HEIGHT / 2), room1);
    }
    else if (pos1.x > pos2.x)
    {
        // room2 is to the west of room1
        room1->setDoor(Pos(0, HEIGHT / 2), room2);
        room2->setDoor(Pos(WIDTH - 1, HEIGHT / 2), room1);
    }
    else if (pos1.y < pos2.y)
    {
        // room2 is to the south of room1
        room1->setDoor(Pos(WIDTH / 2, HEIGHT - 1), room2);
        room2->setDoor(Pos(WIDTH / 2, 0), room1);
    }
    else if (pos1.y > pos2.y)
    {
        // room2 is to the north of room1
        room1->setDoor(Pos(WIDTH / 2, 0), room2);
        room2->setDoor(Pos(WIDTH / 2, HEIGHT - 1), room1);
    }
}

// Function to create main path with random positions
void createMainPath(std::unordered_map<Position, Room *, PositionHash> &placedRooms, int &currentRoomId, Position &currentPos, Room *startRoom)
{
    Room *prevRoom = startRoom;
    for (int i = 0; i < 5; ++i) // Increased to 5 rooms to ensure a longer main path
    {
        Position nextPos = getRandomDirection(currentPos, placedRooms);

        if (nextPos == currentPos || placedRooms.find(nextPos) != placedRooms.end())
        {
            break; // No available direction or position is occupied
        }

        bool isFinalRoom = (i == 4); // Last room in the main path
        Room *room = createRandomRoom(currentRoomId++, true, isFinalRoom, false);

        connectRooms(prevRoom, room, currentPos, nextPos);

        // if (i == 3)
        // {
        //     // add a red herring room
        //     Room *redHerring = createRandomRoom(currentRoomId++, false, false, true);
        //     connectRooms(room, redHerring, nextPos, getRandomDirection(nextPos, placedRooms));
        //     scatterEnemies(redHerring);
        //     placedRooms[Position(getDoorsOpposite(Pos(nextPos.x, nextPos.y)).getX(), getDoorsOpposite(Pos(nextPos.x, nextPos.y)).getY())] = redHerring;
        // }

        scatterEnemies(room);
        placedRooms[nextPos] = room;
        currentPos = nextPos; // Move to the next position
        prevRoom = room;
    }
}

// Function to create red herring rooms
void createRedHerrings(std::unordered_map<Position, Room *, PositionHash> &placedRooms, int &currentRoomId, Room *startRoom)
{
    // Create two red herring paths from the start room
    for (int i = 0; i < 2; ++i)
    {
        Position currentPos(0, 0); // Start from the beginning
        Position redHerringPos = getRandomDirection(currentPos, placedRooms);
        if (redHerringPos == currentPos)
            continue; // No available direction

        Room *redHerring = createRandomRoom(currentRoomId++, false, false, true);
        connectRooms(startRoom, redHerring, currentPos, redHerringPos);
        scatterEnemies(redHerring);
        placedRooms[redHerringPos] = redHerring;

        // One longer red herring path
        if (i == 0)
        {
            Position extendedHerringPos = getRandomDirection(redHerringPos, placedRooms);
            if (extendedHerringPos != redHerringPos)
            {
                Room *extendedHerring = createRandomRoom(currentRoomId++, false, false, true);
                connectRooms(redHerring, extendedHerring, redHerringPos, extendedHerringPos);
                scatterEnemies(extendedHerring);
                placedRooms[extendedHerringPos] = extendedHerring;
            }
        }
    }
}

Room *initializeProceduralMap()
{
    srand(static_cast<unsigned>(time(0))); // Seed random number generator

    hasKey = false;
    hasPlacedKey = false;

    std::unordered_map<Position, Room *, PositionHash> placedRooms;
    int currentRoomId = 1;
    Position startPos(0, 0);

    // Step 1: Create starting room
    Room *startRoom = createRandomRoom(currentRoomId++, true, false, false);
    placedRooms[startPos] = startRoom;

    // Step 2: Create main path with randomized room positions
    Position currentPos = startPos;
    createMainPath(placedRooms, currentRoomId, currentPos, startRoom);

    // Step 3: Add red herring rooms from the start room
    createRedHerrings(placedRooms, currentRoomId, startRoom);

    return startRoom; // Return the starting room
}

void printToConsole(char **display)
{
    std::cout << "\033cls";         // Clear the console
    setCursorPosition(0, 0); // Sets the cursor position..
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
/*!
    @brief This method determines whether a player is touching an enemy.
    @details This method takes the current room and player determining whether a player is close-enought oan enemy to trigger combat.
    @param room [in] Room*, the current room.
    @param player [in] Player , the current player.
    @return boolean, t/f if we are or aren't touching an enemy.
*/
boolean touchingEnemy(Room *room, const Player &player)
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
/*!
    @brief clears the input recieved by our game.
    @return void.
*/
void clearInputBuffer()
{
    while (_kbhit())
    {
        _getch(); // Read any characters left in the input buffer
    }
}
/*!
    @brief This method generates a mathematics problem for our combat.
    @details generates a random number pair for a mathproblem.
    @return int, returns the answer to the problem.
*/
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
/*!
    @brief Starts the fight enemy seqeunce.
    @param player [in] Player& - the current player.
    @param enemy [in] Enemy* the current enemy
    @return boolean t/f if we won or lost.

*/
bool fightEnemy(Player &player, Enemy *enemy)
{

    std::cout << "\033cls";      

    clearInputBuffer();

    bool outcome = battleScreen(*enemy, player);

    return outcome;
}
/*!
    @brief Method updates the enemy position each time it is called.
    @param room [in] Room* - the current room
    @param enemy [in] Enemy* - the current enemy
    @param newX [in] int - players x coord
    @param newy [in] int - palyers y coord
    @return void

*/
void updateEnemyPosition(Room *room, Enemy *enemy, int newX, int newY)
{

    // Clear the old enemy position in the room matrix
    room->setCharAt(enemy->getX(), enemy->getY(), ' ');
    // Clear the old enemy position on the screen
    setCursorPosition(enemy->getX(), enemy->getY());
    std::cout << ' ';
    enemy->setX(newX);
    enemy->setY(newY);
    // Set the new enemy position in the room matrix
    room->setCharAt(newX, newY, enemy->getSkin());
    room->setEnemyAt(newX, newY, enemy);
    // Draw the new enemy position on the screen
    setCursorPosition(newX, newY);
    setFGColour(124);
    std::cout << enemy->getSkin();
    resetColour();
}
/*!
    @brief Method updates all enemies position within the room.
    @param room [in] Room* - the current room.
    @return void.
*/
void moveEnemies(Room *room)
{
    bool validmove = true;
    for (auto &enemy : room->getEnemies())
    {
        const Pos &currentPos = enemy->getPos();
        int newX = currentPos.getX();
        int newY = currentPos.getY();

        // Move towards the player
        int playerX = room->getPlayerPos().getX();
        int playerY = room->getPlayerPos().getY();

        // Showcases the option available to our enemy
        std::vector<std::vector<int>> pairs = {
            {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
        // Finding the next best positoon
        double nextbestposScore = 1e9; // Use a large number to find minimum
        double tempscore = 0.0;
        int nextbestmove = 0;
        // Using Pythagorean theorem calculates the distances given a potential move. Chooses the shortest distance.
        for (int i = 0; i < pairs.size(); i++)
        {
            // Calculate the new potential position
            int potentialX = newX + pairs[i][0];
            int potentialY = newY + pairs[i][1];
            // Calculate the distance to the player
            tempscore = std::sqrt(std::pow(playerX - potentialX, 2) + std::pow(playerY - potentialY, 2));
            // Update the best move if the current score is better
            if (tempscore < nextbestposScore)
            {
                nextbestposScore = tempscore;
                nextbestmove = i;
            }
        }

        // Update the position based on the best move found
        newX += pairs[nextbestmove][0];
        newY += pairs[nextbestmove][1];

        // Ensure the move is valid (not hitting another enemy player.)
        for (int i = 0; i < room->getEnemies().size(); i++)
        {
            if (room->getEnemies()[i]->getX() == newX && room->getEnemies()[i]->getY() == newY)
                validmove = false;
        }
        if (room->validMove(newX, newY) == true && validmove == true && room->getCharAt(newX, newY) != 'D')
        {
            updateEnemyPosition(room, enemy, newX, newY);
        }
        validmove = true;
    }
}
/*!
 * @brief Simply returns the menu screen to be displayed. In this case a string.
 * @return - Returns the cavern homescreen logo.
 */
std::string getMenuScreen(bool ingame)
{
    std::string menuScreenInGame =
        "\n"
        "       _______  _______           _______  _______  _             \n"
        "      (  ____ \\(  ___  )|\\     /|(  ____ \\(  _____)( )    /|   \n"
        "      | (    \\/| (   ) || )   ( || (    \\/| (    )||  \\  ( |   \n"
        "      | |      | (___) || |   | || (__    | (____)||   \\ | |     \n"
        "      | |      |  ___  |( (   ) )|  __)   |     __)| (\\ \\) |    \n"
        "      | |      | (   ) | \\ \\_/ / | (      | (\\ (   | | \\   |  \n"
        "      | (____/\\| )   ( |  \\   /  | (____/\\| ) \\ \\__| )  \\  |\n"
        "      (_______/|/     \\|   \\_/   (_______/|/   \\__/|/    )_)   \n"
        "                                                                  \n"
        "       Press \"R\" to continue current game                        \n"
        "                                                                  \n"
        "       Press \"S\" to restart CAVERN                              \n"
        "                                                                  \n"
        "       Press \"T\" to play the tutorial                           \n"
        "                                                                  \n"
        "       Press \"Q\" to quit CAVERN                                 \n"
        "                                                                  \n";

    std::string menuScreenStart =
        "\n"
        "       _______  _______           _______  _______  _             \n"
        "      (  ____ \\(  ___  )|\\     /|(  ____ \\(  _____)( )    /|   \n"
        "      | (    \\/| (   ) || )   ( || (    \\/| (    )||  \\  ( |   \n"
        "      | |      | (___) || |   | || (__    | (____)||   \\ | |     \n"
        "      | |      |  ___  |( (   ) )|  __)   |     __)| (\\ \\) |    \n"
        "      | |      | (   ) | \\ \\_/ / | (      | (\\ (   | | \\   |  \n"
        "      | (____/\\| )   ( |  \\   /  | (____/\\| ) \\ \\__| )  \\  |\n"
        "      (_______/|/     \\|   \\_/   (_______/|/   \\__/|/    )_)   \n"
        "                                                                  \n"
        "       Press \"S\" to start CAVERN                                \n"
        "                                                                  \n"
        "       Press \"T\" to play the tutorial                           \n"
        "                                                                  \n"
        "       Press \"Q\" to quit CAVERN                                 \n"
        "                                                                  \n";
    if (ingame == true)
    {
        return menuScreenInGame;
    }
    else
    {
        return menuScreenStart;
    }
}
void playFootstep()
{
    // choose random step sound format "footstep00"-09.wav
    // int stepSound = rand() % 10;
    // std::string stepSoundFile = "footstep0" + std::to_string(stepSound) + ".wav";
    // PlaySound(TEXT(stepSoundFile.c_str()), NULL, SND_FILENAME | SND_ASYNC);
}

/*!
    @brief This "main" runs our game. It is where the game-loop is located
    @details Method initalizes our game and runs it.
    @return int , exit code.
*/
int main()
{
    try
    {
        int score = 0;
        bool gameRunning = true;
        DWORD lastMoveTime = GetTickCount();
        DWORD lastEnemyMoveTime = GetTickCount();
        DWORD currentTime = GetTickCount();
        const DWORD enemyMoveDelay = 500;
        const DWORD moveDelay = 100;
        int newX = 0;
        int newY = 0;
        srand(static_cast<unsigned>(time(0)));
        Room *currentRoom;
        bool resumeGame = false;
        clearScreen();

        displayCavernAnimation();
        std::cout << getMenuScreen(false) << std::endl;
        // Start menu logic!
        while (resumeGame == false)
        {
            if (isKeyPressed('S'))
            {
                currentRoom = initializeProceduralMap();
                resumeGame = true;
            }
            if (isKeyPressed('T'))
            {
                currentRoom = initalizeTutorialMap(10);
                resumeGame = true;
            }
            if (isKeyPressed('Q'))
            {
                std::cout << "\033cls";      
                return (0);
            }
        }
        Player player('P', 100);
        player.setPosition(WIDTH / 2, HEIGHT / 2);
        currentRoom->setCharAt(player.getPos().getX(), player.getPos().getY(), player.getSkin());
    //he
        // Initial full screen draw
        printToConsole(currentRoom->getDisplay());
        hideCursor();
        // Game
        while (gameRunning)
        {
            currentTime = GetTickCount();
            if (currentTime - lastMoveTime >= moveDelay)
            {
                const Pos &currentPos = player.getPos();
                newX = currentPos.getX();
                newY = currentPos.getY();
                // Below, logic for when the menu button is pressed.
                if (isKeyPressed('M'))
                {
                    std::cout << "\033cls";      
                    std::cout << getMenuScreen(true) << std::endl;
                    // Loop for whilst we're in the menu.
                    while (resumeGame == false)
                    {
                        DWORD currentTime = GetTickCount();
                        if (currentTime - lastMoveTime >= (DWORD)500)
                        {
                            if (isKeyPressed('R'))
                            {
                                resumeGame = true;
                            }
                            if (isKeyPressed('Q'))
                            {
                                std::cout << "\033cls";      
                                return (0);
                            }
                            if (isKeyPressed('S'))
                            {
                                Room *tempRoom = initializeProceduralMap();
                                currentRoom = tempRoom;
                                // Calculate the new position in the next room
                                Pos newPos = getDoorsOpposite(Pos(newX, newY));
                                // Update player position to the new room
                                updatePlayerPosition(currentRoom, player, newPos.getX(), newPos.getY());
                                // Full redraw when changing rooms
                                player.setPosition(WIDTH / 2, HEIGHT / 2);
                                player.setHealth(100);
                                currentRoom->setCharAt(player.getPos().getX(), player.getPos().getY(), player.getSkin());
                                resumeGame = true;
                                score = 0;
                            }
                            if (isKeyPressed('T'))
                            {
                                currentRoom = initalizeTutorialMap(10);
                                player.setPosition(WIDTH / 2, HEIGHT / 2);
                                player.setHealth(100);
                                currentRoom->setCharAt(player.getPos().getX(), player.getPos().getY(), player.getSkin());
                                resumeGame = true;
                                score = 0;
                            }
                        }
                        DWORD lastMoveTime = currentTime;
                    }
                    resumeGame = false;
                    printToConsole(currentRoom->getDisplay());
                    // if final room and hasKey is false, set the center door to be locked 'L'
                    if (currentRoom->getFinal() && !hasKey)
                    {
                        Pos doorPos = Pos(WIDTH / 2, HEIGHT / 2);
                        currentRoom->setCharAt(doorPos.getX(), doorPos.getY(), 'L');
                    }
                }
                if (isKeyPressed('W'))
                {
                    newY--;
                    playFootstep();
                }
                if (isKeyPressed('S'))
                {
                    newY++;
                    playFootstep();
                }

                if (isKeyPressed('A'))
                {
                    newX--;
                    playFootstep();
                }

                if (isKeyPressed('D'))
                {
                    newX++;
                    playFootstep();
                }

                char nextChar = currentRoom->getCharAt(newX, newY);

                if (currentRoom->validMove(newX, newY))
                {

                    if (currentRoom->isDoorMove(newX, newY))
                    {
                        PlaySound(TEXT("door.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        currentRoom->removePlayer();
                        Room *tempRoom = currentRoom->getRoom(newX, newY);

                        if (tempRoom)
                        {
                            currentRoom = tempRoom;
                            // Calculate the new position in the next room
                            Pos newPos = getDoorsOpposite(Pos(newX, newY));
                            // Update player position to the new room
                            updatePlayerPosition(currentRoom, player, newPos.getX(), newPos.getY());
                            // Full redraw when changing rooms
                            printToConsole(currentRoom->getDisplay());
                            if (currentRoom->getFinal() && !hasKey)
                            {
                                Pos doorPos = Pos(WIDTH / 2, HEIGHT / 2);
                                currentRoom->setCharAt(doorPos.getX(), doorPos.getY(), 'L');
                            }
                        }
                        else
                        {
                            tempRoom = initializeProceduralMap();
                            currentRoom = tempRoom;
                            // Calculate the new position in the next room
                            Pos newPos = getDoorsOpposite(Pos(newX, newY));
                            // Update player position to the new room
                            updatePlayerPosition(currentRoom, player, newPos.getX(), newPos.getY());
                            // Full redraw when changing rooms
                            printToConsole(currentRoom->getDisplay());
                            player.setPosition(WIDTH / 2, HEIGHT / 2);
                            currentRoom->setCharAt(player.getPos().getX(), player.getPos().getY(), player.getSkin());
                        }
                    }
                    else if (nextChar == 'C')
                    {
                        score += 10;
                        PlaySound(TEXT("coin.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        currentRoom->setCharAt(newX, newY, ' ');
                        updatePlayerPosition(currentRoom, player, newX, newY);
                    }
                    else if (nextChar == 'K')
                    {
                        PlaySound(TEXT("key.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        currentRoom->setCharAt(newX, newY, ' ');
                        hasKey = true;
                        updatePlayerPosition(currentRoom, player, newX, newY);
                    }
                    else if (touchingEnemy(currentRoom, player))
                    {
                        PlaySound(TEXT("danger.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        Enemy *enemy = currentRoom->getEnemyAt(newX, newY);
                        if (enemy)
                        {
                            bool playerWon = fightEnemy(player, enemy);
                            if (playerWon)
                            {
                                PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                currentRoom->removeEnemyAt(newX, newY);
                                score += 50;
                                // display the room again
                                printToConsole(currentRoom->getDisplay());
                                updatePlayerPosition(currentRoom, player, newX, newY);
                            }
                            else
                            {
                                PlaySound(TEXT("encounter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                gameRunning = false;
                                displayGameOverAnimation();
                                std::cout << "\033cls";      
                            }
                        }
                    }
                    else
                    {
                        updatePlayerPosition(currentRoom, player, newX, newY);
                    }

                    // Move enemies.
                    if ((currentTime - lastEnemyMoveTime) >= enemyMoveDelay)
                    {
                        moveEnemies(currentRoom);
                        lastEnemyMoveTime = GetTickCount();
                    }
                    // // {
                    // //     moveEnemies(currentRoom);
                    // //     lastEnemyMoveTime = currentTime;
                    // }

                    lastMoveTime = currentTime;
                }

                // Update status information
                setCursorPosition(0, HEIGHT + 1);
                if (!currentRoom->getRoomINFO().empty())
                {
                    std::cout << currentRoom->getRoomINFO() << std::string(80 - currentRoom->getRoomINFO().length(), ' ') << "\n\n";
                }

                int playerHealthBar = (player.getHealth() * 10) / 100;
                std::cout << "Health: [";
                setFGColour(124);
                for (int i = 0; i < 10; i++)
                {
                    std::cout << (i < playerHealthBar ? "=" : " ");
                }
                resetColour();
                std::cout << "] " << player.getHealth() << "/" << 100 << std::string(50, ' ') << "\n";
                std::cout << "Score: " << score << " | Press M for the menu " << std::string(50, ' ') << "\n";
                std::cout << "Room: " << currentRoom->getID() << std::string(50, ' ') << "\n";
                std::cout << "Has Key: " << (hasKey ? "Yes" : "No") << std::string(50, ' ') << "\n";
            }

            Sleep(10);
        }

        std::cout << "Game Over! Final Score: " << score << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "An unknown error occurred." << std::endl;
    }

    system("pause");
    return 0;
}

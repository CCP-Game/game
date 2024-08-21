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
void updatePlayerPosition(Room* room, Player &player, int newX, int newY)
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
    //update Rooms player position
    room->updatePlayerPos(newX,newY);
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
Pos getDoorsOpposite(Pos oldPos){
    if(oldPos.getX() ==0){
        return Pos(WIDTH-2,oldPos.getY());
    }else if(oldPos.getY() ==0){
        return Pos(oldPos.getX(),HEIGHT-2);
    }else if(oldPos.getX() == WIDTH-1){
        return Pos(oldPos.getX(), 0);
        //Case where opposite HEIGHT-1
    }else{
        return(Pos(WIDTH/2,1));
    
    }
}
/**
 * setColor
 * This method uses ANSI escape codes to set the output color to console.
 * @param int textColor - this is the color we want has to be > 1
 * @param int bgColor - this is the background colour has to be > 1
 */
void setColour(int textColor, int bgColor = -1) {
    std::cout << "\033[";
    if (textColor != -1) {
        std::cout << textColor;
    }
    if (bgColor != -1) {
        std::cout << ";" << bgColor;
    }
    std::cout << "m";
}
/**
 * resetColor
 * This method resets the output to it's default Colour
 */
void resetColour() {
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
Room* initalize1DMap(int roomLength){
    Room* FirstRoom = new Room(1,0,WIDTH,HEIGHT);
    Room* SecondRoom = new Room(2,1,WIDTH,HEIGHT);
    FirstRoom->initializeRoom(10);
    SecondRoom->initializeRoom(10);
    FirstRoom->setDoor(Pos(WIDTH/2,0),SecondRoom);
    SecondRoom->setDoor(Pos(WIDTH/2,HEIGHT-1),FirstRoom);
    return FirstRoom;
}


void printToConsole(char** display)
{
    system("cls");            // Clear the console
    resetConsoleAttributes(); // Reset to default console attributes
    setCursorPosition(0, 0); //Sets the cursor position..
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            //Adding in colour on the sides
            if(y==0 || x==0 || y==HEIGHT-1 || x==WIDTH-1){
                if(display[y][x]=='D'){
                    setColour(32,1);
                }else{
                    setColour(41);
                    setColour(31);
                }
            //Colour on the inside of walls
            }else if (display[y][x] == 'C'){
                setColour(33);
            }
            std::cout << display[y][x];
            resetColour();
        }
        std::cout << '\n';
       
    }
}
/**
 * main
 * This is the running part of Cavern. Where the game loop is kept.
 */
int main()
{

    int score = 0;
    bool gameRunning = true;
    DWORD lastMoveTime = GetTickCount();
    const DWORD moveDelay = 100; // Adjust this value to change movement speed (lower = faster)
    int newX =0;
    int newY =0;
    srand(static_cast<unsigned>(time(0)));
    Room* currentRoom = initalize1DMap(1);
   
    Player player('P', 7);
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

            if (isKeyPressed('W')) newY--;
            if (isKeyPressed('S')) newY++;
            if (isKeyPressed('A')) newX--;
            if (isKeyPressed('D')) newX++;

            char nextChar = currentRoom->getCharAt(newX, newY);
            //Checking whether is is a valid move
            if(currentRoom->validMove(newX,newY) != false){
            
                //Checking whether we're on a door node, if so change rooms.
                if(currentRoom->isDoorMove(newX,newY)){
                    Room* temprom = currentRoom->getRoom(newX,newY);
                    if(temprom == NULL){
                        std::cout << "NULLL";
                    }else{  
                        std::cout << "NOT NULLL";
                         currentRoom = temprom;
                    }
                   
                    Pos newPos = getDoorsOpposite(Pos(newX,newY));
                    updatePlayerPosition(currentRoom,player,newPos.getX(),newPos.getY());
                    //Sort out where to print player.
                    printToConsole(currentRoom->getDisplay());
                }else{
                    updatePlayerPosition(currentRoom,player,newX,newY);
                }
                
            }
            lastMoveTime = currentTime;
        }
        // Display score and check for quit
        setCursorPosition(0, HEIGHT + 1);
        //Logic for colou given health
        std::cout << "Health " << player.getHealth() << "\n";
        std::cout << "Score: " << score << " | Press Q to quit\n";
        std::cout << "Room: " << currentRoom->getID() <<"\n";

        if (isKeyPressed('Q'))
        {
            gameRunning = false;
        }
        Sleep(10); // Small delay to prevent excessive CPU usage
    }

    return 0;
}
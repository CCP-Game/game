#include "Room.h"
#include "Pos.h"
#include <iostream>
#include <string>
#include <cassert>
/*!
    @file
    @brief Room is our "map" class. This is how our "wordl-map" is divided into segments e.g Rooms
    @author  Sam Budgen, Ben Darlington, Ben Nicholson & Alex Poore.
    @copyright CCP 2024
*/
/*!
    @brief The core methods for this file are InitalizeRoom.
*/
 /*!
    @brief Default constructor
    @param WIDTH [in] The width of the room
    @param HEIGHT [in] The height of the room
 */
Room::Room() : Room(0, 0, WIDTH, HEIGHT)
{
}
/*!
    @brief This is Rooms deconstructor, deallocating the memory assigned to the char**
*/
Room::~Room()
{
    // Free allocated memory for grid
    for (int i = 0; i < height; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;
}
/*!
    @brief This the main constructor for the  first room in a level.
    @param id [in] int, this is the rooms ID (useful for procedural generation later on)
    @param depth [in] int, this is how "deep" our room is how far awy from the 0,0 room
    @param width [in] int, the width of the room
    @param height [in] int, the height of the room.
*/
Room::Room(int id, int depth, int width, int height)
    : id(id), depth(depth), width(width), height(height)
{
    isFinal = false;
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
    playerPos = Pos(0,0);
}
/*!
    @brief method does a deepcopy of a given Room.
    @param other [in] Room& the room we wish to copy.
*/
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

    // Copy other member
    playerPos = Pos(0,0);
}
 /*!
    @brief Overriding the equals operator. Creating a deep copy of the room we're a = b to.
    @param other [in] Room& the room we wanmt to be equal to.
    @return the address of the deepcopied room.
 */
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
    }
    return *this;
}
 /*!
    @brief This method initalizes a room, creating crucial data strcutures.
    @param NUM_COINS [in] int -  this is the number of coins you want in a room.
    @param type [in] char - this is the type of room you want to create.  'b' = Big Room 'v' = Vertical Hallway 'h' = Horizontal Hallway
    @return void
 */
void Room::initializeRoom(int NUM_COINS, char type)
{
    this->type = type;
    // Clear the room first
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            setCharAt(x, y, ' ');
        }
    }

    int minX, maxX, minY, maxY;

    // Create walls
    if (type == 'b') // Big Room
    {
        for (int x = 0; x < WIDTH; x++)
        {
            setCharAt(x, 0, '#');
            setCharAt(x, HEIGHT - 1, '#');
        }
        for (int y = 0; y < HEIGHT; y++)
        {
            setCharAt(0, y, '#');
            setCharAt(WIDTH - 1, y, '#');
        }
        minX = 1;
        maxX = WIDTH - 2;
        minY = 1;
        maxY = HEIGHT - 2;
    }
    else if (type == 'o') // Room with indented corners (slight plus symbol)
    {
        // Set horizontal walls with indented corners
        for (int x = 2; x < WIDTH - 2; x++)
        {
            setCharAt(x, 0, '#'); // Top wall
            setCharAt(x, HEIGHT - 1, '#'); // Bottom wall
        }
        // Set vertical walls with indented corners
        for (int y = 2; y < HEIGHT - 2; y++)
        {
            setCharAt(0, y, '#'); // Left wall
            setCharAt(WIDTH - 1, y, '#'); // Right wall
        }
        // Indented corners
        setCharAt(2, 1, '#'); // Top-left corner
        setCharAt(2, 2, '#'); // Top-left corner
        setCharAt(1, 2, '#'); // Top-left corner
        setCharAt(WIDTH - 3, 1, '#'); // Top-right corner
        setCharAt(WIDTH - 3, 2, '#'); // Top-right corner
        setCharAt(WIDTH - 2, 2, '#'); // Top-right corner
        setCharAt(2, HEIGHT - 3, '#'); // Bottom-left corner
        setCharAt(2, HEIGHT - 2, '#'); // Bottom-left corner
        setCharAt(1, HEIGHT - 3, '#'); // Bottom-left corner
        setCharAt(WIDTH - 3, HEIGHT - 3, '#'); // Bottom-right corner
        setCharAt(WIDTH - 3, HEIGHT - 2, '#'); // Bottom-right corner
        setCharAt(WIDTH - 2, HEIGHT - 3, '#'); // Bottom-right corner
    


        minX = 3;
        maxX = WIDTH - 3;
        minY = 3;
        maxY = HEIGHT - 3;
    }
    else if (type == 'h') // Horizontal Hallway
    {
        int hallwayHeight = 5; // Set the height of the hallway
        int centerY = HEIGHT / 2; // Find the center of the room vertically
        int startY = centerY - hallwayHeight / 2; // Start 2 units above the center

        // Create top and bottom walls
        for (int x = 0; x < WIDTH; x++)
        {
            setCharAt(x, startY, '#');
            setCharAt(x, startY + hallwayHeight - 1, '#');
        }

        // Create end walls
        for (int y = startY + 1; y < startY + hallwayHeight - 1; y++)
        {
            setCharAt(0, y, '#');
            setCharAt(WIDTH - 1, y, '#');
        }
        
        minX = 1;
        maxX = WIDTH - 2;
        minY = startY + 1;
        maxY = startY + hallwayHeight - 2;
    }
    else if (type == 'v') // Vertical Hallway
    {
        int hallwayWidth = 9; // Set the width of the hallway
        int centerX = WIDTH / 2; // Find the center of the room horizontally
        int startX = centerX - hallwayWidth / 2; // Start 2 units left of the center

        // Create left and right walls
        for (int y = 0; y < HEIGHT; y++)
        {
            setCharAt(startX, y, '#');
            setCharAt(startX + hallwayWidth - 1, y, '#');
        }

        // Create end walls
        for (int x = startX + 1; x < startX + hallwayWidth - 1; x++)
        {
            setCharAt(x, 0, '#');
            setCharAt(x, HEIGHT - 1, '#');
        }

        minX = startX + 1;
        maxX = startX + hallwayWidth - 2;
        minY = 1;
        maxY = HEIGHT - 2;
    } else if(type == 'x' || type == 'a'){
        int passageWidth = type == 'x' ? 5 : 9;
        int centerX = WIDTH / 2;
        int centerY = HEIGHT / 2;
        
        int offsetX = (WIDTH - passageWidth)/ 2;
        int offsetY = (HEIGHT - passageWidth)/ 2;

        for (int i = 0; i < WIDTH; i++){
            if (i < offsetX || i >= offsetX + passageWidth){
                setCharAt(i, offsetY - 1, '#');
                setCharAt(i, offsetY + passageWidth, '#');
            }else{
                setCharAt(i, 0, '#');
                setCharAt(i, HEIGHT - 1, '#');
            }
        }

        for (int y = 0; y < HEIGHT; y++){
            if (y < offsetY || y >= offsetY + passageWidth){
                setCharAt(offsetX - 1, y, '#');
                setCharAt(offsetX + passageWidth, y, '#');
            }else{
                setCharAt(0, y, '#');
                setCharAt(WIDTH - 1, y, '#');
            }
        }

        minX = 1;
        maxX = WIDTH - 2;
        minY = 1;
        maxY = HEIGHT - 2;
        //Handles own scatter coins.
        for (int i = 0; i < NUM_COINS; i++){
            int coinX, coinY;
            do
            {
                coinX = rand() % (maxX - minX + 1) + minX;
                coinY = rand() % (maxY - minY + 1) + minY;
            } while (getCharAt(coinX, coinY) != ' ' || coinX <= offsetX && coinY <= offsetY || coinX > offsetX + passageWidth && coinY <= offsetY || coinX <= offsetX && coinY > offsetY + passageWidth ||coinX > offsetX + passageWidth && coinY > offsetY + passageWidth);
                setCharAt(coinX, coinY, 'C');
        }
        return;  
    }else{
        // Handle invalid room type if necessary
        std::cerr << "Invalid room type!" << std::endl;
        return;
    }

    // Scatter coins
    for (int i = 0; i < NUM_COINS; i++)
    {
        int coinX, coinY;
        do
        {
            coinX = rand() % (maxX - minX + 1) + minX;
            coinY = rand() % (maxY - minY + 1) + minY;
        } while (getCharAt(coinX, coinY) != ' ');
        setCharAt(coinX, coinY, 'C');
    }
}
 /*!
    @brief Method updates the players position in the room.
    @param x [in] int, new x-coord
    @param y [in] int, new y-coord
    @return void
 */
void Room::updatePlayerPos(int x, int y){
    playerPos.setXY(x,y);
}
 /*!
    @brief Method checks whether a given move via a player is allowed.
    @details checks whether the new xy coord is on a wall or not.
    @param newx [in] int, new x-coord
    @param newy [in] int, new y-coord
    @return boolean - true or false regardign a valid move or not.
 */
bool Room::validMove(int newx, int newy){
    if(this->getCharAt(newx,newy) =='#'){
        return false;
    }
    if(this->getCharAt(newx,newy) =='L'){
        return false;
    }

    return true;
}
/*!
    @brief Checks whether our move is on a door.
    @param newx [in] int, new x-coord
    @param newy [in] int, new y-coord
    @return Boolean - true or false whether it is a door move or not.
*/
bool Room::isDoorMove(int newx, int newy){
    if(this->getCharAt(newx,newy)=='D'){
        return true;
    }
    return false;
}
/*! 
    @brief Method sets a door at a given position
    @param dPos [in] Pos, the position (xy) of the door.
    @param room [in] Room* - the pointer this room refers to. 
    @return void
*/
void Room::setDoor(Pos dPos, Room* room){
    this->setCharAt(dPos.getX(),dPos.getY(),'D');
    //Inserting this into our arrays
    this->doorPos.push_back(dPos);
    this->doorRooms.push_back(room);
}
/*! 
    @brief This method sets an enemy at a given position within a room
    @param p [in] Pos - the positon (xy) where an enemy will placed
    @param e [in] Enemy* the enemy we're placing in the room.
    @return void
*/
void Room::setEnemy(Pos p, Enemy* e){
    this->setCharAt(p.getX(),p.getY(),e->getSkin());
    e->setPos(p);
    this->enemies.push_back(e);
    // Set the enemy in the grid
}


/*! 
    @brief Method sets the final room.
    @param value [in] bool - the value of the room.
    @return void
*/
void Room::setFinal(bool value)
{
    this->isFinal = value;
}


/*! 
    @brief Method gets the final room.
    @return bool - the value of the room.
*/
bool Room::getFinal()
{
    return this->isFinal;
}

/*! 
    @brief Method gets the type of room.
    @return char - the type of the room.
*/
char Room::getType(){
    return this->type;
}

/*!
    @brief This method gets the enemy at a given position.
    @details this method should only be called when we know an enemy is at a given position, this just refers to the correct enemy.
    @param x [in] int - the x position of the enemy.
    @param y [in] int - the y position of the enemy.
    @return Enemy* - a pointer to the enemy.
*/
Enemy* Room::getEnemyAt(int x, int y){
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->getX() == x && enemies[i]->getY() == y) {
            return enemies[i];
        }
    }
    return NULL;
}
/*!
    @brief Method removes an enemy at a given x-y coord.
    @details Method removes an enemy at a given position. We assume this method is called when we know, for sure, an enemy is at that position.
    @param x [in] int - the x-coord
    @param y [in] int - the y-coord
    @return void
*/
void Room::removeEnemyAt(int x, int y){
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->getX() == x && enemies[i]->getY() == y) {
            enemies.erase(enemies.begin() + i);
            break;
        }
    }
}
/*!
    @brief Method finds the Room associated with a given door.
    @details Since our id's for doors relies on coords. this method should always be called when we know we're at a door.
    @param x [in] the x-coord
    @param y [in] the y-coord
    @return Room* a pointer to the room associated with a given doors pos.
*/
Room* Room::getRoom(int x, int y) const {
        for (size_t i = 0; i < doorPos.size(); ++i) {
            if (doorPos[i].getX() == x && doorPos[i].getY() == y) {
                return doorRooms[i];
            }
        }
        return nullptr; // Return nullptr if not found
}
 /*!
    @brief get the current display for the room.
    @return Char** - returns the display for the room to be printed.
 */
char** Room::getDisplay()
{
    return grid;
}



/*!
    @brief Returns the array of all enemies.
    @return std::vector - the array of enemies.
*/
std::vector<Enemy*> Room::getEnemies(){
    return this->enemies;
}
/*!
    @brief Debug tool to print all the information about our enemies.
    @return String - information regarding our enemies.
*/
std::string Room::enemiesToString(){
    std::string result = "";
    for (size_t i = 0; i < enemies.size(); ++i) {
        result += "Enemy " + std::to_string(i) + ": " + "Skin: " + enemies[i]->getSkin() + " Pos: " + std::to_string(enemies[i]->getX()) + "," + std::to_string(enemies[i]->getY()) + "\n";
    }
    return result;
}
/*!
    @brief Method sets an enemy at a given position.
    @details Method takes an xy coord and sets an enemy at the fgiven postion. 
    @param x [in] int - the x-coord
    @param y [in] int - the y-coord
    @param e [in] Enemy* - the enemy to be placed.
    @return void.
*/
void Room::setEnemyAt(int x, int y, Enemy* e){
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->getX() == x && enemies[i]->getY() == y) {
            enemies[i] = e;
            break;
        }
    }
}
/*!
    @brief The method removes the player from the room when traversing to another room.
    @return void.
*/
void Room::removePlayer(){
    for(int i =0; i < HEIGHT; i++){
        for(int j =0; j < WIDTH; j++){
            if(grid[i][j] == 'P'){
                this->setCharAt(j,i,' ');
            }
        }
    }
}
/*!
    @brief gets the depth of the room. (how far away from 0,0)
    @return int - the depth of the room.
*/
int Room::getLevel()
{
    return depth;
}
/*!
    @brief gets the char at a given position
    @param x [in] int - the x-coord
    @param y [in] int - the y-coord
    @return char - the char at the given position.
*/
char Room::getCharAt(int x, int y) const
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        return grid[y][x];
    }
    return ' ';
}
/*!
    @brief Sets a character at a given position in the room.
    @param x [in] int - the x-coord
    @param y [in] int - the y-coord
    @param c [in] char - the character we wish to set.
    @return void
*/
void Room::setCharAt(int x, int y, char c)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        grid[y][x] = c;
    }
}
/*!
    @brief gets the ID of a room
    @return int - the ID of the room
*/
int Room::getID(){
    return this->id;
}
/*!
    @brief sets the players position in the room.
    @param p [in] Pos - the position xy we're setting the player at.
    @return void
*/
void Room::setPlayerPos(Pos p){
    this->playerPos = p;
}
/*!
    @brief returns the position the player is currently at.
    @return Pos - the pos the player is currently at within our room.
*/
Pos Room::getPlayerPos(){
    return this->playerPos;
}
/*!
    @brief gets information about the room. (E.g the message of Use W A S D ..)
    @return std::string - the information about the room.
*/
std::string Room::getRoomINFO(){
    return this->roomINFO;
}
/*!
    @brief sets the room information.
    @param roomInfo [in] String - the room information
    @return. void
*/
void Room::setRoomINFO(const std::string info){
    this->roomINFO = info;
}
/*!
    @brief sets the key for the room.
    @return void
*/
void Room::setKey()
{
    this->hasKey = true;
    // set put a single key in the room ('K')
    int keyX, keyY;
    if (this->type == 'x'){
        do
        {
            keyX = rand() % (WIDTH - 14) + 7;  
            keyY = rand() % (HEIGHT - 10) + 5; 
        } while (getCharAt(keyX, keyY) != ' ');
        setCharAt(keyX, keyY, 'K');   
    }else{
        do
        {
            keyX = rand() % (WIDTH - 2) + 1;
            keyY = rand() % (HEIGHT - 2) + 1;
        } while (getCharAt(keyX, keyY) != ' ');
        setCharAt(keyX, keyY, 'K');    
    }
}


/*!
    @brief Method checks if the room has a key.
    @return bool - true or false whether the room has a key or not.
*/
bool Room::getKey()
{
    return this->hasKey;
}

/*!


    @brief this method contains our unit test for our room class.
    @return void.
*/
void Room::unittest() {
    std::cout << "Room unittest called!" << std::endl;

    // Test default constructor
    Room roomDefault;
    assert(roomDefault.getID() == 0);
    assert(roomDefault.getLevel() == 0);
    
    // Test parameterized constructor
    Room testRoom(2, 1, 15, 20);
    assert(testRoom.getID() == 2);
    assert(testRoom.getLevel() == 1);

    testRoom.setPlayerPos(Pos(2, 3));
    assert(testRoom.getPlayerPos().getX() == 2);
    assert(testRoom.getPlayerPos().getY() == 3);

    testRoom.updatePlayerPos(4, 5);
    assert(testRoom.getPlayerPos().getX() == 4);
    assert(testRoom.getPlayerPos().getY() == 5);

    // testRoom.removePlayer();
    // assert(testRoom.getCharAt(4, 5) == ' ');


    assert(testRoom.isDoorMove(10, 9) == false);
    testRoom.setDoor(Pos(8, 8), &testRoom);
    assert(testRoom.isDoorMove(8, 8));

    Enemy* testEnemy = new Enemy(Pos(6, 7), 'K', 2);
    std::vector<Enemy*> enemiesList = testRoom.getEnemies();
    
    testRoom.setEnemy(Pos(3, 4), new Enemy(Pos(1, 1), 'E', 2));
    int enemy1X = testRoom.getEnemyAt(3, 4)->getX();
    int enemy1Y = testRoom.getEnemyAt(3, 4)->getY();
    assert(enemy1X == 3);
    assert(enemy1Y == 4);
    
    testRoom.removeEnemyAt(3, 4);
    assert(testRoom.getEnemyAt(3, 4) == nullptr);


    // Test setting and getting characters in the grid
    testRoom.setCharAt(5, 4, 'G');
    assert(testRoom.getCharAt(5, 4) == 'G');
    testRoom.setCharAt(0, 0, '#');
    assert(testRoom.getCharAt(0, 0) == '#');

    // Test validMove method
    assert(testRoom.validMove(5, 5) == true);
    assert(testRoom.validMove(0, 0) == false); // '#' is a wall


    // Test setting and getting room info
    testRoom.setRoomINFO("Test Room Info");
    assert(testRoom.getRoomINFO() == "Test Room Info");

    // Room roomCopy = Room(testRoom);
    // assert(roomCopy.getRoomINFO == "Test Room Info");

    // Doesn't work.
    //testRoom.initializeRoom(5, 'b');
    
    testRoom.getDisplay();
    std::string enemys = testRoom.enemiesToString();

    testRoom.setFinal(true);
    assert(testRoom.getFinal() == true);
    

    std::cout << "All Room tests passed!" << std::endl;

}
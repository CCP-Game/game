#include <iostream>
#include <cstdlib>  // For system("cls")
#include <ctime>    // For delay function
#include "nums.h"
#include "animation.h"

// Function to clear the screen
void clearScreen() {
    std::system("cls");  // On Unix/Linux/OSX use "clear" instead of "cls"
}

// Function to create a delay
void delay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}

// Function to display the player and skeleton on the same line
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

// Function to animate the player moving towards the skeleton
bool animateEncounter(char enemyHead) {
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
    std::string enemyName;
    bool outcome = false;


    if (enemyHead == '+') {
        enemyName = "Additor";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        outcome = generateEquation();

        
    } else if (enemyHead == '-') {
        enemyName = "Subraktor";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        outcome = generateSubtractionEquation();
    } else if (enemyHead == '/') {
        
        enemyName = "Divisor";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        outcome = generateDivisionEquation();
    } else if (enemyHead == '*') {

        enemyName = "Multiplikator";
        std::cout << "\nYou have encountered " << enemyName << "." << std::endl;
        outcome = generateMultiplicationEquation();
    } else {
        enemyName = "Unknown";
    }

    return outcome;
    
}


#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <cstdlib>  // For system("cls")
#include <ctime>    // For delay function

// Function to clear the screen
void clearScreen();

// Function to create a delay
void delay(int milliseconds);

// Function to display the player and skeleton on the same line
void displayScene(int playerPosition, int enemyPosition, char enemyHead);

// Function to animate the player moving towards the skeleton
bool animateEncounter(char enemyHead);

#endif // ANIMATION_H
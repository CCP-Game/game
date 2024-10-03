#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <string>
#include <vector>

//displayCavernAnimation
void displayCavernAnimation();
// Function to display ASCII art for game over animation
void displayGameOverAnimation();

// Function to delay the display of animations
void delayDisplay(int milliseconds);

void aniunittest();

// Cave and Game Over ASCII art arrays
extern const std::string cavernArt[];
extern const std::string gameOverArt[];

#endif // ANIMATIONS_H
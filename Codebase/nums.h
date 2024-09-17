#ifndef NUMS_H
#define NUMS_H

#include <string>

// ASCII art for numbers and operations
extern const char *ASCII_NUMBERS[];

// Function to get user input
int getUserInput();

// Function to print the ASCII representation of numbers and operators
void printNums(const std::string &nums);

// Function to generate random numbers within a specified range
int improvedRandom(int min, int max);

// Functions to generate equations and validate answers
bool generateEquation();
bool generateSubtractionEquation();
bool generateMultiplicationEquation();
bool generateDivisionEquation();
int evaluateExpression(const std::string &expression);

/*!
 * @brief Generates a more complex equation with multiple operations, prints it in ASCII art, and checks if the user's answer is correct.
 *
 * Generates a random sequence of numbers and operations (+, -, *, /), prints the equation in ASCII art,
 * and evaluates the user's input.
 *
 * @return Returns true if the user's answer is correct, false otherwise.
 */
bool generateComplexEquation();


#endif // NUMS_H
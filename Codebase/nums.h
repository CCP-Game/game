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
std::string generateEquation();
std::string generateSubtractionEquation();
std::string generateMultiplicationEquation();
std::string generateDivisionEquation();

#endif // NUMS_H

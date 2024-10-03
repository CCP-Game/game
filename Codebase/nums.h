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

// Functions to generate random operations and evaluate expressions
char generateRandomOperation();  // Generates a random operator: '+', '-', '*', '/'
int evaluate(int num1, int num2, char op);  // Evaluates an expression with the given operator

// Functions to generate equations and validate answers
bool generateEquation();
bool generateSubtractionEquation();
bool generateMultiplicationEquation();
bool generateDivisionEquation();
bool generateComplexEquation(); // New method for complex equations

// Unit test function for nums
void numsunittest();

#endif // NUMS_H

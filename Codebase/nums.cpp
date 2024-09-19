#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "nums.h"
#include <cassert>
#include <iostream>
#include <functional>


/*!
 * @brief Array of ASCII art representations for digits 0-9 and some symbols.
 */
const char *ASCII_NUMBERS[] = {
    "  ___  \n"
    " / _ \\ \n"
    "| | | |\n"
    "| | | |\n"
    "| |_| |\n"
    " \\___/ \n",

    " __ \n"
    "/_ |\n"
    " | |\n"
    " | |\n"
    " | |\n"
    " |_|\n",

    " ___  \n"
    "|__ \\ \n"
    "   ) |\n"
    "  / / \n"
    " / /_ \n"
    "|____|\n",

    " ____  \n"
    "|___ \\ \n"
    "  __) |\n"
    " |__ < \n"
    " ___) |\n"
    "|____/ \n",

    " _  _   \n"
    "| || |  \n"
    "| || |_ \n"
    "|__   _|\n"
    "   | |  \n"
    "   |_|  \n",

    " _____ \n"
    "| ____|\n"
    "| |__  \n"
    "|___ \\ \n"
    " ___) |\n"
    "|____/ \n",

    "   __  \n"
    "  / /  \n"
    " / /_  \n"
    "| '_ \\ \n"
    "| (_) |\n"
    " \\___/ \n",

    " ______ \n"
    "|____  |\n"
    "    / / \n"
    "   / /  \n"
    "  / /   \n"
    " /_/    \n",

    "  ___  \n"
    " / _ \\ \n"
    "| (_) |\n"
    " > _ < \n"
    "| (_) |\n"
    " \\___/ \n",

    "  ___  \n"
    " / _ \\ \n"
    "| (_) |\n"
    " \\__, |\n"
    "   / / \n"
    "  /_/  \n",

    "    _   \n"
    "  _| |_ \n"
    " |_   _|\n"
    "   |_|  \n"
    "        \n"
    "        \n",

    "         \n"
    "         \n"
    "  ______ \n"
    " |______|\n"
    "         \n"
    "         \n",

    "      __\n"
    "     / /\n"
    "    / / \n"
    "   / /  \n"
    "  / /   \n"
    " /_/    \n",

    "       \n"
    " __  __\n"
    " \\ \\/ /\n"
    "  >  < \n"
    " /_/\\_\\\n"
    "       \n",

    "         \n"
    "  ______ \n"
    " |______|\n"
    "  ______ \n"
    " |______|\n"
    "         \n",

};

/*!
 * @brief Prompts the user to enter an integer and returns their input.
 *
 * This function displays a prompt to the user asking for an integer input and
 * then reads and returns the value entered by the user.
 *
 * @return The integer input by the user.
 */
int getUserInput()
{
    int userAnswer;
    std::cout << "Enter your answer: ";
    std::cin >> userAnswer;
    return userAnswer;
}

/*!
 * @brief Prints the given string as ASCII art.
 *
 * This function takes a string containing digits and/or symbols and prints
 * each character in its corresponding ASCII art form. The ASCII art is
 * represented by an array of strings where each index corresponds to a character.
 *
 * @param nums [in] The string containing digits and symbols to be converted to ASCII art.
 */
void printNums(const std::string &nums)
{
    // Prepare a vector to hold each line of the final ASCII art
    std::vector<std::string> lines(6, "");

    // Process each character in the input string
    for (char ch : nums)
    {
        int index = -1;
        if (ch >= '0' && ch <= '9')
        {
            index = ch - '0';
        }
        else if (ch == '+')
        {
            index = 10;
        }
        else if (ch == '-')
        {
            index = 11;
        }
        else if (ch == '/')
        {
            index = 12;
        }
        else if (ch == '*')
        {
            index = 13;
        }
        else if (ch == '=')
        {
            index = 14;
        }
        else if (ch == ' ')
        {
            // Add spaces between characters for readability
            for (int i = 0; i < 6; ++i)
            {
                lines[i] += "  "; // Two spaces for separation
            }
            continue;
        }

        if (index != -1)
        {
            // Append the corresponding ASCII art to each line
            const char *ascii = ASCII_NUMBERS[index];
            std::string line;
            int lineIndex = 0;

            for (const char *p = ascii; *p; ++p)
            {
                if (*p == '\n')
                {
                    lines[lineIndex] += line + ' ';
                    line.clear();
                    ++lineIndex;
                }
                else
                {
                    line += *p;
                }
            }
        }
    }

    // Print each line of the final ASCII art
    for (const std::string &line : lines)
    {
        std::cout << line << std::endl;
    }
}

/*!
 * @brief Generates a random integer between a given minimum and maximum.
 *
 * Uses a Mersenne Twister engine to generate a uniformly distributed random integer.
 *
 * @param min [in] The minimum value of the random integer (inclusive).
 * @param max [in] The maximum value of the random integer (inclusive).
 *
 * @return A random integer between min and max.
 */
int improvedRandom(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

/*!
 * @brief Generates an addition equation, prints it in ASCII art, and checks if the user's answer is correct.
 *
 * Generates two random numbers, calculates their sum, and prints the equation in ASCII art.
 * Prompts the user to enter the answer and returns whether it is correct.
 *
 * @return Returns true if the user's answer is correct, false otherwise.
 */
bool generateEquation()
{
    int num1 = improvedRandom(1, 100); // Generate first number
    int num2 = improvedRandom(1, 100); // Generate second number
    int result = num1 + num2;

    // Print the equation
    std::string equation = std::to_string(num1) + "+" + std::to_string(num2) + "=";
    printNums(equation);

    int answer = getUserInput();
    return answer == result;
}

/*!
 * @brief Generates a subtraction equation, prints it in ASCII art, and checks if the user's answer is correct.
 *
 * Generates two random numbers, calculates their difference, and prints the equation in ASCII art.
 * Prompts the user to enter the answer and returns whether it is correct.
 *
 * @return Returns true if the user's answer is correct, false otherwise.
 */
bool generateSubtractionEquation()
{
    int num1 = improvedRandom(1, 100);  // Generate first number
    int num2 = improvedRandom(1, num1); // Generate second number
    int result = num1 - num2;

    // Print the equation
    std::string equation = std::to_string(num1) + "-" + std::to_string(num2) + "=";
    printNums(equation);

    int answer = getUserInput();
    return answer == result;
}

/*!
 * @brief Generates a multiplication equation, prints it in ASCII art, and checks if the user's answer is correct.
 *
 * Generates two random numbers, calculates their product, and prints the equation in ASCII art.
 * Prompts the user to enter the answer and returns whether it is correct.
 *
 * @return Returns true if the user's answer is correct, false otherwise.
 */
bool generateMultiplicationEquation()
{
    int num1 = improvedRandom(1, 10); // Generate first number
    int num2 = improvedRandom(1, 15); // Generate second number
    int result = num1 * num2;

    // Print the equation
    std::string equation = std::to_string(num1) + "*" + std::to_string(num2) + "=";
    printNums(equation);

    int answer = getUserInput();
    return answer == result;
}

/*!
 * @brief Generates a division equation, prints it in ASCII art, and checks if the user's answer is correct.
 *
 * Generates a divisor and a dividend (multiple of the divisor), calculates their quotient, and prints
 * the equation in ASCII art. Prompts the user to enter the answer and returns whether it is correct.
 *
 * @return Returns true if the user's answer is correct, false otherwise.
 */
bool generateDivisionEquation()
{
    int num2 = improvedRandom(1, 10);        // Generate divisor
    int num1 = num2 * improvedRandom(1, 10); // Generate dividend as a multiple of num2
    int result = num1 / num2;

    // Print the equation
    std::string equation = std::to_string(num1) + "/" + std::to_string(num2) + "=";
    printNums(equation);

    int answer = getUserInput();
    return answer == result;
}


void numsunittest()
{
    std::cout << "Player unittest called!" << std::endl;

    assert(improvedRandom(4, 4) == 4);


    
    // //EquationGenerator generator;

    // // Simulate correct user input
    // auto mockCorrectInput = []() -> int {
    //     return 5; // Mocked input value, assuming the expected result is 5
    // };

    // // Simulate incorrect user input
    // auto mockIncorrectInput = []() -> int {
    //     return 3; // Mocked wrong input value
    // };

    // // Test case 1: User gives the correct answer
    // bool resultCorrect = generateDivisionEquation();
    // assert(resultCorrect == true); // Expect true for correct input

    // // Test case 2: User gives the wrong answer
    // bool resultIncorrect = generateDivisionEquation();
    // assert(resultIncorrect == false); // Expect false for incorrect input
    std::cout << "All Player tests passed!" << std::endl;
}
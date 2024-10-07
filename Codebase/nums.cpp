#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <sstream>
#include <stack>
#include "nums.h"
#include <cassert>
#include <iostream>
#include <functional>
#include <sstream>

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

    "    __   \n"
    "   / /   \n"
    "   | |   \n"
    "   | |   \n"
    "   | |   \n"
    "    \\_\\  \n",

    "    __    \n"
    "    \\ \\   \n"
    "    | |   \n"
    "    | |   \n"
    "    | |   \n"
    "   /_/    \n",

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
    while (true)
    {
        std::cout << "Enter your answer: ";
        std::cin >> userAnswer;

        // Check if the input was valid
        if (std::cin.fail())
        {
            std::cin.clear();                                                   // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter an integer.\n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard any remaining input
            return userAnswer;                                                  // Valid input, return the answer
        }
    }
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
        else if (ch == '(')
        {
            index = 15;
        }
        else if (ch == ')')
        {
            index = 16;
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
 * @brief Generates a complex equation, prints it in ASCII art, and checks if the user's answer is correct.
 *
 * The equation is formed by two random sub-equations inside brackets, each using random operations.
 * A random operation is selected to combine these sub-equations, and the result is calculated.
 *
 * @return Returns true if the user's answer is correct, false otherwise.
 */
bool generateComplexEquation()
{
    // Generate random numbers for the first sub-equation
    int num1_1 = improvedRandom(2, 10);
    int num1_2 = improvedRandom(2, 10);
    char op1;
    int result1;

    // Choose a random operation for the first sub-equation
    int randomOp1 = improvedRandom(0, 2);
    if (randomOp1 == 0)
    {
        num1_1 = improvedRandom(2, 20);
        num1_2 = improvedRandom(2, 20);
        op1 = '+';
        result1 = num1_1 + num1_2;
    }
    else if (randomOp1 == 1)
    {
        num1_1 = improvedRandom(2, 50);
        num1_2 = improvedRandom(2, num1_1); // Ensures positive result
        op1 = '-';
        result1 = num1_1 - num1_2;
    }
    else if (randomOp1 == 2)
    {
        num1_1 = improvedRandom(2, 10);
        num1_2 = improvedRandom(2, 10);
        op1 = '*';
        result1 = num1_1 * num1_2;
    }
    else
    { 
        num1_2 = improvedRandom(2, 10);
        num1_1 = num1_2 * improvedRandom(2, 10); // Ensures clean division
        op1 = '/';
        result1 = num1_1 / num1_2;
    }

    // Generate random numbers for the second sub-equation
    int num2_1 = 0;
    int num2_2 = 0;
    char op2 = ' ';
    int result2 = 0;

    // Choose a random operation for the second sub-equation
    int randomOp2 = improvedRandom(0, 2);
    if (randomOp2 == 0)
    {
        num2_1 = improvedRandom(2, 20);
        num2_2 = improvedRandom(2, 20);
        op2 = '+';
        result2 = num2_1 + num2_2;
    }
    else if (randomOp2 == 1)
    {
        num2_1 = improvedRandom(2, 50);
        num2_2 = improvedRandom(2, num2_1); // Ensures positive result
        op2 = '-';
        result2 = num2_1 - num2_2;
    }
    else if (randomOp2 == 2)
    {
        num2_1 = improvedRandom(2, 10);
        num2_2 = improvedRandom(2, 10);
        op2 = '*';
        result2 = num2_1 * num2_2;
    }
    else
    {
        num2_2 = improvedRandom(2, 10);
        num2_1 = num2_2 * improvedRandom(2, 10); // Ensures clean division
        op2 = '/';
        result2 = num2_1 / num2_2;
    }

    // Choose a random operation to combine the two sub-equations
    char finalOp;
    int finalResult;
    int randomFinalOp = improvedRandom(0, 3);

    if (randomFinalOp == 0)
    {
        finalOp = '+';
        finalResult = result1 + result2;
    }
    else if (randomFinalOp == 1)
    {
        finalOp = '-';
        if (result1 >= result2)
        {
            finalResult = result1 - result2;
        }
        else
        {
            finalResult = result2 - result1; // Swapping to ensure a positive result
            std::swap(result1, result2); // Also swap the operands for display
            std::swap(num1_1, num2_1);  // Ensure the equation looks correct after swapping
            std::swap(num1_2, num2_2);
        }
    }
    else if (randomFinalOp == 2)
    {
        finalOp = '*';
        finalResult = result1 * result2;
    }
    else // Division between two sub-equations
    { 
        finalOp = '/';
        
        // Ensure clean division by checking if result1 is divisible by result2
        if (result2 != 0 && result1 % result2 == 0)
        {
            finalResult = result1 / result2;
        }
        else
        {
            // Recalculate result2 to be a divisor of result1
            result2 = improvedRandom(2, result1); // Ensure result2 is less than or equal to result1
            while (result1 % result2 != 0) // Keep generating result2 until it's a divisor of result1
            {
                result2 = improvedRandom(2, result1);
            }
            finalResult = result1 / result2;
        }
    }

    // Print the complex equation
    std::string equation = "(" + std::to_string(num1_1) + " " + op1 + " " + std::to_string(num1_2) + ") " + finalOp +
                           " (" + std::to_string(num2_1) + " " + op2 + " " + std::to_string(num2_2) + ") = ";
    printNums(equation); // Print the equation in ASCII art

    // Get the user's answer and check if it's correct
    int answer = getUserInput();
    return answer == finalResult;
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
    int num1 = improvedRandom(1, 50); // Generate first number
    int num2 = improvedRandom(1, 30); // Generate second number
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
    int num1 = improvedRandom(2, 50);  // Generate first number
    int num2 = improvedRandom(2, num1); // Generate second number
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
    int num1 = improvedRandom(1, 5); // Generate first number
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

/*!
 * @brief Generates a more complex equation with multiple operations, prints it in ASCII art, and checks if the user's answer is correct.
 *
 * Generates a random sequence of numbers and operations (+, -, *, /), prints the equation in ASCII art,
 * and evaluates the user's input.
 *
 * @return Returns true if the user's answer is correct, false otherwise.
 */
// bool generateComplexEquation()
// {
//     int expressions =
//     int order = rand() % 4 + 1;

//     if()
// }

/*!
    @brief runs unittest for the other methods.
    @return. void
*/
void numsunittest()
{
    std::cout << "Player unittest called!" << std::endl;

    assert(improvedRandom(4, 4) == 4);

    std::istringstream mockInput("5\n");
    std::streambuf *originalCinBuffer = std::cin.rdbuf();
    std::cin.rdbuf(mockInput.rdbuf());
    int res = getUserInput();
    assert(res == 5);
    assert(res != 3);

    std::istringstream mockInput1("201\n");
    std::streambuf *CinBuffer1 = std::cin.rdbuf();
    std::cin.rdbuf(mockInput1.rdbuf());
    bool resPlus = generateEquation();
    assert(resPlus == false);

    std::istringstream mockInput2("101\n");
    std::streambuf *CinBuffer2 = std::cin.rdbuf();
    std::cin.rdbuf(mockInput1.rdbuf());
    bool resMin = generateMultiplicationEquation();
    assert(resMin == false);

    std::istringstream mockInput3("151\n");
    std::streambuf *CinBuffer3 = std::cin.rdbuf();
    std::cin.rdbuf(mockInput1.rdbuf());
    bool resMult = generateMultiplicationEquation();
    assert(resMult == false);

    std::istringstream mockInput4("200\n");
    std::streambuf *CinBuffer4 = std::cin.rdbuf();
    std::cin.rdbuf(mockInput4.rdbuf());
    bool resDiv = generateDivisionEquation();
    assert(resDiv == false);

    std::cout << "All Player tests passed!" << std::endl;
}
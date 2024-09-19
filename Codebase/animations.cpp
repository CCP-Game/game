#include <iostream>
#include <thread>
#include <chrono>
#include "animations.h"

 const std::string cavernArt[] = {

  "⢀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀ ",
    "⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
    "⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
    "⠀⠘⠛⠛⠛⠿⣿⣿⣿⣿⠛⠿⠿⠿⠋⣿⣿⠿⢿⡇⠈⢻⣿⣿⠟⠋⠁⠀⠀⠘⠛⠛⠛⠿⣿⣿⣿⣿⠛⠿⠿⠿⠋⣿⣿⠿⢿⡇⠈⢻⣿⣿⠟⠋⠁  ⣿⠟⠋⠁⠀⠀⠘⠛⠛⠛⠿⣿⣿⣿⣿⠛⠿⠿⠿⠋⣿⣿",
    "⠀⠀⠀⠀⠀⠀⠈⣿⣿⡿⠀⠀⠀⠀⠀⢹⡟⠀⠸⠃⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⡿⠀⠀⠀⠀⠀⢹⡟⠀⠸⠃⠀⠀⠈⠁                          ",
    "⠀⠀⠀⠀⠀⠀⠀⢸⣿⠇⠀⠀⠀⠀⠀⠸⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠇⠀⠀⠀⠀⠀                                        ",
    "⠀⠀⠀⠀⠀⠀⠀⠈⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                              ",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠁                                                                                ",
    " ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓███████▓▒░░▒▓███████▓▒░  ",
    "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░",
    "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░",
    "░▒▓█▓▒░      ░▒▓████████▓▒░░▒▓█▓▒▒▓█▓▒░░▒▓██████▓▒░ ░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░",
    "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░",
    "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░",
    " ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░  ░▒▓██▓▒░  ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░"
    "                                                                                            ",
    "                                                                                            ",
    "⠀⢸⣷⣦⡀⠀⠀⣠⣾⣷⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣾⣿⣿⣿⣷⡀⣦⡀⠀⠀⣠⣾⣷⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣾⣿⣿⣿⣷⡀⠀  ⣿⣿⣷⡀⣦⡀⠀⠀⣠⣾⣷⣶   ⣿⣿⣿⣷⡀⣦⡀",
    "⠀⢸⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
    "⠀⠈⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⠉⠉⠉⠉⠉⠉⠉⠁⠉⠉⠉",
};
const std::string gameOverArt[] = {
    "⢀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀ ",
    "⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
    "⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
    "⠀⠘⠛⠛⠛⠿⣿⣿⣿⣿⠛⠿⠿⠿⠋⣿⣿⠿⢿⡇⠈⢻⣿⣿⠟⠋⠁⠀⠀⠘⠛⠛⠛⠿⣿⣿⣿⣿⠛⠿⠿⠿⠋⣿⣿⠿⢿⡇⠈⢻⣿⣿⠟⠋⠁  ⣿⠟⠋⠁⠀⠀⠘⠛⠛⠛⠿⣿⣿⣿⣿⠛⠿⠿⠿⠋⣿⣿⠿⢿⣿⠛⠿⠿⠿⠋⣿⣿⠿⢿",
    "⠀⠀⠀⠀⠀⠀⠈⣿⣿⡿⠀⠀⠀⠀⠀⢹⡟⠀⠸⠃⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⡿⠀⠀⠀⠀⠀⢹⡟⠀⠸⠃⠀⠀⠈⠁                          ",
    "⠀⠀⠀⠀⠀⠀⠀⢸⣿⠇⠀⠀⠀⠀⠀⠸⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠇⠀⠀⠀⠀⠀                                        ",
    "⠀⠀⠀⠀⠀⠀⠀⠈⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                              ",
    "⠀⠀⠀⠀⠀⠀⠀⠀⠁                                                                                ",
    "░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░      ░▒▓███████▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓███████▓▒░",
    "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░",
    "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░",
    " ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓██████▓▒░ ░▒▓█▓▒░░▒▓█▓▒░",
    "   ░▒▓█▓▒░   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░",
    "   ░▒▓█▓▒░   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░",
    "   ░▒▓█▓▒░    ░▒▓██████▓▒░ ░▒▓██████▓▒░       ░▒▓███████▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓███████▓▒░",
    "                                                                                            ",
    "                                                                                            ",
    "⠀⢸⣷⣦⡀⠀⠀⣠⣾⣷⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣾⣿⣿⣿⣷⡀⣦⡀⠀⠀⣠⣾⣷⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣾⣿⣿⣿⣷⡀⠀  ⣿⣿⣷⡀⣦⡀⠀⠀⣠⣾⣷⣶   ⣿⣿⣿⣷⡀⣦⡀⠀⠀⣠⣾⣷⣶⣤⣀⣠⣾⣤⣀",
    "⠀⢸⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
    "⠀⠈⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉",
};


/*!
    @brief displays the Cavern logo.
    @param roomInfo string cavernArt[] - the ascii acrt for the Cavern screen.
    @return. void
*/
void displayCavernAnimation(const std::string art[])
{

    int rows = sizeof(gameOverArt) / sizeof(gameOverArt[0]);
    int duration = 2000; // 2 seconds in milliseconds
    // Find the maximum length of the lines
    int maxLength = 0;
    for (int i = 0; i < rows; ++i) {
        if (gameOverArt[i].length() > maxLength) {
            maxLength = gameOverArt[i].length();
        }
    }


    //this possible /0 error needs dealing with...
    if(maxLength == 0){
        return;
    }

    int delay = duration / maxLength; // Delay to fit within the total duration

    // Animate each step, displaying more of the text progressively
    for (int step = 0; step <= maxLength; ++step) {
        for (int i = 0; i < rows; ++i) {
            std::cout << gameOverArt[i].substr(0, step) << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        std::cout << "\033[H\033[J"; // Clear the screen for animation effect
    }

    std::cout.flush();
}

/*!
    @brief displays the game over animation.
    @return. void
*/
void displayGameOverAnimation()
{
    int rows = sizeof(cavernArt) / sizeof(cavernArt[0]);

    // Calculate the maximum length of the longest line
    int maxLength = 0;
    for (int i = 0; i < rows; ++i) {
        if (cavernArt[i].length() > maxLength) {
            maxLength = cavernArt[i].length();
        }
    }

    if(maxLength == 0){
        return;
    }
    //this possible /0 error needs dealing with...
    int totalDuration = 2000; // 2 seconds in milliseconds
    int delay = totalDuration / maxLength; // Delay based on the longest line

    for (int step = 0; step <= maxLength; ++step) {
        for (int i = 0; i < rows; ++i) {
            std::cout << cavernArt[i].substr(0, step); // Print up to the current step
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delay)); // Wait
        std::cout << "\033[H\033[J"; // Clear the screen for animation effect
    }

    std::cout.flush();
}

/*!
    @brief runs unittest for the other methods.
    @return. void
*/
void aniunittest()
{
    // Not ideal but currently just running the animations to make sure they don't throw any errors.
    displayCavernAnimation(cavernArt);
    displayCavernAnimation(gameOverArt);
    displayGameOverAnimation();
}

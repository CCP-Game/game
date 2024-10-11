#include <iostream>
#include <thread>
#include <chrono>
#include "Animations.h"

 const std::string cavernArt[] = {
    "                                                          ", 
    "   _______  _______           _______  _______  _         ",
    "  (  ____ \\(  ___  )|\\     /|(  ____ \\(  _____)( )    /|  ",
    "  | (    \\/| (   ) || )   ( || (    \\/| (    )||  \\  ( |  ",
    "  | |      | (___) || |   | || (__    | (____)||   \\ | |  ",
    "  | |      |  ___  |( (   ) )|  __)   |     __)| (\\ \\) |  ",
    "  | |      | (   ) | \\ \\_/ / | (      | (\\ (   | | \\   |  ",
    "  | (____/\\| )   ( |  \\   /  | (____/\\| ) \\ \\__| )  \\  |  ",
    "  (_______/|/     \\|   \\_/   (_______/|/   \\__/|/    )_)  "
};
// const std::string gameOverArt[] = {
//         "_  /)",
//                  "mo / )                      ",
//                  "|/)\)",
//                   "/\_",
//                   "\__|=",
//                  "(    )",
//                  "__)(__",
//            "_____/      \\_____",
//           "|  _     ___   _   ||",
//           "| | \     |   | \  ||",
//           "| |  |    |   |  | ||",
//           "| |_/     |   |_/  ||",
//           "| | \     |   |    ||",
//           "| |  \    |   |    ||",
//           "| |   \. _|_. | .  ||",
//           "|                  ||",
//           "|  bad adventurer  ||",
//           "|                  ||",
//   "*       | *   **    * **   |**      **",
//    "\))ejm97/.,(//,,..,,\||(,,.,\\,.((//",
// };

const std::string gameOverArt[] = {
    " ,--.   ,--..-'),-----.  ,--. ,--.    ",
    "   \\  `.'  /( OO'  .-.  ' |  | |  |    ",
    " .-')     / /   |  | |  | |  | | .-')  ",
    "(OO  \\   /  \\_) |  |\\|  | |  |_|( OO ) ",
    " |   /  /\\_   \\ |  | |  | |  | | `-' / ",
    " `-./  /.__)   `'  '-'  '('  '-'(_.-'  ",
    "   `--'          `-----'   `-----'     ",
    " _ .-') _              ('-.  _ .-') _  ",
    "( (  OO) )           _(  OO)( (  OO) ) ",
    " \\     .'_   ,-.-') (,------.\\     .'_ ",
    " ,`'--..._)  |  |OO) |  .---',`'--..._)",
    " |  |  \\  '  |  |  \\ |  |    |  |  \\  '",
    " |  |   ' |  |  |(_/(|  '--. |  |   ' |",
    " |  |   / : ,|  |_.' |  .--' |  |   / :",
    " |  '--'  /(_|  |    |  `---.|  '--'  /",
    " `-------'   `--'    `------'`-------'  "
};


/*!
    @brief displays the Cavern logo.
    @param roomInfo string cavernArt[] - the ascii acrt for the Cavern screen.
    @return. void
*/
void displayGameOverAnimation()
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
       system("cls");;
    }

    std::cout.flush();
}

/*!
    @brief displays the game over animation.
    @return. void
*/
void displayCavernAnimation()
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
    int totalDuration = 1000; // 2 seconds in milliseconds
    int delay = totalDuration / maxLength; // Delay based on the longest line

    for (int step = 0; step <= maxLength; ++step) {
        for (int i = 0; i < rows; ++i) {
            std::cout << cavernArt[i].substr(0, step); // Print up to the current step
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delay)); // Wait
        system("cls");
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
    // displayCavernAnimation();
    // displayCavernAnimation();
    // displayGameOverAnimation();
}

#include <iostream>
#include <string>
#include <vector>

const char* ASCII_NUMBERS[] = {
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

    "       \n"
    "  _  _ \n"
    " | || |\n"
    " | || | \n"
    " |__   _|\n"
    "    |_| \n",

    "       \n"
    "  _____\n"
    " |____ |\n"
    "     / / \n"
    "    /_/ \n"
    "   |_|  \n",

    "       \n"
    "       \n"
    "    _  \n"
    "  _(_)_\n"
    " (_)___\n"
    "       \n",

    "  _____\n"
    " |  __ \\\n"
    " | |__) |\n"
    " |  ___/\n"
    " | |    \n"
    " |_|   \n",

    "   _  _\n"
    "  (_)/ /\n"
    "    / /\n"
    "   / /\n"
    "  /_/\n"
    "  /_/ \n"
};

void printNums(const std::string& nums) {
    std::vector<std::string> lines(6);

    for (char ch : nums) {
        if ((ch >= '0' && ch <= '9') || ch == '+' || ch == '-' || ch == '/' || ch == '*') {
            int index;
            if (ch >= '0' && ch <= '9') {
                index = ch - '0';
            } else {
                switch (ch) {
                    case '+': index = 10; break;
                    case '-': index = 11; break;
                    case '/': index = 12; break;
                    case '*': index = 13; break;
                    default: continue;
                }
            }

            const char* ascii = ASCII_NUMBERS[index];
            std::string line;
            int lineIndex = 0;

            for (const char* p = ascii; *p; p++) {
                if (*p == '\n') {
                    lines[lineIndex] += line + ' '; // Add a space after each number/symbol for better readability
                    lineIndex++;
                    line.clear();
                } else {
                    line += *p;
                }
            }
        }
    }

    for (const std::string& line : lines) {
        std::cout << line << std::endl;
    }
}

int main() {
    std::string input = "11+19-3/2*4";
    printNums(input);
    return 0;
}

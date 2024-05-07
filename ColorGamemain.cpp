#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <ncurses.h>

// Define colors
enum Colors {
    RED, ORANGE, WHITE, BLACK, GREEN, BLUE, BROWN, PURPLE, CYAN, YELLOW, PINK, MAGENTA
};

std::vector<std::string> colors = {"Red", "Orange", "White", "Black", "Green", "Blue", "Brown", "Purple", "Cyan", "Yellow", "Pink", "Magenta"};
int timer = 60;
int score = 0;
std::string displayed_word_color = "";

// Function to start the game
void startGame() {
    if (timer == 60) {
        // Start the countdown
        startCountDown();
        // Display a random word with a random color
        displayed_word_color = colors[rand() % colors.size()];
        attron(COLOR_PAIR(RED + rand() % (MAGENTA - RED + 1)));
        printw("%s\n", colors[rand() % colors.size()].c_str());
        attroff(COLOR_PAIR(RED + rand() % (MAGENTA - RED + 1)));
    }
}

// Function to reset the game
void resetGame() {
    timer = 60;
    score = 0;
    displayed_word_color = "";
    printw("Your Score: %d\n", score);
    printw("Game Ends in: -\n");
    clrtoeol();
}

// Function to start the countdown
void startCountDown() {
    if (timer >= 0) {
        printw("Game Ends in: %ds\n", timer--);
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        startCountDown();
        if (timer == -1) {
            printw("Game Over!!!\n");
            clrtoeol();
        }
    }
}

// Function to display the next word
void displayNextWord() {
    if (timer > 0) {
        std::string input;
        printw("\nEnter the color of the word: ");
        refresh();
        echo();
        getstr(input);
        noecho();
        if (input == displayed_word_color) {
            score++;
            printw("Your Score: %d\n", score);
            clrtoeol();
        }
        displayed_word_color = colors[rand() % colors.size()];
        attron(COLOR_PAIR(RED + rand() % (MAGENTA - RED + 1)));
        printw("%s\n", colors[rand() % colors.size()].c_str());
        attroff(COLOR_PAIR(RED + rand() % (MAGENTA - RED + 1)));
    }
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Initialize ncurses
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_CYAN, COLOR_BLACK);
    init_pair(9, COLOR_RED, COLOR_WHITE);
    init_pair(10, COLOR_GREEN, COLOR_WHITE);
    init_pair(11, COLOR_YELLOW, COLOR_WHITE);
    init_pair(12, COLOR_BLUE, COLOR_WHITE);
    init_pair(13, COLOR_MAGENTA, COLOR_WHITE);

    // Display game description
    printw("Game Description: Enter the color of the words displayed below.\n");
    printw("And Keep in mind not to enter the word text itself.\n");

    // Game loop
    while (true) {
        startGame();
        displayNextWord();
        resetGame();
    }

    // End ncurses
    endwin();
    return 0;
}
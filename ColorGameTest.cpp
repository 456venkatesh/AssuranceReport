#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <thread>
#include "color_game.hpp"  // Assuming the provided code is saved in a file named color_game.hpp

using namespace std;
using ::testing::HasSubstr;

// Mock function for the NCurses printw function
int mock_printw(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int ret = vwprintw(stdscr, format, args);
    va_end(args);
    return ret;
}

class ColorGameTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        // Redirect printw calls to the mock function
        original_printw = printw;
        printw = mock_printw;
    }

    virtual void TearDown() {
        // Restore the original printw function
        printw = original_printw;
    }

    // Original printw function
    int (*original_printw)(const char*, ...);
};

// Test startGame function
TEST_F(ColorGameTest, StartGame) {
    // Call startGame function
    startGame();

    // Wait for a second to allow the timer to decrease
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Verify if printw is called to display the game description
    EXPECT_CALL(mock_printw, _)
        .WillOnce(HasSubstr("Game Description"));
}

// Test resetGame function
TEST_F(ColorGameTest, ResetGame) {
    // Call resetGame function
    resetGame();

    // Verify if printw is called to display the score and game ends message
    EXPECT_CALL(mock_printw, _)
        .WillOnce(HasSubstr("Your Score"))
        .WillOnce(HasSubstr("Game Ends in"));
}

// Test displayNextWord function
TEST_F(ColorGameTest, DisplayNextWord) {
    // Call displayNextWord function
    displayNextWord();

    // Verify if printw is called to prompt the user to enter the color of the word
    EXPECT_CALL(mock_printw, _)
        .WillOnce(HasSubstr("Enter the color of the word"));

    // Manually input a color and verify if the score is updated
    string input_color = "Red";
    stringstream ss;
    ss << input_color << "\n";
    string input = ss.str();
    setbuf(stdin, NULL);
    write(fileno(stdin), input.c_str(), input.size());
    displayNextWord();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
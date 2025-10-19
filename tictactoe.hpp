#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include "players.hpp"
using namespace std;

class tictactoe{
    private:
    vector<string> board = {"-","-","-","-","-","-","-","-","-"};
    map<int, string, greater<int>> leaderboard = {{7, "Maddy"}, {6, "Zac"}, {99, "Bingo"}, {80, "Wahoooo"}};
    int turnCount = 0;

    public:
    void play(){
        bool playAgain = true;
        bool gameEnded = false;

        // setup players
        

        while (playAgain){
            // reset all counters
            turnCount = 1;
            board = {"-","-","-","-","-","-","-","-","-"};
            playAgain = false;
            gameEnded = false;

            // while through turns
            while (gameEnded == false){
                // let each player take their turn
                // check between if the game has ended
                // at the end of each turn iterate turns
                // when turns >= 9, game end and check
            }
        }
    }

    void mainMenu(){
        string choice = "";

        while (choice != "Close"){
            choice = printMenu();

            if (choice == "Play"){
                srand(time(0));
                int startingPlayer = rand() % 2; // Select randomly the player to go first, 0 (x) or 1 (o)
                if(startingPlayer == 0) {
                    cout << "x goes first!" << endl;
                } else if (startingPlayer == 1) {
                    cout << "o goes first!" << endl;
                }
                play(startingPlayer);
            }

            if (choice == "Leaderboard"){
                printLeaderboard();

                // something where you need to press any button to move on
                cout << "\nPress any key to continue: ";
                while (cin.get() != '\n');
            }

            cout << "\n";
        }

        // choice of Close
        cout << "Bye!\n";
        return;
    }

    string printMenu(){
        cout << "Please type the option you would like from the options below:\n";
        cout << "    Play\n    Leaderboard\n    Close\n";

        string choice;
        cin >> choice;

        bool correct = false;
        if (choice == "Play" || choice == "Leaderboard" || choice == "Close"){
            correct = true;
        }

        while (correct == false){
            cout << "Try again!\n\n";
            cout << "Please type the option you would like from the options below:\n";
            cout << "    Play\n    Leaderboard\n    Close\n";
            cin >> choice;
            if (choice == "Play" || choice == "Leaderboard" || choice == "Close"){
                correct = true;
            }
        }

        return choice;
    }

    void printBoard(){
        cout << "   a     b     c\n";
        cout << "      |     |\n";
        cout << "1  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n";
        cout << " _____|_____|_____\n";
        cout << "      |     |\n";
        cout << "2  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "\n";
        cout << " _____|_____|_____\n";
        cout << "      |     |\n";
        cout << "3  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "\n";
        cout << "      |     |\n";

        return;
    }

    void printLeaderboard(){
        cout << "                    |\n";
        cout << "    player          |   score\n";
        cout << "____________________|____________\n";
        cout << "                    |\n";

        for (const auto& [score, name] : leaderboard){
            cout << "    " << name;

            for (int i = 0; i < 16 - name.size(); i++){
                cout << " ";
            }

            cout << "|   " << score << "\n";
        }

        cout << "                    |\n";
    }

    string checkWinCon(){
        // there are 16 possible wins, 8 for each player

        // checking the horizontal win cons
        for (int i = 0; i < 7; i = i+3){
            if (board[i] == board[i+1] && board[i+1] == board[i+2]){
                if (board[i] == "x"){
                return "Player 1";
                }
                if (board[i] == "o"){
                    return "Player 2";
                }
            }
        }

        // checking the vertical win cons
        for (int i = 0; i < 3; i++){
            if (board[i] == board[i+3] && board[i+3] == board[i+6]){
                if (board[i] == "x"){
                return "Player 1";
                }
                if (board[i] == "o"){
                    return "Player 2";
                }
            }
        }

        // checking the diagonals
        if (board[0] == board[4] && board[4] == board[8]){
            if (board[0] == "x"){
                return "Player 1";
            }
            if (board[0] == "o"){
                return "Player 2";
            }
        }

        if (board[2] == board[4] && board[4] == board[6]){
            if (board[2] == "x"){
                return "Player 1";
            }
            if (board[2] == "o"){
                return "Player 2";
            }
        }

        return "None";
    }
    bool checkPosition(int position, bool currentPlayer) { // Current player is either 0 or 1, 0=x, 1=o, returns false if invalid, true otherwise
        switch(currentPlayer) {
            case 0:
                if(board[position] == "o") {
                    cout << "Invalid position (there is already an o there, try again)" << endl;
                    return false;
                }
                if(board[position] == "x") {
                    cout << "Invalid position (you have already placed an x there, try again)" << endl;
                    return false;
                } else {
                    board[position] = "x";
                    return true;

                }
                
            case 1:
                if(board[position] == "x") {
                    cout << "Invalid position (there is already an x there, try again)" << endl;
                    return false;
                }
                if(board[position] == "o") {
                    cout << "Invalid position (you have already placed an o there, try again)" << endl;
                    return false;
                } else {
                    board[position] = "o";
                    return true;

                }
        }
    }
    int playerChoice(bool currentPlayer) { // Just gives the option for a choice, no need to run printBoard() again (will all be combined in the play() function)
        int choice;
        while(true) {
            cout << "Select position" << endl;
            cin >> choice;
            if(choice >= 0 && choice <= 8) {
                if (checkPosition(choice, currentPlayer) == true) {
                    return choice;
                }
            } else {
                cout << "Invalid position (pick a number from 0-8), try again" << endl;
            }

        }



    }
    bool play(bool currentPlayer) {
        cout << "Not yet!\n";
        return true;
    }

};

#endif
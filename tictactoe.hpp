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
    map<int, string, greater<int>> leaderboard = {};

    public:
    void play(bool startingPlayer){     // true = player1, false = player2
        bool playAgain = true;

        // setup players
        cout << "Please enter player 1's (x) name: ";
        string name = "";
        cin >> name;
        while (name.size() > 16){
            cout << "Name must be under 16 characters!\n";
            cout << "Please enter player 1's (x) name: ";
            cin >> name;
        }

        Players player1 = Players(name);

        cout << "Please enter player 2's (o) name: ";
        cin >> name;
        while (name.size() > 16){
            cout << "Name must be under 16 characters!\n";
            cout << "Please enter player 2's (x) name: ";
            cin >> name;
        }
        Players player2 = Players(name);

        while (playAgain){
            // reset all counters
            board = {"-","-","-","-","-","-","-","-","-"};
            playAgain = false;

            // actually a for loop where there's a break if there's an early ended game makes way more sense
            // if i is even, do the starting player. if i is odd, do the other player
            printBoard();
            for (int i = 0; i < 9; i++){
                // player 1's turn
                if ((startingPlayer==false && i%2==0) || (startingPlayer && i%2==1)){
                    cout << "X's turn!" << endl;
                    playerChoice(false);
                    printBoard();
                    if (checkWinCon() != "None"){
                        break;
                    }
                }
                // player 2's turn
                else {
                    cout << "O's turn!" << endl;
                    playerChoice(true);
                    printBoard();
                    if (checkWinCon() != "None"){
                        break;
                    }
                }
            }

            // winner announcements and updating winning streaks
            string winner = checkWinCon();
            if (winner == "Player 1"){
                player1.anotherWin();
                player2.lostAGame();
                cout << player1.getName() << " has won!\n";
            }
            else if (winner == "Player 2") {
                player2.anotherWin();
                player1.lostAGame();
                cout << player2.getName() << " has won!\n";
            }
            else {
                cout << "It's a draw!\n";
            }

            // something here for choosing whether to play again
            cout << "Would you like to play again? Type Yes or No: ";
            string anotherGame = "";
            cin >> anotherGame;

            // checking input
            while(anotherGame != "Yes" && anotherGame != "No"){
                cout << "Invalid input.\n";
                cout << "Would you like to play again? Type Yes or No: ";
                cin >> anotherGame;
            }

            if (anotherGame == "Yes"){
                playAgain = true;
            }
            else {
                // update to leaderboards
                if (player1.getConsecWins() != 0){
                    leaderboard.insert({player1.getConsecWins(), player1.getName()});
                }
                if (player2.getConsecWins() != 0){
                    leaderboard.insert({player2.getConsecWins(), player2.getName()});
                }
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
        // delete excess elements


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
        string choice;
        int integerChoice = 0;
        while(true) {
            int integerChoice = 0;
            choice = "";
            cout << "Select position (Enter position by coordinate like 1a, 2b, 3c etc)" << endl;

            cin >> choice;
            integerChoice += ((choice[0] - '0') - 1) * 3;
            if(((int)choice[1]) - 97 >= 0 && ((int)choice[1]) - 97 <= 2) {
                integerChoice += ((int)choice[1]) - 97; // (int)choice[1] gets the ascii value of a, b, c, 97 is the ascii value of 'a' (pretty sure)
            }
            if(integerChoice >= 0 && integerChoice <= 8) {
                if (checkPosition(integerChoice, currentPlayer) == true) {
                    return integerChoice;
                }
            } else {
                cout << "Invalid position (pick a number from 0-8), try again" << endl;
            }

        }
    }
    // bool play(bool currentPlayer) {
    //     cout << "Not yet!\n";
    //     return true;
    // }

};

#endif
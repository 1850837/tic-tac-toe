#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;

class tictactoe{
    private:
    vector<string> board = {"-","-","-","-","-","-","-","-","-"};
    map<int, string, greater<int>> leaderboard = {{7, "Maddy"}, {6, "Zac"}, {99, "Bingo"}, {80, "Wahoooo"}};

    public:
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

};

#endif
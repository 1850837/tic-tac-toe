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
        // checking the horizontal win cons
        

        // checking the vertical win cons

        // checking the diagonals
    }

};

#endif
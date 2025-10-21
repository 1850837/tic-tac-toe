#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <string>
using namespace std;

class Players {
    private:
    string name;
    int consecWins;

    public:
    Players(string newName){
        name = newName;
        consecWins = 0;
    }
    string getName(){
        return name;
    }
    int getConsecWins(){
        return consecWins;
    }
    void anotherWin(){
        consecWins++;
    }
    void lostAGame(){
        consecWins = 0;
    }
};

#endif
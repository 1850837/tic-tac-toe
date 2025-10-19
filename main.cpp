#include "tictactoe.hpp"
using namespace std;

int main(){

    tictactoe a;

    a.printBoard();
    cout << a.checkWinCon() << "\n";

    return 0;
}
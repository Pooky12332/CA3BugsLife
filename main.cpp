#include "Board.h"
#include <iostream>

using namespace std;

int main() {
    Board board;
    board.init();
    board.tap();
    board.tap();
    board.tap();
    board.tap();
    board.tap();
    board.displayAllPaths();
    board.displayAllCells();
}
#include "Board.h"
#include <iostream>

using namespace std;

int main() {
    Board board;
    board.init();
    board.findById(101);
    board.tap();
    board.findById(101);
    board.tap();
    board.findById(101);
    board.tap();
    board.findById(101);
}
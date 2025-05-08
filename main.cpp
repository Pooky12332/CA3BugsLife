#include "Board.h"
#include "GUI.h"
#include <iostream>

using namespace std;

int main() {
    Board board;
    GUI gui(&board);
    board.init();
    gui.run();

    cout << "// Bug Status" << endl;
    board.displayAll();

    cout << endl << "// Display all paths" << endl;
    board.displayAllPaths();
}
#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "Board.h"

class GUI {
public:
	GUI(Board* board);
	void run();

private:
	void drawGrid();
	void drawBugs();
	void updateBoard();

	sf::RenderWindow window;
	Board* board;
	const int cellSize = 50;
	const int gridSize = 10;
	sf::Font font;
};

#endif
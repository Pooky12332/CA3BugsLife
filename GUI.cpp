#include "GUI.h"
#include "Board.h"
#include "Slider.h"

GUI::GUI(Board* board) : board(board), window(sf::VideoMode(500, 500), "Bug Simulator") {
	font.loadFromFile("arial.ttf");
}

void GUI::run() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Drawing the
		window.clear(sf::Color::White);
		drawGrid();
		drawBugs();
		window.display();

		// Running the simulation
		board->tap();
		updateBoard();
		sf::sleep(sf::seconds(1));
	}

	// Write to file before exit
	board->exit();
}

// Drawing the grid itself
void GUI::drawGrid() {
	for (int x = 0; x < gridSize; ++x) {
		for (int y = 0; y < gridSize; ++y) {
			sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
			cell.setPosition(x * cellSize, y * cellSize);
			cell.setFillColor(sf::Color(230, 230, 230));
			cell.setOutlineColor(sf::Color::Black);
			cell.setOutlineThickness(1);
			window.draw(cell);
		}
	}
}


// Draw the currently alive bugs to the grid
void GUI::drawBugs() {
	for (Bug* bug : board->getBugs()) {
		if (!bug->isAlive()) continue;
		Position pos = bug->getPosition();

		sf::CircleShape bugShape(cellSize / 2 - 5);
		bugShape.setPosition(pos.x * cellSize + 5, pos.y * cellSize + 5);

		if (dynamic_cast<Crawler*>(bug)) {
			bugShape.setFillColor(sf::Color::Red);
		} else if (dynamic_cast<Hopper*>(bug)) {
			bugShape.setFillColor(sf::Color::Blue);
		} else if (dynamic_cast<Slider*>(bug)) {
			bugShape.setFillColor(sf::Color::Green);
		}

		window.draw(bugShape);

		// Setting up some info on the bugs
		sf::Text infoText;
		infoText.setFont(font);
		infoText.setString(std::to_string(bug->getId()));
		infoText.setCharacterSize(12);
		infoText.setFillColor(sf::Color::Black);
		infoText.setPosition(pos.x * cellSize + 10, pos.y * cellSize + 10);
		window.draw(infoText);
		infoText.setString(std::to_string(bug->getSize()));
		infoText.setPosition(pos.x * cellSize + 10, pos.y * cellSize + 20);
		window.draw(infoText);
	}
}

void GUI::updateBoard() {
	// Count alive bugs
	int aliveCount = 0;
	for (Bug* bug : board->getBugs()) {
		if (bug->isAlive()) {
			aliveCount++;
		}
	}

	// If only one bug remains, close the window after a short pause
	if (aliveCount <= 1) {
		sf::sleep(sf::seconds(2)); // Allow time to see the final state
		window.close();
	}
}
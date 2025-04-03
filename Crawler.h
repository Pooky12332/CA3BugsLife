#ifndef CRAWLER_H
#define CRAWLER_H

#include <list>

using namespace std;
// Position struct
struct Position {
	int x;
	int y;
};

enum Direction {
	North = 1,
	East = 2,
	South = 3,
	West = 4
};

class Crawler {
private:
	int id;
	Position position;
	Direction direction;
	int size;
	bool alive;
	list<Position> path;

public:
	// Constructors
	Crawler(int id, Position position, Direction direction, int size, bool alive, list<Position> path);

	// Deconstructors
	~Crawler() {};

	// Methods
	void move();
	bool isWayBlocked();

	// Getters
	int getId() const;
	Position getPosition() const;
	Direction getDirection() const;
	int getSize() const;
	bool isAlive() const;
	list<Position> getPath() const;

	// Setters
	void setId(int id);
	void setPosition(Position position);
	void setDirection(Direction direction);
	void setSize(int size);
	void setAlive(bool alive);
};

#endif //CRAWLER_H

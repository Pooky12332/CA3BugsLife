#ifndef BUG_H
#define BUG_H

#include <list>

using namespace std;

// Position Struct
struct Position {
	int x;
	int y;

	// For when use in mapping, allows comparison
	bool operator<(const Position& other) const {
		return std::tie(x, y) < std::tie(other.x, other.y);
	}
};

// Direction ENUM
enum Direction {
	North = 1,
	East = 2,
	South = 3,
	West = 4
};

class Bug {
private:
	int id;
	Position position;
	Direction direction;
	int size;
	bool alive;
	list<Position> path;

public:
	// Constructor
	Bug();
	Bug(int id, Position position, Direction direction, int size, bool alive);

	// Deconstructor
	virtual ~Bug();

	// Methods
	bool isWayBlocked();
	virtual void move() = 0;

	// Getters
	int getId() const;
	Position getPosition() const;
	Direction getDirection() const;
	int getSize() const;
	bool isAlive() const;
	list<Position>& getPath();

	// Setters
	void setId(int id);
	void setPosition(Position position);
	void setDirection(Direction direction);
	void setSize(int size);
	void setAlive(bool alive);
};

#endif //BUG_H
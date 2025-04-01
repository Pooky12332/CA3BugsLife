#ifndef CRAWLER_H
#define CRAWLER_H

#include <list>

using namespace std;

struct Position {
	int x;
	int y;
};

class Crawler {
	private:
		int id;
		Position position;
		int direction;
		int size;
		bool alive;
		list<Position> path;

	public:
		// Constructors
		Crawler();
		Crawler(int id, Position position, int direction, int size, bool alive, list<Position> path);

		// Deconstructors
		~Crawler();

		// Getters
		int getId();
		Position getPosition();
		int getDirection();
		int getSize();
		bool isAlive();
		list<Position> getPath();

		// Setters
		void setId(int id);
		void setPosition(Position position);
		void setDirection(int direction);
		void setSize(int size);
		void setAlive(bool alive);
		void setPath(list<Position> path);

		// Methods

};

#endif //CRAWLER_H

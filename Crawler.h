#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"

using namespace std;

class Crawler : public Bug {
public:
	// Constructors
	Crawler(int id, Position position, Direction direction, int size, bool alive);

	// Deconstructors
	~Crawler() override;

	// Methods
	void move() override;
};

#endif //CRAWLER_H

#pragma once
#include <vector>

struct Position {
	double x;
	double y;

	double dx;
	double dy;

	Position(double x, double y, double dx, double dy) {
		this->x = x;
		this->y = y;
		this->dx = dx;
		this->dy = dy;
	}

	Position(double x, double y) {
		this->x = x;
		this->y = y;
		dx = 0;
		dy = 0;
	}
};

class TrainPositions {
private:
	std::vector<Position> positions;
public:
	TrainPositions(int trainCount);
	Position* getPositionPointer(int index);
	Position& operator[] (int index);
};

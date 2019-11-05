#include "Positions.h"

TrainPositions::TrainPositions(int amount) {
	for (int i = 0; i < amount; i++) {
		positions.push_back(Position(0, 0, 0, 0));
	}
}

Position& TrainPositions::operator[] (int index) {
	return positions[index];
}

Position* TrainPositions::getPositionPointer(int index)
{
	return &positions[index];
};

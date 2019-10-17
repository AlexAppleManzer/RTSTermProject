#pragma once
#include "Positions.h"
#include "Signals.h"
#include <chrono>

void startControlCenter(TrainPositions* positions, Signals* signals, std::chrono::milliseconds tickTime, int numTicks, int numTrains);

struct Collision {
	int train1;
	int train2;


};

struct Segments {
	std::vector<Position> startSegmentPoints;
	std::vector<Position> endSegmentPoints;
};

class ControlCenter {
private:
	TrainPositions* positions;
	Signals* signals;
	int numTrains;

	// input train pos and output if collision occurs
	// -1 = good anything else = bad
	bool detectCollision();

	int detectCollision(std::vector<Position>);

	// take a set of positions and fast forward them a set number of ticks
	std::vector<Position> simulate(int ticks);

	// take all train positions, simulate and detect possible collisions and then signal a train to stop if a collision is detected
	void predictCollision();

	// stop a train
	void stopTrain(int train);

public:
	ControlCenter(TrainPositions* positions, Signals* signals, int numTrains);
	void tick();
};

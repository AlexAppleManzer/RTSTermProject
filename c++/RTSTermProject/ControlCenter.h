#pragma once
#include "Positions.h"
#include "Signals.h"
#include <chrono>
#include <json.h>

void startControlCenter(TrainPositions* positions, Signals* signals, std::chrono::milliseconds tickTime, int numTicks, int numTrains);

struct Collision {
	Collision(int t1, int t2) {
		collision = true;
		train1 = t1;
		train2 = t2;
	}

	Collision() {

	}

	bool collision = false;
	int train1 = -1;
	int train2 = -1;
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
	//Json::Value trainPos;

	int predictionTicks = 3;


	// input train pos and output if collision occurs
	// -1 = good anything else = bad
	bool detectCollision();

	
	Collision detectCollision(std::vector<Position>);

	// take a set of positions and fast forward them a set number of ticks
	std::vector<Position> simulate(int ticks);

	// stop a train
	void stopTrain(int train);

	void avoidCollision(int ticks=1);

public:
	ControlCenter(TrainPositions* positions, Signals* signals, int numTrains);
	void tick();
};
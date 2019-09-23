#pragma once
#include "Positions.h"
#include "Signals.h"

class Train {
private:
	const double trainLength = 1;

    double x;
	double y;
	double dx;
	double dy;

    int maxX = 10; //0-10
    int maxY = 10; //0-10
    Position* position;
	int* signal;

public:
    Train(double startX, double startY, double dx, double dy, Position* position, int* signal);
	void incrementTrain();
};

void startTrainThread(double startX, double startY, double dx, double dy, Position* position, int* signal, std::chrono::milliseconds tickTime, int numTicks);

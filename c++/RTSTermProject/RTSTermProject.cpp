#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <json.h>

#include "Train.h"
#include "ControlCenter.h"

const static int trainCount = 10;
const static int totalTicks = 20;
const static std::chrono::milliseconds tickTime = std::chrono::milliseconds(250);

//Json::Value createJSONTrainPos(double position)
//{
//
//}

int main()
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0, 10);
	std::uniform_real_distribution<> firstOrderDist(-1, 1);

	TrainPositions positions(trainCount);
	Signals signals(trainCount);

	std::thread* trainThreads[trainCount];
	for (int i = 0; i < trainCount; i++) {
		//initializes all train threads and gives them communication objects
		double x = dist(e2);
		double y = dist(e2);
		double dx = firstOrderDist(e2);
		double dy = firstOrderDist(e2);
		trainThreads[i] = new std::thread(startTrainThread, x, y, dx, dy, positions.getPositionPointer(i), signals.getTrainSignal(i), tickTime, totalTicks);
	}

	// starts CC thread
	std::thread readerThread(startControlCenter, &positions, &signals, tickTime, totalTicks, trainCount);

	Json::Value trainPos;

	for (int i = 0; i < trainCount; i++) {
		trainThreads[i]->join();

		trainPos[i]["x-pos"].append(positions[i].x);
		trainPos[i]["y-pos"].append(positions[i].y);
		trainPos[i]["dx-pos"].append(positions[i].dx);
		trainPos[i]["dy-pos"].append(positions[i].dy);
	}

	readerThread.join();

	std::cout << trainPos;
	return 0;
}

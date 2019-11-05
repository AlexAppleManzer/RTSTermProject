#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <random>

#include "Train.h"
#include "ControlCenter.h"

const static int trainCount = 5;
const static int totalTicks = 20;
const static std::chrono::milliseconds tickTime = std::chrono::milliseconds(250);

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

	for (int i = 0; i < trainCount; i++) {
		trainThreads[i]->join();
	}
	readerThread.join();
	return 0;
}

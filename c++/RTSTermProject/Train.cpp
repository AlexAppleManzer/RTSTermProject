#include <chrono>
#include <thread>
#include <assert.h>
#include "Train.h"
#include <iostream>

Train::Train(double startX, double startY, double dx, double dy, Position* position, int* signal) {
	this->x = startX;
	this->y = startY;
	assert(this->dx < trainLength);
	assert(this->dy < trainLength);
	this->dy = dy;
	this->dx = dx;
	this->signal = signal;
	this->position = position;
	this->position->x = x;
	this->position->y = y;
	this->position->dx = dx;
	this->position->dy = dy;
}

double constrain(double num, double min, double max) {
	if (num > max) {
		return constrain(num - (max - min), min, max);
	}
	if (num < min) {
		return constrain(num + (max - min), min, max);
	}
	return num;
}

void Train::incrementTrain() {
	switch (*signal) {
	case 0:	// Continue as normal (green light)
		x = constrain(x + dx, 0, maxX);
		y = constrain(y + dy, 0, maxY);
		this->position->x = x;
		this->position->y = y;
		break;
	case 1: // Slow down? (yellow light)
		break;
	case 2: // STOP (red light)
		std::cout << "I'm stopped" << std::endl;
		break;
	}

}

void startTrainThread(double startX, double startY, double dx, double dy, Position* position, int* signal, std::chrono::milliseconds tickTime, int numTicks) {

	Train train(startX, startY, dx, dy, position, signal);

	for (int i = 0; i < numTicks; i++) {
		train.incrementTrain();
		std::this_thread::sleep_for(tickTime);
	}
}
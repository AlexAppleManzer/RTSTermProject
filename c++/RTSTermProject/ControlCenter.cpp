#include "ControlCenter.h"
#include "HelperFunctions.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <json.h>
#include <string>



void ControlCenter::stopTrain(int train)
{
	signals->setTrainSignal(train, 2);
}

ControlCenter::ControlCenter(TrainPositions* positions, Signals* signals, int numTrains)
{
	this->positions = positions;
	this->signals = signals;
	this->numTrains = numTrains;
}

void ControlCenter::tick()
{
	signals->resetTrainSignals();

	//trainPos.clear();

	for (int i = 0; i < numTrains; i++) {
		Position pos = positions -> operator[](i);
		logTrainPos(pos.x, pos.y, pos.dx, pos.dy, i);


		//trainPos["x-pos"].append(pos.x);
		//trainPos["y-pos"].append(pos.y);
		//trainPos["dx-pos"].append(pos.dx);
		//trainPos["dy-pos"].append(pos.dy);
	}

	avoidCollision(predictionTicks);

	std::cout << "Collision? " << detectCollision() << std::endl;

	std::cout << std::endl;
}

void ControlCenter::avoidCollision(int ticks) {
	// adapted from big brain python code.
	for (int i = 1; i <= ticks; i++) {
		Collision nextCrash = detectCollision(simulate(i));
		if (nextCrash.collision == true) {
			if (*(signals->getTrainSignal(nextCrash.train1)) == 0)
			{
				stopTrain(nextCrash.train2);
			}
			else
			{
				stopTrain(nextCrash.train1);
			}
			avoidCollision(ticks);
		}
	}
}


bool ControlCenter::detectCollision() {
	// get point pairings (start and end of train)
	Segments segments;
	for (int i = 0; i < numTrains; i++) {
		Position pos = positions -> operator[](i);
		segments.startSegmentPoints.push_back(pos);

		double r = std::sqrt(pos.dx * pos.dx + pos.dy * pos.dy);
		double endX = (-pos.dx / r) + pos.x;
		double endY = (-pos.dy / r) + pos.y;

		segments.endSegmentPoints.push_back(Position(endX, endY));
	}

	//detect collisions
	for (int i = 0; i < numTrains; i++) {
		for (int j = i + 1; j < numTrains; j++) {
			Position startLine1 = segments.startSegmentPoints[i];
			Position endLine1 = segments.endSegmentPoints[i];
			Position startLine2 = segments.startSegmentPoints[j];
			Position endLine2 = segments.endSegmentPoints[j];

			if (intersect(startLine1.x, startLine1.y, endLine1.x, endLine1.y, startLine2.x, startLine2.y, endLine2.x, endLine2.y)) {
				std::cout << i << ", " << j << std::endl;
				std::cout << endLine1.x << "," << endLine1.y << std::endl;
				std::cout << endLine2.x << "," << endLine2.y << std::endl;
				return true;
			}
		}
	}
	return false;
}

Collision ControlCenter::detectCollision(std::vector<Position> positions) {
	// get point pairings (start and end of train)
	Segments segments;
	for (int i = 0; i < numTrains; i++) {
		Position pos = positions[i];
		segments.startSegmentPoints.push_back(pos);

		double r = std::sqrt(pos.dx * pos.dx + pos.dy * pos.dy);
		double endX = (-pos.dx / r) + pos.x;
		double endY = (-pos.dy / r) + pos.y;

		segments.endSegmentPoints.push_back(Position(endX, endY));
	}

	//detect collisions
	for (int i = 0; i < numTrains; i++) {
		for (int j = i + 1; j < numTrains; j++) {
			Position startLine1 = segments.startSegmentPoints[i];
			Position endLine1 = segments.endSegmentPoints[i];
			Position startLine2 = segments.startSegmentPoints[j];
			Position endLine2 = segments.endSegmentPoints[j];

			if (intersect(startLine1.x, startLine1.y, endLine1.x, endLine1.y, startLine2.x, startLine2.y, endLine2.x, endLine2.y)) {
				return Collision(i, j);
			}
		}
	}
	return Collision();
}

std::vector<Position> ControlCenter::simulate(int ticks)
{
	std::vector<Position> result = std::vector<Position>();
	for (int i = 0; i < numTrains; i++) {
		double dx = positions->operator[](i).dx;
		double dy = positions->operator[](i).dy;
		if (*(signals->getTrainSignal(i)) == 2) {
			result.emplace_back(Position(positions->operator[](i).x, positions->operator[](i).y, dx, dy));
			continue;
		}
		double newX = positions->operator[](i).x + ticks * dx;
		double newY = positions->operator[](i).y + ticks * dy;
		result.emplace_back(Position(newX, newY, dx, dy));
	}
	return result;
}

void startControlCenter(TrainPositions* positions, Signals* signals, std::chrono::milliseconds tickTime, int numTicks, int numTrains)
{
	ControlCenter controlCenter(positions, signals, numTrains);

	for (int i = 0; i < numTicks; i++) {
		controlCenter.tick();
		std::this_thread::sleep_for(tickTime);
	}
}
#include <vector>
#include "Signals.h"


Signals::Signals(int totalTrains) //initializes vector of signals with total number of trains; gives each train the OK command
{
	signals.resize(totalTrains, 0);
}

void Signals::setTrainSignal(int train, int signal) //modifies signal for a train
{
	signals[train] = signal;
}

int* Signals::getTrainSignal(int train) //function trains use to receive their signal
{
	return &signals[train];
}

void Signals::resetTrainSignals()
{
	for (int i = 0; i < signals.size(); i++) {
		signals[i] = 0;
	}
}
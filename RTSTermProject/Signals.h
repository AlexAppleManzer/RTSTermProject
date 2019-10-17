#pragma once
#include <vector>


/*
	SIGNALS
	0 - proceed
	1 - slow down
	2 - stop
*/

// Signals class -> will contain multiple signal
// Control center will get Signals object
// Train will get their cooresponding signtal 

class Signals
{
private:
	std::vector<int> signals{ 0 };
public:
	Signals(int trains);
	void setTrainSignal(int train, int signal);
	int* getTrainSignal(int train);
	void resetTrainSignals();
};

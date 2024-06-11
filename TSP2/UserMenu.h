#pragma once
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"
class UserMenu
{
public:
	void mainMenu();

	void tests();

	SimulatedAnnealing simulatedAnnealing;

	TabuSearch tabuSearch;

	MyInOut inOut;
};


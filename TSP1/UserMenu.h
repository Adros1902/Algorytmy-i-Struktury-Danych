#pragma once
#include "BruteForce.h"
#include "DynamicProgramming.h"
#include "BranchAndBound.h"
#include "BranchAndBoundDFS.h"
class UserMenu
{
public:
	BruteForce bruteForce;

	DynamicProgramming dynamicProgramming;

	BranchAndBound branchAndBound;

	BranchAndBoundDFS branchAndBoundDFS;

	double elapsedTime = 0;

	void mainMenu();

	void bruteForceMenu();

	void dynamicProgrammingMenu();

	void branchAndBoundMenu();

	void branchAndBoundDFSMenu();

	void Tests();

	std::string replaceDotWithComma(double value);
};


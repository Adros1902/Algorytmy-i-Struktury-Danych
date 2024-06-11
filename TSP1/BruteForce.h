#pragma once
#include <string>
#include "MyList.h"

class BruteForce
{
public:
	int cityNumber = 0;

	int currentCost;

	int bestCost;

	int startVertex = 0;

	int** matrix = NULL;

	bool* visited = NULL;

	MyList bestPath;

	MyList currentPath;

	BruteForce();

	~BruteForce();

	void createFromFile(std::string fileName);

	void generateMatrix(int size);

	void printMatrix();

	void bruteForceAlgorithmRecursion(int vertex);

	void bruteForce(int startVertex);

	void printResult();

	void generateRandomMatrix(int size);
};


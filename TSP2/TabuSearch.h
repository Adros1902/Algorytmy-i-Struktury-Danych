#pragma once
#include "MyInOut.h"
#include <vector>
class TabuSearch
{
public:
	MyInOut inOut;

	int** matrix;

	int numberOfCities = 0;

	int costFromGreedy = 0;

	int currentNewPathCost = 0;

	int bestPathCost = 0;

	double bestPathTime = 0;

	double elapsedTime = 0;

	int stopTime = 0;

	int tabuTenure = 0;

	std::vector<int> greedyPath;

	std::vector<int> currentNewPath;

	std::vector<int> bestPath;

	std::vector<std::vector<double>> bestFoundTimes;

	int** tabuMatrix;

	bool** usedEdges;

	void generateMatrix(int size);

	void deleteMatrix();

	void generateTabuMatrix(int size);

	void createFromFile(std::string fileName);

	void greedyAlgorithm();

	void printResult();

	void tabuSearch();

	void searchWithSwap();

	void saveToFile(std::string fileName);

};


#pragma once
#include <string>
#include <vector>
#include "MyInOut.h"
class SimulatedAnnealing
{
public:

	MyInOut inOut;

	int** matrix;

	int numberOfCities = 0;

	int costFromGreedy = 0;

	double temperatureCoefficient = 0;

	int currentPathCost = 0;

	int currentNewPathCost = 0;

	int bestPathCost = 0;

	double finalTemp = 0;

	double currentTemp = 0;

	double startTemperature = 0;

	double bestPathTime = 0;

	double elapsedTime = 0;

	int stopTime = 0;

	int tabuTenure = 0;

	std::vector<int> greedyPath;

	std::vector<int> currentPath;
	
	std::vector<int> currentNewPath;

	std::vector<int> bestPath;

	std::vector<std::vector<double>> bestFoundTimes;

	int** tabuMatrix;

	bool** usedEdges;

	SimulatedAnnealing();

	void generateMatrix(int size);

	void deleteMatrix();

	void createFromFile(std::string fileName);

	void printMatrix();

	void greedyAlgorithm();

	void simulatedAnnealing();

	double calculateInitialTemperature();

	void printResult();

	void saveToFile(std::string fileName);
};


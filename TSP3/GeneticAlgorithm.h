#pragma once
#include <string>
#include <vector>
#include "MyInOut.h"
class GeneticAlgorithm
{
public:

	MyInOut inOut;

	int** matrix;

	std::vector<std::vector<int>> population;
	std::vector<std::vector<int>> newPopulation;

	int numberOfCities = 0;

	int bestPathCost = INT_MAX;

	int populationSize = 0;

	double elapsedTime = 0;

	int stopTime = 0;

	float crossoverProb;

	float mutationProb;

	int crossoverType;

	int mutationType;

	double bestPathTime = 0;

	std::vector<std::vector<double>> bestFoundTimes;

	std::vector<int> bestPath;

	GeneticAlgorithm();

	void generateMatrix(int size);

	void deleteMatrix();

	void createFromFile(std::string fileName);

	void printMatrix();

	void printResult();

	void geneticAlgorithm();

	void orderCrossover(std::vector<int> &parent1, std::vector<int> &parent2, std::vector<int>& child1, std::vector<int>& child2);

	void partiallyMatchedCrossover(std::vector<int> &parent1, std::vector<int> &parent2, std::vector<int>& child1, std::vector<int>& child2);
	
	std::vector<int> tournamentSelection();

	int calculateFitness(std::vector<int> path);

	std::vector<int> swapMutation(std::vector<int> path);

	std::vector<int> invertionMutation(std::vector<int> path);

	void generatePopulation(int populationSize);

	void saveToFile(std::string fileName);
};


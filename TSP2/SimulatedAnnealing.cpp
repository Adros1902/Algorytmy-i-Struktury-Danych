#include "SimulatedAnnealing.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <Windows.h>



SimulatedAnnealing::SimulatedAnnealing()
{
}

void SimulatedAnnealing::generateMatrix(int size)
{
	matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}
}

void SimulatedAnnealing::deleteMatrix()
{
	for (int i = 0; i < numberOfCities; i++)
	{
			delete[] matrix[i];
	}
	delete[] matrix;
	numberOfCities = 0;
}

void SimulatedAnnealing::createFromFile(std::string fileName)
{
	if (numberOfCities != 0) {
		deleteMatrix();
	}
	numberOfCities = inOut.getNumberOfCities(fileName);
	generateMatrix(numberOfCities);

	matrix = inOut.createMatrixFromFile(fileName);

}

// uzywane tylko do testow 
void SimulatedAnnealing::printMatrix()
{
	std::cout << "Macierz:" << std::endl;
	for (int i = 0; i < numberOfCities; i++) {
		for (int j = 0; j < numberOfCities; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void SimulatedAnnealing::greedyAlgorithm()
{
	costFromGreedy = 0;
	greedyPath.clear();
	bool* visited = new bool[numberOfCities];
	
	for (int i = 0; i < numberOfCities; i++)
	{ 
		visited[i] = false;
	}

	std::vector<int> path;
	int currentVertex = 0;

	path.push_back(0);
	visited[0] = true;

	while (path.size() < numberOfCities)
	{
		int tempMin = INT_MAX;
		int nextVertex;
		for (int i = 0; i < numberOfCities; i++) {
			if (tempMin >= matrix[currentVertex][i] && !visited[i] && currentVertex != i) {
				tempMin = matrix[currentVertex][i];
				nextVertex = i;
			}
		}
		path.push_back(nextVertex);
		costFromGreedy += tempMin;
		visited[nextVertex] = true;
		currentVertex = nextVertex;

	}

	path.push_back(0);
	costFromGreedy += matrix[currentVertex][0];

	greedyPath = path;
	delete[] visited;
}

void SimulatedAnnealing::simulatedAnnealing()
{
	if (bestFoundTimes.size() != 0) {
		bestFoundTimes.clear();
	}
	LARGE_INTEGER frequency;
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
	LARGE_INTEGER foundBestPathTime;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randomInt(1, (numberOfCities - 1));
	std::uniform_int_distribution<> randomInt2(1, (numberOfCities - 2));
	std::uniform_real_distribution<double> dis(0.0, 1.0);

	//uzywane tylko dla testow
	//temperatureCoefficient = 0.999;

	currentTemp = calculateInitialTemperature();
	//currentTemp = 0.99;
	//std::cout << currentTemp;
	startTemperature = currentTemp;
	//stopTime = 1;
	

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);

	greedyAlgorithm();

	currentPath = greedyPath;
	currentPathCost = costFromGreedy;
	bestPath = greedyPath;
	bestPathCost = costFromGreedy;

	int era = numberOfCities * 2;
	int eraIterator = 0;
	while (true) {
		eraIterator++;

		int firstElement, secondElement, temp;

		firstElement = randomInt(gen);

		//wyznaczanie nowej sasiadujacej sciezki
		while (true) {
			temp = randomInt2(gen);
			if (temp != firstElement) {
				secondElement = temp;
				break;
			}
		}
		currentNewPath = currentPath;
		currentNewPathCost = 0;
		int tempIndex = currentNewPath[firstElement];
		currentNewPath.erase(currentNewPath.begin() + (firstElement));
		currentNewPath.insert(currentNewPath.begin() + secondElement, tempIndex);
		for (int i = 0; i < numberOfCities; i++)
		{
			int startCity, endCity;
			startCity = currentNewPath[i];
			endCity = currentNewPath[i + 1];
			currentNewPathCost += matrix[startCity][endCity];
		}
		//sprawdzanie czy jest lepsza
		if (currentNewPathCost < currentPathCost) {
			currentPathCost = currentNewPathCost;
			currentPath = currentNewPath;
			if (currentPathCost < bestPathCost) {
				
				bestPathCost = currentPathCost;
				bestPath = currentPath;
				QueryPerformanceCounter(&foundBestPathTime);
				bestPathTime = static_cast<double>(foundBestPathTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
				std::vector<double> tempElement;
				tempElement.push_back(bestPathCost);
				tempElement.push_back(bestPathTime);
				bestFoundTimes.push_back(tempElement);
			}
		}
		else {
			//jesli nie to z prawdopodobienstwa
			double probability, randomProbability;
			probability = std::exp( (-(currentNewPathCost - currentPathCost)) / currentTemp);
			
			randomProbability = dis(gen);
			if (randomProbability < probability) {
				currentPath = currentNewPath;
				currentPathCost = currentNewPathCost;
			}
		}
		if (eraIterator == era) {
			currentTemp = temperatureCoefficient * currentTemp;
			eraIterator = 0;
		}

		QueryPerformanceCounter(&endTime);
		elapsedTime = static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
		// sprawdzanie czy kryterium stopu zostalo spelnione
		if (elapsedTime > stopTime) {
			break;
		}
	}
}

double SimulatedAnnealing::calculateInitialTemperature()
{
	int totalDistance = 0;

	for (int i = 0; i < numberOfCities; i++) {
		for (int j = 0; j < numberOfCities; j++)
		{
			if (i != j) {
				totalDistance += matrix[i][j];
			}
		}
	}
	double avgDistance = static_cast<double>(totalDistance) / ((numberOfCities * numberOfCities) - numberOfCities);

	return avgDistance;
}

void SimulatedAnnealing::printResult()
{
	std::cout << "Sciezka: " << std::endl;
	for (int i = 0; i < bestPath.size(); i++)
	{
		std::cout << bestPath[i] << " ";
	}
	std::cout << std::endl << "Koszt: " << bestPathCost << std::endl;
	double expValue = std::exp(-1.0 / currentTemp);
	std::cout << "exp(-1/Tk) = " << expValue << std::endl;
	std::cout << "Tk = " << currentTemp;
}

void SimulatedAnnealing::saveToFile(std::string fileName)
{

	inOut.saveToFile(fileName, numberOfCities, bestPath);

}




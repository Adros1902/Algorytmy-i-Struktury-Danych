#include "TabuSearch.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <Windows.h>

void TabuSearch::generateMatrix(int size)
{
	matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}
}

void TabuSearch::deleteMatrix()
{
}

void TabuSearch::generateTabuMatrix(int size)
{
	tabuMatrix = new int* [size];
	usedEdges = new bool* [size];
	for (int i = 0; i < size; i++) {
		tabuMatrix[i] = new int[size];
		usedEdges[i] = new bool[size];
		for (int j = 0; j < size; j++) {
			tabuMatrix[i][j] = 0;
			usedEdges[i][j] = false;
		}
	}
}

void TabuSearch::createFromFile(std::string fileName)
{
	if (numberOfCities != 0) {
		deleteMatrix();
	}
	numberOfCities = inOut.getNumberOfCities(fileName);
	generateMatrix(numberOfCities);

	matrix = inOut.createMatrixFromFile(fileName);

	generateTabuMatrix(numberOfCities);
}

void TabuSearch::greedyAlgorithm()
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

void TabuSearch::printResult()
{
	std::cout << "Sciezka: " << std::endl;
	for (int i = 0; i < bestPath.size(); i++)
	{
		std::cout << bestPath[i] << " ";
	}
	std::cout << std::endl << "Koszt: " << bestPathCost;
}

void TabuSearch::tabuSearch()
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

	generateTabuMatrix(numberOfCities);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);

	greedyAlgorithm();


	currentNewPath = greedyPath;
	currentNewPathCost = costFromGreedy;
	bestPath = greedyPath;
	bestPathCost = costFromGreedy;

	tabuTenure = numberOfCities;
	int sameValue = numberOfCities;
	int sameCounter = 0;
	while (true) {

		//szukanie sasiada
		searchWithSwap();
		//sprawdzanie czy lepszy
		if (currentNewPathCost < bestPathCost) {
			sameCounter = 0;
			bestPath = currentNewPath;
			bestPathCost = currentNewPathCost;
			QueryPerformanceCounter(&foundBestPathTime);
			bestPathTime = static_cast<double>(foundBestPathTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
			std::vector<double> tempElement;
			tempElement.push_back(bestPathCost);
			tempElement.push_back(bestPathTime);
			bestFoundTimes.push_back(tempElement);
		}
		//iteracja zmniejszajaca tablice tabu
		for (int i = 0; i < numberOfCities; i++)
		{
			for (int j = 0; j < numberOfCities; j++) {
				if (tabuMatrix[i][j] != 0) {
					tabuMatrix[i][j] -= 1;
					tabuMatrix[j][i] -= 1;
				}
			}
		}

		//dywersyfikacja 
		sameCounter++;
		if (sameCounter == sameValue) {
			sameCounter = 0;
			currentNewPathCost = 0;
			currentNewPath = bestPath;
			for (int i = 0; i < numberOfCities / 5; i++) {
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
				std::swap(currentNewPath[firstElement], currentNewPath[secondElement]);
			}
			for (int i = 0; i < numberOfCities; i++)
			{
				int startCity, endCity;
				startCity = currentNewPath[i];
				endCity = currentNewPath[i + 1];
				currentNewPathCost += matrix[startCity][endCity];
			}
		}
		QueryPerformanceCounter(&endTime);
		elapsedTime = static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
		// sprawdzanie czy kryterium stopu zostalo spelnione
		if (elapsedTime > stopTime) {
			break;
		}
	}
}

void TabuSearch::searchWithSwap()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randomInt(1, (numberOfCities - 2));
	std::uniform_int_distribution<> randomInt2(1, (numberOfCities - 2));

	int firstElement, secondElement;
	std::vector<int> searchedPath = currentNewPath;
	int searchedPathCost = INT_MAX;
	for (int i = 0; i < numberOfCities * 5; i++)
	{

		while (true) {
			firstElement = randomInt(gen);
			//wyznaczanie nowej sasiadujacej sciezki
			while (true) {
				int temp;
				temp = randomInt2(gen);
				if (temp != firstElement) {
					secondElement = temp;
					break;
				}
			}
			// sprawdzanie czy nie ma na tabu i czy nie byla juz wyszukana
			if (usedEdges[currentNewPath[firstElement]][currentNewPath[secondElement]] == false) {
				break;
			} 
		}

		
		std::vector<int> currentNewPathCopy = currentNewPath;
		int currentNewPathCopyCost = 0;
		//operacja zamiany elementow
		std::swap(currentNewPathCopy[firstElement], currentNewPathCopy[secondElement]);

		for (int i = 0; i < numberOfCities; i++)
		{
			int startCity, endCity;
			startCity = currentNewPathCopy[i];
			endCity = currentNewPathCopy[i + 1];
			currentNewPathCopyCost += matrix[startCity][endCity];
		}

		if (tabuMatrix[currentNewPath[firstElement]][currentNewPath[secondElement]] != 0) {
			if (currentNewPathCopyCost > bestPathCost) {
				continue;
			}
		}

		//sprawdzanie czy lepsza niz poprzednia
		if (currentNewPathCopyCost < searchedPathCost) {
			searchedPathCost = currentNewPathCopyCost;
			searchedPath = currentNewPathCopy;
		}


		usedEdges[currentNewPathCopy[firstElement]][currentNewPathCopy[secondElement]] = true;
		usedEdges[currentNewPathCopy[secondElement]][currentNewPathCopy[firstElement]] = true;
	}

	for (int i = 0; i < numberOfCities; i++)
	{
		for (int j = 0; j < numberOfCities; j++) {
			usedEdges[i][j] = false;
		}
	}
	//dodawanie do macierzy tabu
	tabuMatrix[searchedPath[firstElement]][searchedPath[secondElement]] = tabuTenure;
	tabuMatrix[searchedPath[secondElement]][searchedPath[firstElement]] = tabuTenure;
	currentNewPath = searchedPath;
	currentNewPathCost = searchedPathCost;
}

void TabuSearch::saveToFile(std::string fileName)
{
	inOut.saveToFile(fileName, numberOfCities, bestPath);
}


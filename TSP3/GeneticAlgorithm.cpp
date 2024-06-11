#include "GeneticAlgorithm.h"\
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <Windows.h>
#include <unordered_map>


GeneticAlgorithm::GeneticAlgorithm()
{
}

void GeneticAlgorithm::generateMatrix(int size)
{
	matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			if (i == j) {
				matrix[i][j] = 0;
			}
			else
				matrix[i][j] = j;
		}
	}
}

void GeneticAlgorithm::deleteMatrix()
{
	for (int i = 0; i < numberOfCities; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	numberOfCities = 0;
}

void GeneticAlgorithm::createFromFile(std::string fileName)
{
	if (numberOfCities != 0) {
		deleteMatrix();
	}
	numberOfCities = inOut.getNumberOfCities(fileName);
	generateMatrix(numberOfCities);

	matrix = inOut.createMatrixFromFile(fileName);
}

void GeneticAlgorithm::printMatrix()
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

void GeneticAlgorithm::printResult()
{

}

void GeneticAlgorithm::geneticAlgorithm()
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
	LARGE_INTEGER foundBestPathTime;

	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::uniform_real_distribution<float> randomFloat(0, 1);

	elapsedTime = 0;

	bestFoundTimes.clear();

	if (bestPath.size() != 0) {
		bestPath.clear();
		
	}
	bestPathCost = INT_MAX;
	bestPath.clear();


	generatePopulation(populationSize);
	
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	
	while (elapsedTime < stopTime) {
		for (int i = 0; i < populationSize / 2; i++)
		{
			std::vector<int> parent1 = tournamentSelection();
			std::vector<int> parent2 = tournamentSelection();

			while (parent1 == parent2) {
				parent2 = tournamentSelection();
			}

			int randomProb = randomFloat(gen);

			if (randomProb < crossoverProb) {
				std::vector<int> child1(numberOfCities + 1, 0);
				std::vector<int> child2(numberOfCities + 1, 0);

				switch (crossoverType) {
				case 0:
					orderCrossover(parent1, parent2, child1, child2);
					break;
				case 1:
					partiallyMatchedCrossover(parent1, parent2, child1, child2);
					break;
				default:
					break;
				}

				switch (mutationType) {
				case 0:
					child1 = swapMutation(child1);
					child2 = swapMutation(child2);
					break;
				case 1:
					child1 = invertionMutation(child1);
					child2 = invertionMutation(child2);
					break;
				default:
					break;
				}

				newPopulation.push_back(child1);
				newPopulation.push_back(child2);

			}
			else {
				newPopulation.push_back(parent1);
				newPopulation.push_back(parent2);
			}
		}
		population = newPopulation;
		newPopulation.clear();

		for (int i = 0; i < population.size(); i++)
		{
			
			int tempFitness = calculateFitness(population[i]);
			//std::cout << tempFitness << std::endl;
			
			if (bestPathCost > tempFitness)
			{
				
				//std::cout << bestPathCost << std::endl;
				bestPathCost = tempFitness;
				bestPath = population[i];
				QueryPerformanceCounter(&foundBestPathTime);
				bestPathTime = static_cast<double>(foundBestPathTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
				std::vector<double> tempElement;
				tempElement.push_back(bestPathCost);
				tempElement.push_back(bestPathTime);
				bestFoundTimes.push_back(tempElement);
				//tylko do testu
				
			}
		}


		QueryPerformanceCounter(&endTime);
		elapsedTime = static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
		//std::cout << "Elapsed time:" << elapsedTime << std::endl;
	}

}

void GeneticAlgorithm::orderCrossover(std::vector<int> &parent1, std::vector<int> &parent2, std::vector<int> &child1, std::vector<int> &child2)
{
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::uniform_int_distribution<int> randomInt(1, numberOfCities - 1);

	//generowanie poczatku i konca wycinka
	int firstInt = randomInt(gen);
	int secondInt = randomInt(gen);

	while (firstInt == secondInt) {
		secondInt = randomInt(gen);
	}

	int startInt = min(firstInt, secondInt);
	int endInt = max(firstInt, secondInt);

	std::vector<bool> visited1(numberOfCities, false);
	std::vector<bool> visited2(numberOfCities, false);

	// skopiowanie losowego fragmentu
	for (int i = startInt; i <= endInt; i++)
	{
		child1[i] = parent1[i];
		child2[i] = parent2[i];
		visited1[child1[i]] = true;
		visited2[child2[i]] = true;
	}
	//indeks elementu gdzie zaczyanamy kopiowanie z 2-go rodzica
	int currentCopyIndex = (endInt + 1) % (numberOfCities);
	int currentCopySourceIndex = (endInt + 1) % (numberOfCities);
	if (currentCopyIndex == 0) currentCopyIndex = 1;
	if (currentCopySourceIndex == 0) currentCopySourceIndex = 1;
	bool isVisited;
	
	//kopiowanie pzoostalych elementow z rodzica2 do dziecka1
	while (currentCopyIndex != startInt)
	{

		
		if (!visited1[parent2[currentCopySourceIndex]]) {
			child1[currentCopyIndex] = parent2[currentCopySourceIndex];
			visited1[child1[currentCopyIndex]] = true;
			currentCopyIndex = (currentCopyIndex + 1) % (numberOfCities);
			if (currentCopyIndex == 0) currentCopyIndex = 1;
		}
		currentCopySourceIndex = (currentCopySourceIndex + 1) % (numberOfCities);
		if (currentCopySourceIndex == 0) currentCopySourceIndex = 1;

		
	}

	currentCopyIndex = (endInt + 1) % (numberOfCities);
	currentCopySourceIndex = (endInt + 1) % (numberOfCities);
	if (currentCopyIndex == 0) currentCopyIndex = 1;
	if (currentCopySourceIndex == 0) currentCopySourceIndex = 1;

	while(currentCopyIndex != startInt)
	{
		if (!visited2[parent1[currentCopySourceIndex]]) {
			
			child2[currentCopyIndex] = parent1[currentCopySourceIndex];
			visited2[child2[currentCopyIndex]] = true;
			currentCopyIndex = (currentCopyIndex + 1) % (numberOfCities);
			if (currentCopyIndex == 0) currentCopyIndex = 1;	
		}
		currentCopySourceIndex = (currentCopySourceIndex + 1) % (numberOfCities);
		if (currentCopySourceIndex == 0) currentCopySourceIndex = 1;
		
	}
}

void GeneticAlgorithm::partiallyMatchedCrossover(std::vector<int> &parent1, std::vector<int> &parent2, std::vector<int>& child1, std::vector<int>& child2)
{
	//usuwanie startowego miasta ( i tak nie mozemy go podmieniac,
	//a dzieki temu zarzadznie indeksami staje sie prostsze)
	child1.pop_back();
	child1.erase(child1.begin());
	child2.pop_back();
	child2.erase(child2.begin());
	parent1.pop_back();
	parent1.erase(parent1.begin());
	parent2.pop_back();
	parent2.erase(parent2.begin());

	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::uniform_int_distribution<int> randomInt(0, child1.size() - 1);
	

	//generowanie poczatku i konca wycinka
	int firstInt = randomInt(gen);
	int secondInt = randomInt(gen);

	while (firstInt == secondInt) {
		secondInt = randomInt(gen);
	}

	int startInt = min(firstInt, secondInt);
	int endInt = max(firstInt, secondInt);
	std::vector<int> unusedCities1;
	std::vector<int> unusedCities2;
	std::unordered_map<int, int> map1;
	std::unordered_map<int, int> map2;
	// skopiowanie losowego fragmentu
	for (int i = startInt; i <= endInt; i++)
	{
		child1[i] = parent1[i];
		child2[i] = parent2[i];
		map1[parent1[i]] = parent2[i];
		map2[parent2[i]] = parent1[i];
	}

	for (int i = 0; i < parent1.size(); i++)
	{
		if (i < startInt || i > endInt) {
			int current1 = parent2[i];
			int current2 = parent1[i];
			while (map1.find(current1) != map1.end()) {
				current1 = map1[current1];
			}
			
			child1[i] = current1;
			while (map2.find(current2) != map2.end()) {
				current2 = map2[current2];
			}
			child2[i] = current2;
		}
	}

	//dodawanie miasta startowego i konowego spowrotem do sciezki
	child1.insert(child1.begin(), 0);
	child1.push_back(0);
	child2.insert(child2.begin(), 0);
	child2.push_back(0);

}

std::vector<int> GeneticAlgorithm::tournamentSelection() 
{
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::uniform_int_distribution<int> randomInt(0, population.size() - 1);
	std::vector<int> tournamentTaken;
	int randomElementOfPopulation;
	int bestParent = 0;
	int bestFitness = INT_MAX;
	bool isTaken;
	int tempIterator = 0;
	while (tempIterator <= populationSize / 100) {
		isTaken = false;
		randomElementOfPopulation = randomInt(gen);

		for (int j = 0; j < tournamentTaken.size(); j++)
		{
			if (tournamentTaken[j] == randomElementOfPopulation) {
				isTaken = true;
				break;
			}
		}

		if (isTaken)
			continue;
		int tempFitness = calculateFitness(population[randomElementOfPopulation]);
		tournamentTaken.push_back(randomElementOfPopulation);
		tempIterator++;
		if (bestFitness > tempFitness)
		{
			bestFitness = tempFitness;
			bestParent = randomElementOfPopulation;
		}
	}

	//element o najnizszym koszcie
	return population[bestParent];
}

int GeneticAlgorithm::calculateFitness(std::vector<int> path) 
{
	int cost = 0;

	for (int i = 0; i < numberOfCities ; i++)
	{
		cost += matrix[path[i]][path[i+1]];
	}
	
	return cost;
}

std::vector<int> GeneticAlgorithm::swapMutation(std::vector<int> path)
{
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::uniform_int_distribution<int> randomInt(1, numberOfCities - 1);
	std::uniform_real_distribution<float> randomFloat(0, 1);

	float randomProb = randomFloat(gen);

	if (randomProb < mutationProb)
	{
		for (int i = 0; i < numberOfCities /10; i++)
		{
		int firstInt = randomInt(gen);
		int secondInt = randomInt(gen);

		while (firstInt == secondInt) {
			secondInt = randomInt(gen);
		}

		std::swap(path[firstInt], path[secondInt]);
		}
	}
	
	return path;
}

std::vector<int> GeneticAlgorithm::invertionMutation(std::vector<int> path)
{
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::uniform_int_distribution<int> randomInt(1, numberOfCities - 1);
	std::uniform_real_distribution<float> randomFloat(0, 1);

	float randomProb = randomFloat(gen);
	std::vector<int> fragmentToCopy;
	if (randomProb < mutationProb)
	{
		int startIndex = randomInt(gen);
		int endIndex = randomInt(gen);
		while (startIndex == endIndex) {
			endIndex = randomInt(gen);
		}
		int start = min(startIndex, endIndex);
		int end = max(startIndex, endIndex);
		std::reverse(path.begin() + start, path.begin() + end);
	}

	return path;
}

void GeneticAlgorithm::generatePopulation(int populationSize)
{
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	population.clear();
	for (int i = 0; i < populationSize; i++)
	{
		std::vector<int> path;
		for (int j = 0; j < numberOfCities; j++)
		{
			path.push_back(j);
		}
		path.push_back(0);

		//przetasowanie sciezki bez miasta startowego i koncowego
		std::shuffle(path.begin() + 1, path.end() - 1, gen);
		
		population.push_back(path);
	}
}


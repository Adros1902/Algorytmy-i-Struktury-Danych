#pragma once
#include <iostream>
#include <vector>
class MyInOut
{
public:
	int numberOfCities;

	int numberOfCitiesFromFile;

	int** matrix;

	int** matrixFromFile;

	int** createMatrixFromFile(std::string fileName);

	void generateMatrix(int size);

	int getNumberOfCities(std::string fileName);

	void saveToFile(std::string fileName, int numberOfCities, std::vector<int> bestPath);

	std::vector<int> readPath(std::string fileName);

	void calculateCostFromFile(std::string fileNamePath, std::string fileNamematrix);
};


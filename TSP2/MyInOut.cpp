#include "MyInOut.h"
#include "pugixml.hpp"
#include <fstream>
#include <iostream>
#include <vector>

int** MyInOut::createMatrixFromFile(std::string fileName)
{
	
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(fileName.c_str());

	std::cout << "Load result: " << result.description() << std::endl;

	pugi::xml_node tsp = doc.child("travellingSalesmanProblemInstance");

	pugi::xml_node graph = tsp.child("graph");

	if (graph) {
		generateMatrix(numberOfCities);
		int currentStartVertex = 0;
		for (pugi::xml_node vertex : graph.children("vertex")) {
			for (pugi::xml_node edge : vertex.children("edge")) {
				int currentEndVertex = edge.text().as_int();
				double tempValue = edge.attribute("cost").as_double();
				matrix[currentStartVertex][currentEndVertex] = static_cast<int>(tempValue);
			}
			currentStartVertex++;
		}
	}
    return matrix;
}

void MyInOut::generateMatrix(int size)
{
	matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}
}

int MyInOut::getNumberOfCities(std::string fileName)
{
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(fileName.c_str());

	std::cout << "Load result: " << result.description() << std::endl;

	pugi::xml_node tsp = doc.child("travellingSalesmanProblemInstance");

	pugi::xml_node graph = tsp.child("graph");

	if (graph) {
		numberOfCities = std::distance(graph.children("vertex").begin(), graph.children("vertex").end());
	}
	return numberOfCities;
}

void MyInOut::saveToFile(std::string fileName, int numberOfCities, std::vector<int> bestPath)
{
	std::ofstream outputFile(fileName);

	if (outputFile.is_open()) {
		outputFile << numberOfCities << "\n";
		for (int i = 0; i < bestPath.size(); i++)
		{
			outputFile << bestPath[i] << "\n";
		}
		outputFile.close();
	}
}

std::vector<int> MyInOut::readPath(std::string fileName)
{
	std::ifstream inputFile(fileName);
	std::vector<int> pathFromFile;
	if (inputFile.good()) {
		if (inputFile.is_open()) {
			inputFile >> numberOfCitiesFromFile;
			for (int i = 0; i < numberOfCitiesFromFile; i++)
			{
				int temp;
				inputFile >> temp;
				pathFromFile.push_back(temp);
			}
		}
	}
	inputFile.close();
	return pathFromFile;
}

void MyInOut::calculateCostFromFile(std::string fileNamePath, std::string fileNamematrix)
{
	numberOfCitiesFromFile = getNumberOfCities(fileNamematrix);
	matrixFromFile = createMatrixFromFile(fileNamematrix);
	std::vector<int> path = readPath(fileNamePath);
	int pathCost = 0;
	for (int i = 0; i < numberOfCitiesFromFile; i++)
	{
		int startCity, endCity;
		startCity = path[i];
		endCity = path[i + 1];
		pathCost += matrixFromFile[startCity][endCity];
	}
	std::cout << "Obliczony koszt: " << pathCost << std::endl;
}

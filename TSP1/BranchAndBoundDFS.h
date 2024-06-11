#pragma once
#include <string>
#include <vector>
#include "Node.h"
class BranchAndBoundDFS
{
public:
	int cityNumber = 0;

	int** matrix;

	int finalCost;

	std::vector<int> finalPath;

	~BranchAndBoundDFS();
	
	void createFromFile(std::string fileName);

	void generateMatrix(int size);

	void printMatrix();

	int branchAndBoundAlgorithm();

	int reduceRows(Node* node);

	int reduceColums(Node* node);

	int calculateCost(Node* node);

	void generateRandomMatrix(int size);

	void printResult();

	void recursive(int vertex);
};


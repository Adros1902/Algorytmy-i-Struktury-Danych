#pragma once
#include <cstddef>
#include "MyList.h"
#include <string>
class DynamicProgramming
{
public:
	int cityNumber = 0;

	int last;

	int result;

	int** matrix = NULL;

	int** memory = NULL;

	int** previous = NULL;

	MyList bestPath;

	MyList currentPath;

	DynamicProgramming();

	~DynamicProgramming();

	void createFromFile(std::string fileName);

	void generateMatrix(int size);

	void printMatrix();

	void dynamicProgramming();

	void printResult();

	void printPath(int bitmask, int vertex);

	void generateRandomMatrix(int size);
	
};


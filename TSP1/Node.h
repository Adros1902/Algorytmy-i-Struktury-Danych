#pragma once
#include "MyList.h"
#include "iostream"
#include <vector>
class Node
{
public:
	Node();

	~Node();

	Node* newNode(int cityNumber, int** parentMatrix, std::vector<int> parentPath, int endVertex);

	std::vector<int> path;

	int** reducedMatrix;

	int cost = 0;

	int cityNumber;

	int vertex;
};


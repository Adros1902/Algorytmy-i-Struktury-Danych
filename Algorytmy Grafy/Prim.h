#pragma once
#include <string>
#include "Heap.h"
#include "List.h"
#include "ListOfAdjency.h"
class Prim
{
public:
	int vertexNumber = 0;

	bool firstTime;

	int edgeNumber = 0;

	int** matrix = NULL;

	ListOfAdjency* list;

	//Heap heap;

	List mstEdgeListMatrix;

	List mstEdgeList;

	Prim();

	~Prim();

	void createFromFile(std::string filename);

	void createListFromFile(std::string filename);

	void generateMatrix(int size);

	void generateGraph(int numberOfVertex, int density);

	void printMatrix();

	void printList();

	void primAlgorithmMatrix();

	void primAlgorithmList();

	void printResultFromMatrix();

	void printResultFromList();

	void deleteMatrix();

	void deleteList();
};


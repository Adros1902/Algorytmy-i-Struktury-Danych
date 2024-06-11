#pragma once
#include <string>
#include "Edge.h"

class Heap
{
public:
	int inputSize;

	Heap(int inputSize);

	~Heap();

	Edge* heap;

	int size = 0;

	int getParent(int i);

	int getLeftSon(int i);

	int getRightSon(int i);

	//bool createHeapFromFile(std::string fileName);

	void insertEdgeToHeap(Edge edge);

	void heapifyBottom(int index);

	Edge deleteRoot();

	void repairUp(int index);
};


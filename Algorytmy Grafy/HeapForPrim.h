#pragma once
#include "VertexPrim.h"
class HeapForPrim
{
public:
	int inputSize;

	HeapForPrim(int inputSize);

	~HeapForPrim();

	VertexPrim* heap;

	int size = 0;

	int getParent(int i);

	int getLeftSon(int i);

	int getRightSon(int i);

	//bool createHeapFromFile(std::string fileName);

	void insertVertexToHeap(VertexPrim edge);

	void heapifyBottom(int index);

	VertexPrim deleteRoot();

	void repairUp(int index);

	bool searchForElement(int index);

	void editElement(int index, int newKey);
};


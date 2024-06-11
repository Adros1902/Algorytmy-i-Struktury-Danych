#pragma once
class Heap
{

	Heap();

	~Heap();

	int* heap;

	int size;

	int getParent(int i);

	int getLeftSon(int i);

	int getRightSon(int i);

	void insertValueToHeap(int value);

	void heapify(int index);

	void printElementsIntable();
};


#include "Heap.h"
#include "Edge.h"
#include <iostream>
#include <fstream>


Heap::Heap(int inputSize)
{
	size = 0;
	heap = new Edge [2*inputSize];

}

Heap::~Heap()
{
	delete[] heap;
}
// metody zwracajace rodzica i synow
int Heap::getParent(int i)
{
	return (i - 1) / 2;
}

int Heap::getLeftSon(int i)
{
	return 2 * i + 1;
}

int Heap::getRightSon(int i)
{
	return 2 * i + 2;
}


//wstawienie wartosci i naprawa kopca
void Heap::insertEdgeToHeap(Edge edge)
{
		heap[size] = edge;
		size++;
		int currentIndex = size-1;
		repairUp(currentIndex);
}

// usuwanie elementu i naprawa
Edge Heap::deleteRoot()
{	
	int index = 0;
	Edge edgeToExtract = heap[index];
	heap[index] = heap[size - 1];
	size--;
	//repairUp(index);
	heapifyBottom(index);
	return edgeToExtract;
}


void Heap::repairUp(int index)							// naprawianie kopca w gore
{
	int parentIndex = getParent(index);
	if (heap[index].weight < heap[parentIndex].weight && index > 0) {
		Edge tempValueParent = heap[parentIndex];
		heap[parentIndex] = heap[index];
		heap[index] = tempValueParent;
		index = parentIndex;
		repairUp(index);
	}

}

void Heap::heapifyBottom(int index)						// naprawianie kopca w dol
{
	int smallestValueIndex = index;
	int leftSonIndex = getLeftSon(index);
	int rightSonIndex = getRightSon(index);

	if (heap[leftSonIndex].weight < heap[index].weight && leftSonIndex < size) {
		smallestValueIndex = leftSonIndex;
	}
	if (heap[rightSonIndex].weight < heap[smallestValueIndex].weight && rightSonIndex < size) {
		smallestValueIndex = rightSonIndex;
	}
	if (smallestValueIndex != index) {
		Edge tempSwapValue = heap[index];
		heap[index] = heap[smallestValueIndex];
		heap[smallestValueIndex] = tempSwapValue;
		heapifyBottom(smallestValueIndex);
	}
}
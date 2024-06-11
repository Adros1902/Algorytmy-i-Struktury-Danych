#include "HeapForPrim.h"
#include "VertexPrim.h"
#include <iostream>
#include <fstream>


HeapForPrim::HeapForPrim(int inputSize)
{
	size = 0;
	heap = new VertexPrim[2 * inputSize];

}

HeapForPrim::~HeapForPrim()
{
	delete[] heap;
}
// metody zwracajace rodzica i synow
int HeapForPrim::getParent(int i)
{
	return (i - 1) / 2;
}

int HeapForPrim::getLeftSon(int i)
{
	return 2 * i + 1;
}

int HeapForPrim::getRightSon(int i)
{
	return 2 * i + 2;
}


//wstawienie wartosci i naprawa kopca
void HeapForPrim::insertVertexToHeap(VertexPrim edge)
{
	heap[size] = edge;
	size++;
	int currentIndex = size - 1;
	repairUp(currentIndex);
}

// usuwanie elementu i naprawa
VertexPrim HeapForPrim::deleteRoot()
{
	int index = 0;
	VertexPrim edgeToExtract = heap[index];
	heap[index] = heap[size - 1];
	size--;
	//repairUp(index);
	heapifyBottom(index);
	return edgeToExtract;
}


void HeapForPrim::repairUp(int index)							// naprawianie kopca w gore
{
	int parentIndex = getParent(index);
	if (heap[index].key < heap[parentIndex].key && index > 0) {
		VertexPrim tempValueParent = heap[parentIndex];
		heap[parentIndex] = heap[index];
		heap[index] = tempValueParent;
		index = parentIndex;
		repairUp(index);
	}

}

bool HeapForPrim::searchForElement(int index)
{
	for (int i = 0; i < size; i++) {
		if (heap[i].vertex == index) {
			return true;
		}
	}
	return false;
}

void HeapForPrim::editElement(int index, int newKey)
{
	for (int i = 0; i < size; i++) {
		if (heap[i].vertex == index) {
			heap[i].key = newKey;
			repairUp(i);
			heapifyBottom(i);
			break;
		}
	}
}

void HeapForPrim::heapifyBottom(int index)						// naprawianie kopca w dol
{
	int smallestValueIndex = index;
	int leftSonIndex = getLeftSon(index);
	int rightSonIndex = getRightSon(index);

	if (heap[leftSonIndex].key < heap[index].key && leftSonIndex < size) {
		smallestValueIndex = leftSonIndex;
	}
	if (heap[rightSonIndex].key < heap[smallestValueIndex].key && rightSonIndex < size) {
		smallestValueIndex = rightSonIndex;
	}
	if (smallestValueIndex != index) {
		VertexPrim tempSwapValue = heap[index];
		heap[index] = heap[smallestValueIndex];
		heap[smallestValueIndex] = tempSwapValue;
		heapifyBottom(smallestValueIndex);
	}
}

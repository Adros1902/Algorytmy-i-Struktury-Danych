#include "Heap.h"
#include <iostream>

Heap::Heap()
{
	heap = new int[100];
	size = 0;
}

Heap::~Heap()
{
	delete heap;
}

int Heap::getParent(int i)
{
	return (i-1)/2;
}

int Heap::getLeftSon(int i)
{
	return 2*i+1;
}

int Heap::getRightSon(int i)
{
	return 2*i+2;
}

void Heap::insertValueToHeap(int value)
{
	if (size == 0) {
		heap[0] = value;
		size++;
	}
	else {
		size++;
		heap[size] = value;
		int currentIndex = size;
		int parentIndex = getParent(currentIndex);

		while (currentIndex > 0 && heap[parentIndex] < heap[currentIndex]) {

			int tempValueParent = heap[parentIndex];
			heap[parentIndex] = heap[currentIndex];
			heap[currentIndex] = tempValueParent;
			currentIndex = parentIndex;
		}
	}
	
}

void Heap::printElementsIntable()
{
	for (int i = 0; i < size; i++) {
		std::cout << i << " " << std::endl;
	}
	std::cout << std::endl;
}



//void Heap::heapify(int index)
//{
//	if(get)
//}

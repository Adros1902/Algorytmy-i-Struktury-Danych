#include "Kruskal.h"
#include "Edge.h"
#include "fstream"
#include "iostream"
#include "DisjointSet.h"

Kruskal::Kruskal()
{
	matrix = nullptr;
	list = nullptr;
	firstTime = true;
	vertexNumber = 0;
	edgeNumber = 0;
}

Kruskal::~Kruskal()
{
	deleteMatrix();
	deleteList();
}

void Kruskal::generateMatrix(int size)
{
	matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}
}

// tworzenie grafu spojnego w sposob losowy - od razu dodaje do listy i macierzy, aby dane byly takie same
void Kruskal::generateGraph(int numberOfVertex, int density)
{
	generateMatrix(numberOfVertex);
	//tworzenie listy
	list = new ListOfAdjency[numberOfVertex];
	vertexNumber = numberOfVertex;
	float tempValue = std::round((vertexNumber * (vertexNumber - 1)) / 2.0f) * (density / 100.0f);
	edgeNumber = static_cast<int>(tempValue);
	if (edgeNumber < vertexNumber - 1) {
		edgeNumber = vertexNumber - 1;
	}
	//generowanie drzewa rozpinaj¹cego
	int* visited = new int[numberOfVertex];
	for (int i = 0; i < numberOfVertex; i++) {
		visited[i] = 0;
	}
	int tempVertex, tempEndVertex;
	int** edgeTable = new int*[edgeNumber];
	for (int i = 0; i < edgeNumber; i++) {
		edgeTable[i] = new int[2];
	}
	
	srand((unsigned)time(NULL));
	tempVertex = rand() % numberOfVertex;
	for (int i = 0; i < numberOfVertex - 1; i++) {
		while (true) {
			tempEndVertex = rand() % numberOfVertex;
			if (visited[tempEndVertex] == 0 && tempEndVertex != tempVertex) {
				edgeTable[i][0] = tempVertex;
				edgeTable[i][1] = tempEndVertex;
				visited[tempVertex] = 1;
				tempVertex = tempEndVertex;
				break;
			}
		}
	}
	delete[] visited;
	//dodawanie losowych krawedzi do powstalego drzewa rozpinajacego
	int iterator = numberOfVertex - 1;
	while (iterator < edgeNumber) {
		edgeTable[iterator][0] = rand() % numberOfVertex;
		edgeTable[iterator][1] = rand() % numberOfVertex;

		if (edgeTable[iterator][0] == edgeTable[iterator][1]) {
			continue;
		}
		else {
			for (int j = 0; j < iterator; j++) {
				if ((edgeTable[iterator][0] == edgeTable[j][0] && edgeTable[iterator][1] == edgeTable[j][1]) ||
					(edgeTable[iterator][0] == edgeTable[j][1] && edgeTable[iterator][1] == edgeTable[j][0])) {
					iterator--;
				}
			}
		}
		iterator++;
	}
	int randomWeight;
	EdgeForList tempEdge;
	EdgeForList secondTempEdge;
	for (int i = 0; i < edgeNumber; i++) {
		randomWeight = rand() % 9 + 1;
		matrix[edgeTable[i][0]][edgeTable[i][1]] = randomWeight;
		matrix[edgeTable[i][1]][edgeTable[i][0]] = randomWeight;
		tempEdge.endVertex = edgeTable[i][1];
		tempEdge.weight = randomWeight;
		secondTempEdge.endVertex = edgeTable[i][0];
		secondTempEdge.weight = randomWeight;
		list[edgeTable[i][0]].addElementToListTail(tempEdge);
		list[edgeTable[i][1]].addElementToListTail(secondTempEdge);
	}
	for (int i = 0; i < edgeNumber; i++) {
		delete[] edgeTable[i];
	}
	delete[] edgeTable;
}

// tworzenie macierzy z pliku
void Kruskal::createFromFile(std::string filename)
{
	std::ifstream inputFile(filename);

	if (inputFile.good()) {
		if (inputFile.is_open())
		{
			inputFile >> edgeNumber >> vertexNumber;
			generateMatrix(vertexNumber);
			int startVertex, endVertex, weight;
			for (int i = 0; i < edgeNumber; i++)
			{
				inputFile >> startVertex >> endVertex >> weight;
				matrix[startVertex][endVertex] = weight;
				matrix[endVertex][startVertex] = weight;
			}
		}
	}
}

void Kruskal::createListFromFile(std::string filename)
{
	std::ifstream inputFile(filename);
	if (inputFile.good()) {
		if (inputFile.is_open())
		{
			inputFile >> edgeNumber >> vertexNumber;
			//tworzenie listy sasiedztwa
			list = new ListOfAdjency[vertexNumber];

			int startVertex, endVertex, weight;
			EdgeForList tempEdge;
			EdgeForList secondTempEdge;
			for (int i = 0; i < edgeNumber; i++)
			{
				inputFile >> startVertex >> endVertex >> weight;
				tempEdge.endVertex = endVertex;
				tempEdge.weight = weight;
				secondTempEdge.endVertex = startVertex;
				secondTempEdge.weight = weight;
				list[startVertex].addElementToListTail(tempEdge);
				list[endVertex].addElementToListTail(secondTempEdge);
			}
		}
	}
}



void Kruskal::printMatrix() {
	std::cout <<std::endl << "Macierz:" << std::endl;
	std::cout << "    ";
	for (int i = 0; i < vertexNumber; i++)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::cout << "----------------------" << std::endl;

	for (int i = 0; i < vertexNumber; i++) {
		std::cout << i << " | ";
		for (int j = 0; j < vertexNumber; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Kruskal::printList() {
	std::cout << std::endl << "Lista" << std::endl;
	std::cout << "----------------------" << std::endl;

	
	for (int i = 0; i < vertexNumber; i++) {
		std::cout << i << " | ";
		for (int j = 0; j < list[i].size; j++) {
			EdgeForList tempEdge;
			tempEdge = list[i].returnListElements();
			std::cout << tempEdge.endVertex << "-" << tempEdge.weight << "; ";
		}
		list[i].listElementIterator = 0;
		std::cout << std::endl;
	}
}


void Kruskal::kruskalAlgorithmMatrix()
{
	DisjointSet disjointSet(vertexNumber);
	Heap queue(edgeNumber);

	//tworzenie kolejki priorytetowej z krawedziami - graf nieskierowany wiec dodaje tylko polowe macierzy, bo jest ona symetryczna
	for (int i = 0; i < vertexNumber; i++) {
		for (int j = i; j < vertexNumber; j++) {
			if (matrix[i][j] != 0) {
				Edge edge;
				edge.startVertex = i;
				edge.endVertex = j;
				edge.weight = matrix[i][j];
				queue.insertEdgeToHeap(edge);
			}
		}
	}
	for (int i = 0; i < edgeNumber; i++) {
		Edge edgeToCheck = queue.deleteRoot();	//wyciaganie z kolejki krawedzi o najmnniejszej wadze
		if (disjointSet.findSet(edgeToCheck.startVertex) != disjointSet.findSet(edgeToCheck.endVertex)) {
			mstEdgeListMatrix.addElementToListTail(edgeToCheck);
			disjointSet.unionSets(edgeToCheck.startVertex, edgeToCheck.endVertex);
		}
	}
}

void Kruskal::kruskalAlgorithmList() 
{
	DisjointSet disjointSetList(vertexNumber);
	Heap queueList(2*edgeNumber);
	for (int i = 0; i < vertexNumber; i++) {
		for (int j = 0; j < list[i].size; j++) {
			EdgeForList tempEdge;
			Edge edge;
			tempEdge = list[i].returnListElements();
			edge.startVertex = i;
			edge.endVertex = tempEdge.endVertex;
			edge.weight = tempEdge.weight;
			queueList.insertEdgeToHeap(edge);
		}
		list[i].listElementIterator = 0;
	}
	for (int i = 0; i < edgeNumber*2; i++) {
		Edge edgeToCheck = queueList.deleteRoot();	//wyciaganie z kolejki krawedzi o najmnniejszej wadze
		if (disjointSetList.findSet(edgeToCheck.startVertex) != disjointSetList.findSet(edgeToCheck.endVertex)) {
			mstEdgeList.addElementToListTail(edgeToCheck);
			disjointSetList.unionSets(edgeToCheck.startVertex, edgeToCheck.endVertex);
		}
	}
}


void Kruskal::printResultFromMatrix() 
{
	int mstWeight = 0;
	std::cout << std::endl << "Wynik MST Kruskal z macierzy:" << std::endl;
	for (int i = 0; i < vertexNumber - 1; i++)
	{
		Edge currentEdge;
		currentEdge = mstEdgeListMatrix.returnListElements();
		mstWeight = mstWeight + currentEdge.weight;
		std::cout << currentEdge.startVertex << " " << currentEdge.endVertex << " " << currentEdge.weight << std::endl;
	}
	std::cout << "Waga calkowita: " << mstWeight;
}

void Kruskal::printResultFromList()
{
	
	int mstWeight = 0;
	std::cout << std::endl << "Wynik MST Kruskal z listy:" << std::endl;
	for (int i = 0; i < vertexNumber - 1; i++)
	{
		Edge currentEdge;
		currentEdge = mstEdgeList.returnListElements();
		mstWeight = mstWeight + currentEdge.weight;
		std::cout << currentEdge.startVertex << " " << currentEdge.endVertex << " " << currentEdge.weight << std::endl;
	}
	std::cout << "Waga calkowita: " << mstWeight;
}


void Kruskal::deleteMatrix()
{
	for (int i = 0; i < vertexNumber; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

void Kruskal::deleteList()
{
	if (list != nullptr) {
		for (int i = 0; i < vertexNumber; i++) {
			list[i].~ListOfAdjency();
		}
		delete[] list;
	}
}



#include "BranchAndBound.h"
#include "fstream"
#include "iostream"
#include <queue>
#include "Node.h"
#define INF INT_MAX

BranchAndBound::~BranchAndBound()
{
	if (cityNumber != 0) {
		for (int i = 0; i < cityNumber; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		cityNumber = 0;
		finalCost = 0;
		finalPath.clear();
	}
}

void BranchAndBound::createFromFile(std::string fileName)
{
	BranchAndBound::~BranchAndBound();
	std::ifstream inputFile(fileName);
	if (inputFile.good()) {
		if (inputFile.is_open()) {
			inputFile >> cityNumber;
			generateMatrix(cityNumber);
			for (int i = 0; i < cityNumber; i++) {
				for (int j = 0; j < cityNumber; j++) {
					inputFile >> matrix[i][j];
				}
			}
		}
	}
}

void BranchAndBound::generateMatrix(int size)
{
	
	matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}
}

void BranchAndBound::printMatrix()
{
	std::cout << "Macierz:" << std::endl;
	for (int i = 0; i < cityNumber; i++) {
		for (int j = 0; j < cityNumber; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

struct CompareNodes {
	bool operator()(const Node* node1,const Node* node2) {
		return node1->cost > node2->cost;
	}
};

int BranchAndBound::branchAndBoundAlgorithm()
{
	//kolejka priorytetowa z wezlami, sortuje po koszcie - najwyzszy priorytet to najnizszy koszt)
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priorityQueue;
	std::vector<int> path;

	Node* tempRoot = new Node;
	Node* root = tempRoot->newNode(cityNumber, matrix, path, 0);
	delete tempRoot;
	//tworzenie pierwszego elementu
	root->cost = calculateCost(root);
	priorityQueue.push(root);

	while (!priorityQueue.empty()) {
		//Node node(cityNumber,matrix,path,0);
		Node* node = priorityQueue.top();
		priorityQueue.pop();

		int startVertex = node->vertex;
		//jesli znaleziono sciezke, przypisanie pol do wynikow i usuwanie pzoostalosci
		if (node->path.size() == cityNumber) {
			node->path.push_back(0);
			finalPath = node->path;
			finalCost = node->cost;
			while (!priorityQueue.empty()) {
				Node* tempNode = priorityQueue.top();
				priorityQueue.pop();
				delete tempNode;
			}
			int cost = node->cost;
			delete node;
			return cost;
		}

		for (int i = 0; i < cityNumber; i++)
		{
			if (node->reducedMatrix[startVertex][i] != INF && node->reducedMatrix[startVertex][i] != -1) {
				Node* childNodeTemp = new Node;
				Node* childNode = childNodeTemp->newNode(cityNumber, node->reducedMatrix, node->path, i);
				delete childNodeTemp;
				// obliczanie kosztu (dolnej granicy) dla wezla syna (kolejny wyszukany BFS)
				childNode->cost = node->cost + node->reducedMatrix[startVertex][i] + calculateCost(childNode);
				//dodanie go do kolejki priorytetowej
				priorityQueue.push(childNode);

			}
		}
		delete node;
	}
}

int BranchAndBound::reduceRows(Node* node)
{
	int reducedValue = 0;

	for (int i = 0; i < cityNumber; i++)
	{
		//wyznaczenie najmniejszej wartosci w wierszu
		int smallestNumber = INF;
		int temp;
		for (int j = 0; j < cityNumber; j++) {
			if (node->reducedMatrix[i][j] != INF && node->reducedMatrix[i][j] != -1) {
				temp = node->reducedMatrix[i][j];
				if (temp < smallestNumber) {
					smallestNumber = temp;
				}
			}
		}
		//odejmowanie najmniejszej wartosci i dodawanie do calosci, by obliczyc dolna granice
		if (smallestNumber != INF && smallestNumber != 0) {
			for (int j = 0; j < cityNumber; j++) {
				if(node->reducedMatrix[i][j] != -1 && node->reducedMatrix[i][j] != INF)
					node->reducedMatrix[i][j] = node->reducedMatrix[i][j] - smallestNumber;
			}
			reducedValue = reducedValue + smallestNumber;
		}
	}

	return reducedValue;
}

int BranchAndBound::reduceColums(Node* node)
{
	int reducedValue = 0;
	for (int i = 0; i < cityNumber; i++)
	{
		//wyznaczenie najmniejszej wartosci w kolumnie
		int smallestNumber = INF;
		int temp;
		for (int j = 0; j < cityNumber; j++) {
			if (node->reducedMatrix[j][i] != INF && node->reducedMatrix[j][i] != -1) {
				temp = node->reducedMatrix[j][i];
				if (temp < smallestNumber) {
					smallestNumber = temp;
				}
			}
		}
		//odejmowanie najmniejszej wartosci i dodawanie do calosci, by obliczyc dolna granice
		if (smallestNumber != INF && smallestNumber != 0) {
			for (int j = 0; j < cityNumber; j++) {
				if(node->reducedMatrix[j][i] != -1 && node->reducedMatrix[j][i] != INF)
					node->reducedMatrix[j][i] = node->reducedMatrix[j][i] - smallestNumber;
			}
			reducedValue = reducedValue + smallestNumber;
		}
	}

	return reducedValue;
}

int BranchAndBound::calculateCost(Node* node)
{
	// dodawanie wyliczonych wartosci
	int cost = 0;

	cost = reduceRows(node);

	cost = cost + reduceColums(node);

	return cost;
}

void BranchAndBound::generateRandomMatrix(int size)
{
	BranchAndBound::~BranchAndBound();
	cityNumber = size;
	generateMatrix(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
		{
			if (i == j) {
				matrix[i][j] = -1;
			}
			else {
				matrix[i][j] = (rand() % RAND_MAX - 1) + 1;
			}

		}
	}
}

void BranchAndBound::printResult()
{
	std::cout << "Minimalny koszt: " << finalCost << std::endl;
	std::cout << "Sciezka: " << std::endl;
	for (int i = 0; i < cityNumber + 1; i++)
	{
		std::cout << finalPath[i] << " ";
	}
	std::cout << std::endl;
}

#include "BranchAndBoundDFS.h"
#include "fstream"
#include "iostream"
#include <queue>
#include "Node.h"
#include <stack>
#define INF INT_MAX

BranchAndBoundDFS::~BranchAndBoundDFS()
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

void BranchAndBoundDFS::createFromFile(std::string fileName)
{
	BranchAndBoundDFS::~BranchAndBoundDFS();
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

void  BranchAndBoundDFS::generateMatrix(int size)
{
	matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}
}

void  BranchAndBoundDFS::printMatrix()
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


int  BranchAndBoundDFS::branchAndBoundAlgorithm()
{
	finalCost = INF;
	std::vector<int> path;
	// roznica - stos zamiast kolejki priorytetowej
	std::stack<Node*> stack;
	Node* tempRoot = new Node;
	Node* root = tempRoot->newNode(cityNumber, matrix, path, 0);
	delete tempRoot;

	root->cost = calculateCost(root);

	stack.push(root);

	while(!stack.empty()){
		Node* node = stack.top();
		stack.pop();

		int startVertex = node->vertex;

		if (node->path.size() == cityNumber) {
			node->path.push_back(0);
			if (node->cost < finalCost) {
				finalCost = node->cost;
				finalPath = node->path;
			}
		}
		else {

			for (int i = 0; i < cityNumber; i++)
			{
				if (node->reducedMatrix[startVertex][i] != INF && node->reducedMatrix[startVertex][i] != -1) {
					Node* childNodeTemp = new Node;
					Node* childNode = childNodeTemp->newNode(cityNumber, node->reducedMatrix, node->path, i);
					delete childNodeTemp;
					childNode->cost = node->cost + node->reducedMatrix[startVertex][i] + calculateCost(childNode);
					// sprawdzenie czy badany wezel jest lepszy niz najlepszy dotychczas znaleziony
					if (childNode->cost < finalCost) {
						stack.push(childNode);
					}
					else {
						delete childNode;
					}
				}
			}
		}
		delete node;
	}
	while (!stack.empty()) {
		Node* tempNode = stack.top();
		stack.pop();
		delete tempNode;
	}
	return finalCost;
}

int  BranchAndBoundDFS::reduceRows(Node* node)
{
	int reducedValue = 0;

	for (int i = 0; i < cityNumber; i++)
	{
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
		if (smallestNumber != INF && smallestNumber != 0) {
			for (int j = 0; j < cityNumber; j++) {
				if (node->reducedMatrix[i][j] != -1 && node->reducedMatrix[i][j] != INF)
					node->reducedMatrix[i][j] = node->reducedMatrix[i][j] - smallestNumber;
			}
			reducedValue = reducedValue + smallestNumber;
		}
	}

	return reducedValue;
}

int  BranchAndBoundDFS::reduceColums(Node* node)
{
	int reducedValue = 0;
	for (int i = 0; i < cityNumber; i++)
	{
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
		if (smallestNumber != INF && smallestNumber != 0) {
			for (int j = 0; j < cityNumber; j++) {
				if (node->reducedMatrix[j][i] != -1 && node->reducedMatrix[j][i] != INF)
					node->reducedMatrix[j][i] = node->reducedMatrix[j][i] - smallestNumber;
			}
			reducedValue = reducedValue + smallestNumber;
		}
	}

	return reducedValue;
}

int  BranchAndBoundDFS::calculateCost(Node* node)
{
	int cost = 0;

	cost = reduceRows(node);

	cost = cost + reduceColums(node);

	return cost;
}

void BranchAndBoundDFS::generateRandomMatrix(int size)
{
	BranchAndBoundDFS::~BranchAndBoundDFS();
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

void BranchAndBoundDFS::printResult()
{
	std::cout << "Minimalny koszt: " << finalCost << std::endl;
	std::cout << "Sciezka: " << std::endl;
	for (int i = 0; i < cityNumber + 1; i++)
	{
		std::cout << finalPath[i] << " ";
	}
	std::cout << std::endl;
}

void BranchAndBoundDFS::recursive(int vertex)
{
}

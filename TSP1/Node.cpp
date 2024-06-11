#include "Node.h"
#include "iostream"

#define INF INT_MAX

Node::Node()
{

}

Node::~Node()
{
	for (int i = 0; i < cityNumber; i++)
	{
		delete[] reducedMatrix[i];
	}
	delete[] reducedMatrix;
}



Node* Node::newNode(int cityNumber, int** parentMatrix, std::vector<int> parentPath, int endVertex)
{
	Node* node = new Node;
	node->cityNumber = cityNumber;
	node->reducedMatrix = new int* [cityNumber];
	//tworzenie zredukowanej macierzy
	for (int i = 0; i < cityNumber; i++)
	{
		node->reducedMatrix[i] = new int[cityNumber];
	}

	for (int i = 0; i < cityNumber; i++) {
		for (int j = 0; j < cityNumber; j++)
		{
			node->reducedMatrix[i][j] = parentMatrix[i][j];
		}
	}

	for (int i = 0; i < parentPath.size(); i++)
	{
		node->path.push_back(parentPath[i]);
	}

	if (node->path.size() != 0) {
		for (int i = 0; i < cityNumber; i++)
		{
			//wykreslanie odpowiednich wierszy i kolumn
			node->reducedMatrix[node->path.back()][i] = INF;
			node->reducedMatrix[i][endVertex] = INF;
		}
		node->reducedMatrix[endVertex][node->path.back()] = INF;
	}

	node->path.push_back(endVertex);

	node->vertex = endVertex;
	return node;
}

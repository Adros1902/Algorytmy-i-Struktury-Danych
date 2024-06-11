#include "BruteForce.h"
#include "fstream"
#include "iostream"
#include "MyList.h"

#define INF 1e9

BruteForce::BruteForce()
{	
}

BruteForce::~BruteForce()
{
	if (cityNumber != 0) {
		for (int i = 0; i < cityNumber; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		delete[] visited;
		currentPath.deleteAllElementsOfList();
		bestPath.deleteAllElementsOfList();
		cityNumber = 0;
	}
}

void BruteForce::createFromFile(std::string fileName)
{
	BruteForce::~BruteForce();
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

void BruteForce::generateMatrix(int size)
{
	matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}
	visited = new bool[size];

	for (int i = 0; i < size; i++)
	{
		visited[i] = false;
	}

}

void BruteForce::printMatrix()
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

void BruteForce::bruteForceAlgorithmRecursion(int vertex)
{	
		currentPath.addElementToListTail(vertex);
		//sprawwdzenie czy juz nie przeszukalismy calej trasy (zlozonej z wszystkich wierzcholkow, bez powrotu do poczatkowego)
		if (currentPath.size != cityNumber ) {

			visited[vertex] = true;

			for (int i = 0; i < cityNumber; i++) {

				int tempElement = matrix[vertex][i];
				if (visited[i] || tempElement <=0) {
					continue;
				}
				//dodawanie wartosci danego elementu
				currentCost += tempElement;
				//warunek sprawdzajacy czy aktualny koszt nie przewyzsza juz najlepszego, jesli tak to pomijamy dalsze poszukiwania w tej trasie
				/*if (currentCost >= bestCost) {
					currentCost -= tempElement;
					continue;
				}*/
				//wywolanie rekurencyjne w poszukiwaniu kolejnego elementu
				bruteForceAlgorithmRecursion(i);

				currentCost -= tempElement;
				
				currentPath.deleteElementOfListTail();
			}
			visited[vertex] = false;
		}
		else {
			// dodanie do calej sciezki krawedzi laczacej wierzcholek koncowy (ten sam co poczatkowy) do ostatniego z wyszukanej trasy
			currentCost += matrix[vertex][startVertex];
			currentPath.addElementToListTail(0);
			//jesli znaleziona trasa ma mniejszy koszt niz dotychczasowa najlepsza, to je zamieniamy
			if (currentCost < bestCost) {
				bestCost = currentCost;
				
				if (bestPath.size != 0) {
					bestPath.deleteAllElementsOfList();
				}

				for (int i = 0; i < cityNumber + 1; i++)
				{
					bestPath.addElementToListTail(currentPath.returnListElements());
				}

			}
			// usuwamy dodany element (ostatni) i szukamy dalej
			currentCost -= matrix[vertex][startVertex];
			currentPath.deleteElementOfListTail();
		}
	

}

void BruteForce::bruteForce(int startVertex)
{
	bestCost = INF;
	currentCost = 0;
	this->startVertex = startVertex;
	bestPath.deleteAllElementsOfList();
	currentPath.deleteAllElementsOfList();
	bruteForceAlgorithmRecursion(startVertex);
}

void BruteForce::printResult()
{
	std::cout << "Koszt:" << std::endl;
	std::cout << bestCost << std::endl;
	std::cout << "Sciezka:" << std::endl;
	
	for (int i = 0; i < cityNumber + 1; i++)
	{
		std::cout << bestPath.returnListElements() << " ";
	}
}

void BruteForce::generateRandomMatrix(int size)
{
	BruteForce::~BruteForce();
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

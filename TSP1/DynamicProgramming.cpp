#include "DynamicProgramming.h"
#include "iostream"
#include "fstream"

#define INF 1e9

DynamicProgramming::DynamicProgramming()
{
	last = 0;
	result = INF;
}

DynamicProgramming::~DynamicProgramming()
{
	if (cityNumber != 0) {
		for (int i = 0; i < cityNumber; i++)
		{
			delete[] matrix[i];
		}

		for (int i = 0; i < (1 << cityNumber); i++)
		{
			delete[] memory[i];
			delete[] previous[i];
		}
		delete[] matrix;
		delete[] memory;
		delete[] previous;
		cityNumber = 0;
	}
}

void DynamicProgramming::createFromFile(std::string fileName)
{
	DynamicProgramming::~DynamicProgramming();
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

void DynamicProgramming::generateMatrix(int size)
{
	matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}

	memory = new int* [(1 << cityNumber)];
	previous = new int* [(1 << cityNumber)];

	for (int i = 0; i < (1 << cityNumber); i++) {
		memory[i] = new int[cityNumber];
		previous[i] = new int[cityNumber];
	}
}

void DynamicProgramming::printMatrix()
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

void DynamicProgramming::dynamicProgramming()
{
	//wypelnienie tabeli wartosci drog nieskonczonoscia, przed algorytmem 
	// (tabela kosztow dotarcia do odpowiedniego miasta z danej maski bitowej)
	for (int bitmask = 0; bitmask < (1 << cityNumber); bitmask++) {
		for (int i = 0; i < cityNumber; i++) {
			memory[bitmask][i] = INF;
		}
	}

	memory[1][0] = 0;

	//iteracja po maskach
	for (int bitmask = 1; bitmask < (1 << cityNumber); bitmask++)
	{
		//zaczynamy od 1, bo wchodzimy do miasta i, a wychodzimy z j
		for (int i = 1; i < cityNumber; i++)
		{
			//sprawdzenie czy dane miasto i zawiera sie w masce
			if (bitmask & (1 << i)) {
				for (int j = 0; j < cityNumber; j++)
				{	//sprawdzenie czy dane miasto j zawiera sie w masce
					if ((bitmask & (1 << j)) && i != j) {
						
						// sprawdzenie warunku czy obliczana trasa jest lepsza i czy dana krawedz istnieje 
						//(warunek sprawdzajacy czy znajduje sie lepsza trasa do i, korzystajac z juz uzyskanych masek dochodzacych do j i dodanie wartosci z macierzy j - i)
						// j - miasto z ktorego wychodzimy, i - miasto do ktorego wchodzimy

						if (memory[bitmask][i] > memory[bitmask ^ (1 << i)][j] + matrix[j][i] && matrix[j][i] > 0) {
							
							memory[bitmask][i] = memory[bitmask ^ (1 << i)][j] + matrix[j][i];

							//tablica pozwalajaca na pozniejsze odczytanie trasy
							previous[bitmask][i] = j;
						}
					}
				}
			}
		}
	}

	result = INF;
	// znalezienie najlepszej trasy w petli, zaczynamy od 1, bo miasto 0 jest zawsze na poczatku
	for (int i = 1; i < cityNumber; i++)
	{
		if (result > memory[(1 << cityNumber) - 1][i] + matrix[i][0]) {
			result = memory[(1 << cityNumber) - 1][i] + matrix[i][0];
			last = i;
		}
	}
}

void DynamicProgramming::printResult()
{
	std::cout << "Minimalny koszt:" << result << std::endl;
	std::cout << "Najkrotsza sciezka:" << std::endl;
	printPath((1 << cityNumber) - 1, last);
	std::cout << 0 << std::endl;
}

void DynamicProgramming::printPath(int bitmask, int vertex)
{
	if (vertex == 0) {
		std::cout << 0 << ' ';
		return;
	}
	printPath(bitmask ^ (1 << vertex), previous[bitmask][vertex]);
	std::cout << vertex << ' ';
}

void DynamicProgramming::generateRandomMatrix(int size)
{
	DynamicProgramming::~DynamicProgramming();
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



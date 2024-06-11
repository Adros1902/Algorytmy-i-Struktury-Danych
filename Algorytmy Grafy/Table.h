#pragma once
#include <string>

class Table
{
public:
	// konstruktor
	Table();
	// destruktor
	~Table();
	// rozmiar poczatkowy tablicy
	int size = 0;
	// wskaznik na poczatek tablicy
	int* table;
	// dodawanie elementu do tablicy
	void addElementToTable(int index, int number);
	// usuwanie elementu z tablicy
	void deleteElementFromTable(int index);
	// szukanie danego elementu
	bool findingNumber(int value);
};



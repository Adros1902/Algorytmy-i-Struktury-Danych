#include "Table.h"
#include <iostream>
#include <fstream>

//konstruktor
Table::Table()
{
	table = NULL;
}

//destruktor
Table::~Table()
{
	if (table != NULL) {
		delete table;
	}
}


// rozpatrywanie gdzie element ma byc wstawiony i obsluga wstawiania elementu do srodka tablicy
void Table::addElementToTable(int index, int number)
{
	if (size == 0) {
		table = new int[1];
		table[0] = number;
		size++;
	}
	else {

		int* newTableAdd = new int[size + 1];

		for (int i = 0; i < index; i++) {
			newTableAdd[i] = table[i];
		}
		newTableAdd[index] = number;
		for (int i = index; i < size; i++)
		{
			newTableAdd[i + 1] = table[i];
		}
		delete table;
		table = newTableAdd;
		size++;
	}
}

// usuniecie elementu z zadanego miejsca i obsluga usuwania ze srodka tablicy
void Table::deleteElementFromTable(int index)
{
	if (size == 1) {
		delete table;
		size--;
	}
	else {
		int* newTableDelete = new int[size - 1];
		for (int i = 0; i < index; i++) {
			newTableDelete[i] = table[i];
		}
		for (int i = index + 1; i < size; i++) {
			newTableDelete[i - 1] = table[i];
		}
		delete table;
		table = newTableDelete;
		size--;
	}
}


// szukanie podanej wartosci
bool Table::findingNumber(int value)
{
	bool isNumberInTable = false;
	for (int i = 0; i < size; i++) {
		if (table[i] == value) {
			isNumberInTable = true;
		}
	}
	return isNumberInTable;
}
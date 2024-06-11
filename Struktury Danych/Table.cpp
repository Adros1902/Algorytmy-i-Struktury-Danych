#include "Table.h"
#include <iostream>

Table::Table()
{
	table = NULL;
}

Table::~Table()
{
	if (table != NULL) {
		delete table;
	}
}

void Table::addElementToTableFirst(int number)
{
	if (size == 0) {
		table = new int[1];
		table[0] = number;
		size++;
	}
	else {
		int* newTableAddFirst = new int[size+1];
		newTableAddFirst[0] = number;
		for (int i = 0; i < size; i++) {
			newTableAddFirst[i + 1] = table[i];
		}
		delete table;
		table = newTableAddFirst;
		size++;
	}
}

void Table::addElementToTableLast(int number)
{
	int* newTableAddLast = new int[size + 1];

	for (int i = 0; i < size; i++) {
		newTableAddLast[i] = table[i];
	}
	newTableAddLast[size] = number;
	delete table;
	table = newTableAddLast;
	size++;
}

void Table::addElementToTable(int index, int number)
{
	if (index == 0){
		addElementToTableFirst(number);
	}
	else if (index == size){
		addElementToTableLast(number);
	}
	else {

		int* newTableAdd = new int[size + 1];

		for (int i = 0; i < index ; i++) {
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
	printAllElements();
}

void Table::deleteElementFromTableFirst()
{
	int* newTableDeleteFirst = new int[size - 1];
	for (int i = 1; i < size; i++) {
		newTableDeleteFirst[i - 1] = table[i];
	}
	delete table;
	table = newTableDeleteFirst;
	size--;
}

void Table::deleteElementFromTableLast()
{
	int* newTableDeleteLast = new int[size - 1];
	for (int i = 0; i < size - 1; i++) {
		newTableDeleteLast[i] = table[i];
	}
	delete table;
	table = newTableDeleteLast;
	size--;
}

void Table::deleteElementFromTable(int index)
{
	if (index == 0) {
		deleteElementFromTableFirst();
	} 
	else if (index == size - 1){
		deleteElementFromTableLast();
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

void Table::printAllElements()
{
	for (int i = 0; i < size; i++) {
		std::cout << table[i] << " ";
	}
}

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

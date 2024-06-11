#pragma once
class Table
{
public:
	Table();

	~Table();

	int size = 0;
// wskaznik na poczatek tablicy
	int* table;

	void addElementToTableFirst(int number);

	void addElementToTableLast(int number);

	void addElementToTable(int index, int number);

	void deleteElementFromTableFirst();

	void deleteElementFromTableLast();

	void deleteElementFromTable(int index);

	void printAllElements();

	bool findingNumber(int value);
};


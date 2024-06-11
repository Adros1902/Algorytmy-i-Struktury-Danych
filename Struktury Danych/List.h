#pragma once
#include "ElementOfList.h"
#include <string>

class List
{
public:
// konstruktor listy
	List();
// destruktor listy
	~List();
// deklaracja pierwszego elementy listy - glowy
	ElementOfList* head;
// deklaracja ostatniego elementu listy - ogona
	ElementOfList* tail;
// zmienna - dlugosc listy
	int size = 0;
// metoda tworzaca liste z pliku
	void createListFromFile(std::string fileName);
// metoda obslugujaca dodawanie elementow do listy
	void addElementToList(int index, int value);
// metoda usuwaj¹ca elementy z listy
	void deleteElementOfList(int value);
// metoda wyswietlajaca elementy
	void printAllElements();
// metoda usuwajaca wszystkie elementy z listy, potrzebne do wczytywania z pliku
	void deleteAllElementsOfList();
// metoda wyszukujaca element i mowiaca czy jest on w tablicy
	bool findElement(int value);

	void test();
};


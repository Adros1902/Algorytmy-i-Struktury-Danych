#pragma once
#include "EdgeForListElement.h"
#include "EdgeForList.h"
class ListOfAdjency
{
public:

	int listElementIterator;

	EdgeForListElement* elementToReturn;
	// konstruktor listy
	ListOfAdjency();
	// destruktor listy
	~ListOfAdjency();
	// deklaracja pierwszego elementy listy - glowy
	EdgeForListElement* head;
	// deklaracja ostatniego elementu listy - ogona
	EdgeForListElement* tail;
	// zmienna - dlugosc listy
	int size = 0;
	// metoda dodajaca element na miejsce glowy 
	void addElementToListHead(EdgeForList value);
	// metoda dodajaca element na miejsce ogona
	void addElementToListTail(EdgeForList value);
	// metoda obslugujaca dodawanie elementow do listy
	void addElementToList(int index, int value);
	// metoda usuwajaca element z glowy
	void deleteElementOfListHead();
	// metoda usuwajaca element z ogona
	void deleteElementOfListTail();
	// metoda usuwaj¹ca elementy z listy
	bool deleteElementOfList(EdgeForList value);
	// metoda usuwajaca wszystkie elementy z listy, potrzebne do wczytywania z pliku
	void deleteAllElementsOfList();
	// metoda wyszukujaca element i mowiaca czy jest on w tablicy
	bool findElement(EdgeForList value);

	EdgeForList returnListElements();
};


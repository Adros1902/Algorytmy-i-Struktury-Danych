#pragma once
#include "ElementOfList.h"
class MyList
{

public:
	// konstruktor listy
	MyList();
	// destruktor listy
	~MyList();
	// deklaracja pierwszego elementy listy - glowy
	ElementOfList* head;
	// deklaracja ostatniego elementu listy - ogona
	ElementOfList* tail;
	// zmienna - dlugosc listy
	int size = 0;

	int listElementIterator;

	ElementOfList* elementToReturn;
	// metoda dodajaca element na miejsce glowy 
	void addElementToListHead(int value);
	// metoda dodajaca element na miejsce ogona
	void addElementToListTail(int value);
	// metoda obslugujaca dodawanie elementow do listy
	void addElementToList(int index, int value);
	// metoda usuwajaca element z glowy
	void deleteElementOfListHead();
	// metoda usuwajaca element z ogona
	void deleteElementOfListTail();
	// metoda usuwaj¹ca elementy z listy
	//bool deleteElementOfList(Edge value);
	// metoda usuwajaca wszystkie elementy z listy, potrzebne do wczytywania z pliku
	void deleteAllElementsOfList();
	int returnListElements();
};


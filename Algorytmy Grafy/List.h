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

	int listElementIterator;

	ElementOfList* elementToReturn;
	// metoda dodajaca element na miejsce glowy 
	void addElementToListHead(Edge value);
	// metoda dodajaca element na miejsce ogona
	void addElementToListTail(Edge value);
	// metoda obslugujaca dodawanie elementow do listy
	void addElementToList(int index, Edge value);
	// metoda usuwajaca element z glowy
	void deleteElementOfListHead();
	// metoda usuwajaca element z ogona
	void deleteElementOfListTail();
	// metoda usuwaj¹ca elementy z listy
	//bool deleteElementOfList(Edge value);
	// metoda usuwajaca wszystkie elementy z listy, potrzebne do wczytywania z pliku
	void deleteAllElementsOfList();
	Edge returnListElements();
};


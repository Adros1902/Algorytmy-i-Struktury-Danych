#include "ListOfAdjency.h"
#include "EdgeForListElement.h"
#include <iostream>
#include <fstream>


//konstruktor
ListOfAdjency::ListOfAdjency()
{
	listElementIterator = 0;
	head = NULL;
	tail = NULL;
}

// destruktor
ListOfAdjency::~ListOfAdjency()
{
	deleteAllElementsOfList();
}

// wstawienie elementu w miejsce glowy
void ListOfAdjency::addElementToListHead(EdgeForList value)
{

	EdgeForListElement* newElement = new EdgeForListElement;
	newElement->elementValue = value;
	if (head == NULL) {
		head = newElement;
		tail = head;
	}
	else {
		newElement->next = head;
		head->prev = newElement;
		head = newElement;
	}
	size++;
}

// wstawienie elementu w miejsce ogona
void ListOfAdjency::addElementToListTail(EdgeForList value)
{
	if (tail == NULL) {
		addElementToListHead(value);
	}
	else {
		EdgeForListElement* newElement = new EdgeForListElement;
		newElement->elementValue = value;
		newElement->prev = tail;
		tail->next = newElement;
		tail = newElement;
		size++;
	}
}

// usuwanie glowy z rozpatrzeniem czy jest to ostatni element listy czy nie
void ListOfAdjency::deleteElementOfListHead()
{
	EdgeForListElement* findingElement = head;
	if (size == 1) {
		delete findingElement;
		head = NULL;
		tail = NULL;
	}
	else {
		bool isValueInHead = false;
		head = findingElement->next;
		head->prev = NULL;
		delete findingElement;
	}
	size--;
}

void ListOfAdjency::deleteElementOfListTail()
{
	EdgeForListElement* findingElement = tail;
	tail = findingElement->prev;
	tail->next = NULL;
	delete findingElement;
	size--;
}

// funkcja usuwajaca wszystkie elementy z listy
void ListOfAdjency::deleteAllElementsOfList()
{
	if (size != 0) {
		EdgeForListElement* elementToDeleteAll = head;
		while (elementToDeleteAll != nullptr) {
			EdgeForListElement* nextElement = elementToDeleteAll->next;
			delete elementToDeleteAll;
			elementToDeleteAll = nextElement;
		}

		size = 0;
		head = nullptr;
		tail = nullptr;
	}

}

EdgeForList ListOfAdjency::returnListElements()
{
	listElementIterator++;
	if (listElementIterator == 1) {
		elementToReturn = head;
		return elementToReturn->elementValue;
	}
	elementToReturn = elementToReturn->next;
	return elementToReturn->elementValue;
}
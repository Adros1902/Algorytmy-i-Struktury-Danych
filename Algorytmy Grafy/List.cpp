#include "List.h"
#include "ElementOfList.h"
#include <iostream>
#include <fstream>


//konstruktor
List::List()
{
	head = NULL;
	tail = NULL;
	elementToReturn = NULL;
	listElementIterator = 0;
}

// destruktor
List::~List()
{
	deleteAllElementsOfList();
}

// wstawienie elementu w miejsce glowy
void List::addElementToListHead(Edge value)
{

	ElementOfList* newElement = new ElementOfList;
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
void List::addElementToListTail(Edge value)
{
	if (tail == NULL) {
		addElementToListHead(value);
	}
	else {
		ElementOfList* newElement = new ElementOfList;
		newElement->elementValue = value;
		newElement->prev = tail;
		tail->next = newElement;
		tail = newElement;
		size++;
	}
}

void List::addElementToList(int index, Edge value)
{
	// wstawienie elementu na pierwsze miejsce
	if (index == 0) {
		addElementToListHead(value);
	}
	// wstawienie elementu na koniec
	else if (index == size) {
		addElementToListTail(value);
	}
	// wstawienie w wybrane miejsce
	else {
		ElementOfList* pickedPlaceElement = head;
		// szukanie odpowiedniego miejsca na liscie
		for (int i = 0; i < index - 1; i++) {
			pickedPlaceElement = pickedPlaceElement->next;
		}
		// operacje wstawienia elementu na odpowiednie miejsce
		ElementOfList* newElement = new ElementOfList;
		newElement->elementValue = value;

		newElement->prev = pickedPlaceElement->prev;
		newElement->next = pickedPlaceElement;
		pickedPlaceElement->prev->next = newElement;
		pickedPlaceElement->prev = newElement;
		size++;
	}
}

// usuwanie glowy z rozpatrzeniem czy jest to ostatni element listy czy nie
void List::deleteElementOfListHead()
{
	ElementOfList* findingElement = head;
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

void List::deleteElementOfListTail()
{
	ElementOfList* findingElement = tail;
	tail = findingElement->prev;
	tail->next = NULL;
	delete findingElement;
	size--;
}

// funkcja usuwajaca wszystkie elementy z listy
void List::deleteAllElementsOfList()
{
	while (head != NULL) {
		ElementOfList* elementToDelete = head;
		head = head->next;
		delete elementToDelete;
	}
	delete tail;
	tail = NULL;
	size = 0;

}

Edge List::returnListElements() {
	listElementIterator++;
	if (listElementIterator == 1) {
		elementToReturn = head;
		return elementToReturn->elementValue;
	}
	elementToReturn = elementToReturn->next;
	return elementToReturn->elementValue;
}



#include "MyList.h"
#include "ElementOfList.h"
#include <iostream>
#include <fstream>


//konstruktor
MyList::MyList()
{
	head = nullptr;
	tail = nullptr;
	elementToReturn = nullptr;
	listElementIterator = 0;
	size = 0;
}

// destruktor
MyList::~MyList()
{
	deleteAllElementsOfList();
}

// wstawienie elementu w miejsce glowy
void MyList::addElementToListHead(int value)
{

	ElementOfList* newElement = new ElementOfList;
	newElement->elementValue = value;
	if (head == nullptr) {
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
void MyList::addElementToListTail(int value)
{
	if (tail == nullptr) {
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

void MyList::addElementToList(int index, int value)
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
void MyList::deleteElementOfListHead()
{
	ElementOfList* findingElement = head;
	if (size == 1) {
		delete findingElement;
		head = nullptr;
		tail = nullptr;
	}
	else {
		head = findingElement->next;
		head->prev = nullptr;
		delete findingElement;
	}
	size--;
}

void MyList::deleteElementOfListTail()
{
	ElementOfList* findingElement = tail;
	tail = findingElement->prev;
	tail->next = nullptr;
	delete findingElement;
	size--;
}

// funkcja usuwajaca wszystkie elementy z listy
void MyList::deleteAllElementsOfList()
{
	while (head != nullptr) {
		ElementOfList* elementToDelete = head;
		head = head->next;
		delete elementToDelete;
	}
	//delete tail;
	tail = nullptr;
	size = 0;
	listElementIterator = 0;
}

int MyList::returnListElements() {
	listElementIterator++;
	if (listElementIterator == 1) {
		elementToReturn = head;
		return elementToReturn->elementValue;
	}
	elementToReturn = elementToReturn->next;
	if (elementToReturn->next == nullptr) {
		listElementIterator = 0;
	}
	return elementToReturn->elementValue;
}




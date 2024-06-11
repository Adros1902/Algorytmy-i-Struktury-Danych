#include "List.h"
#include "ElementOfList.h"
#include <iostream>

//dodatek
#include <conio.h>
#include <fstream>
#include <string>
#include <sstream>

List::List()
{
	head = NULL;
	tail = NULL;
}

List::~List()
{
	deleteAllElementsOfList();
}

void List::createListFromFile(std::string fileName)
{
	if (size != 0) {
		deleteAllElementsOfList();
	}

	std::ifstream inputFile(fileName);

	//inputFile.open(fileName, std::ios::in);
	ElementOfList* inputFileElement;
	if (inputFile.is_open()) {
		std::string inputLine;

		getline(inputFile, inputLine);
		int inputNumber = stoi(inputLine);
		int readSize = inputNumber;
		int tempIndex = 0;

		for (int i = 0; i < readSize; i++) {
			getline(inputFile, inputLine);
			inputNumber = stoi(inputLine);
			addElementToList(tempIndex, inputNumber);
			tempIndex++;
		}
		inputFile.close();
	}
}

void List::addElementToList(int index, int value)
{
// Tworzenie elementu i przypisanie mu wartoœæi
	ElementOfList* newElement = new ElementOfList;
	newElement->elementValue = value;
// wstawienie pierwszego elementu tablicy
	if (head == NULL) {
		head = newElement;
		tail = newElement;
		size++;
	}
// wstawienie elementu na pierwsze miejsce
	else if (index == 0) {
		newElement->next = head;
		head->prev = newElement;
		head = newElement;
		size++;
	}
// wstawienie elementu na koniec
	else if (index == size) {
		newElement->prev = tail;
		tail->next = newElement;
		tail = newElement;
		size++;
	}
// wstawienie w wybrane miejsce
	else {
		int findingIndexValue = 0;
		ElementOfList* pickedPlaceElement = head;
// szukanie odpowiedniego miejsca na liscie
		while (true) {
			pickedPlaceElement = pickedPlaceElement->next;
			findingIndexValue++;

			if (findingIndexValue == index) {
				break;
			}
		}
// operacje wstawienia elementu na odpowiednie miejsce
		newElement->prev = pickedPlaceElement->prev;
		newElement->next = pickedPlaceElement;
		pickedPlaceElement->prev->next = newElement;
		pickedPlaceElement->prev = newElement;
		size++;
	}
// print wszystkich rekordow - tymczasowy
	printAllElements();
}

void List::deleteElementOfList(int value)
{
	int findingIndex = 0;
	ElementOfList* findingElement = head;
// wyszukiwanie wartosci do usuniecia
	while (true) {
		if (findingElement->elementValue == value) {
			break;
		}
		else{
			findingIndex++;
			findingElement = findingElement->next;
		}
	}
// usuwanie glowy
	if (findingIndex == 0 && size == 1) {
		delete findingElement;
		head = NULL;
		tail = NULL;
		size--;
	} else if (findingIndex == 0) {
		head = findingElement->next;
		head->prev = NULL;
		delete findingElement;
		size--;
	}
// usuwanie ogona
	else if (findingIndex == size - 1) {
		tail = findingElement->prev;
		tail->next = NULL;
		delete findingElement;
		size--;
	}
// usuwanie elementu ze srodka
	else {
		findingElement->prev->next = findingElement->next;
		findingElement->next->prev = findingElement->prev;
		delete findingElement;
		size--;
	}
	printAllElements();
}

void List::printAllElements()
{
	ElementOfList* toPrintElement = head;
	for (int i = 0; i < size; i++) {
		std::cout << toPrintElement->elementValue << " ";
		toPrintElement = toPrintElement->next;
	}
	_getch();
}
// funkcja usuwajaca wszystkie elementy z listy
void List::deleteAllElementsOfList()
{
	ElementOfList* elementToDeleteAll = head;
	while (true) {
		if (elementToDeleteAll->next != NULL) {
			elementToDeleteAll = elementToDeleteAll->next;
			delete elementToDeleteAll->prev;
		}
		else
		{
			delete elementToDeleteAll;
			size = 0;
			head = NULL;
			tail = NULL;
			std::cout << "Lista zostala usunieta." << std::endl;
			break;
		}
	}
	
}
bool List::findElement(int value)
{
	bool isValueInList = false;
	ElementOfList* elementToFind = head;
	for (int i = 0; i < size; i++) {
		if (elementToFind->elementValue == value) {
			isValueInList = true;
			break;
		}
		else {
			elementToFind = elementToFind->next;
		}
	}
	return isValueInList;
}
// test dodatkowy, niepotrzebny w oficjalnej wersji
void List::test()
{
	List::~List();
}
//
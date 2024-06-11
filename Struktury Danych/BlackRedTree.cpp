#include "BlackRedTree.h"
#include <iostream>
#include <fstream>

BlackRedTree::BlackRedTree()
{
	cr = cl = cp = "  ";					// potrzebne do print tree
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	sentinel = new BlackRedElement;
	root = new BlackRedElement;
	sentinel->value = NULL;
	sentinel->leftSon = sentinel;
	sentinel->rightSon = sentinel;
	sentinel->parent = sentinel;
	sentinel->color = Color::black;
	root = sentinel;
	size = 0;
}

BlackRedTree::~BlackRedTree()
{
	deleteWholeTree(root);
}

void BlackRedTree::generateRandomRBTree(int quantity) {
	if (root != sentinel) {
		deleteWholeTree(root);
		root = sentinel;
	}

	srand(time(NULL));
	int randomValue;
	for (int i = 0; i < quantity; i++) {
		randomValue = rand() * rand();
		insertElementToBRTree(randomValue);
	}
}

void BlackRedTree::deleteWholeTree(BlackRedElement* element) 
{
	if (element != sentinel) {
		deleteWholeTree(element->leftSon);
		deleteWholeTree(element->rightSon);
		delete element;
	}
}


void BlackRedTree::insertElementToBRTree(int value)
{
	BlackRedElement* newElement = new BlackRedElement;
	
	newElement->rightSon = sentinel;
	newElement->leftSon = sentinel;
	newElement->parent = root;
	newElement->value = value;
	

	if (root == sentinel) {
		root = newElement;
		root->color = Color::black;
	}
	else {
		while (true)
		{
			if (value >= newElement->parent->value) {				// sprawdz czy wartosc jest wieksza niz wartosc rodzica
				if (newElement->parent->rightSon == sentinel) {
					newElement->parent->rightSon = newElement;		// elementy wstawiany na prawy lisc
					break;
				}
				newElement->parent = newElement->parent->rightSon;
			} 
			else 
			{
				if (newElement->parent->leftSon == sentinel) {
					newElement->parent->leftSon = newElement;		// element wstawiany na lewy lisc
					break;
				}
				newElement->parent = newElement->parent->leftSon;
			}
		}

		newElement->color = Color::red;
		BlackRedElement* uncle;										

		while (newElement != root && newElement->parent->color == Color::red) {			//zaburzona wlasciwosc drzewa - 2 czerwone pod rzad
			if (newElement->parent == newElement->parent->parent->rightSon) {			//przypadek kiedy rodzic elementu jest prawym synem swojego rodzica
				uncle = newElement->parent->parent->leftSon;

				if (uncle->color == Color::red) {										//przypadek kiedy wujek jest czerwony
					newElement->parent->color = Color::black;
					newElement->parent->parent->color = Color::red;
					uncle->color = Color::black;
					newElement = newElement->parent->parent;
					continue;
				}

				if (newElement == newElement->parent->leftSon) {							//przypadek kiedy wujek jest czarny, a element jest lewym synem ojca - trzeba zrotowac w prawo dookola ojca
					newElement = newElement->parent;
					rightRotate(newElement);
				}

				newElement->parent->parent->color = Color::red;							//wujek jest czarny ale element jest prawym synem swego ojca - rotacja ojca dookola dziadka w lewo
				newElement->parent->color = Color::black;
				leftRotate(newElement->parent->parent);
				break;

			}
			else {																		//rodzic jest lewym synem swojego rodzica - reszta przypadkow jest symetryczna
				uncle = newElement->parent->parent->rightSon;
				if (uncle->color == Color::red) {										
					newElement->parent->parent->color = Color::red;
					newElement->parent->color = Color::black;
					uncle->color = Color::black;
					newElement = newElement->parent->parent;
					continue;
				}

				if (newElement == newElement->parent->rightSon) {						
					newElement = newElement->parent;
					leftRotate(newElement);
				}

				newElement->parent->parent->color = Color::red;							
				newElement->parent->color = Color::black;
				rightRotate(newElement->parent->parent);
				break;
			}
		}
		root->color = Color::black;
	}
}

void BlackRedTree::leftRotate(BlackRedElement* elementToRotate) // x-elementToRotate, y - tempRightSon
{
	BlackRedElement* tempRightSon = elementToRotate->rightSon;
	

	if (tempRightSon != sentinel) {
		elementToRotate->rightSon = tempRightSon->leftSon;

		if (elementToRotate->rightSon != sentinel) {
			elementToRotate->rightSon->parent = elementToRotate;
		}
		tempRightSon->parent = elementToRotate->parent;

		if (elementToRotate->parent == sentinel) {					//jesli rodzic elementu do rotacji jest pusty, to prawy syn jest nowym korzeniem
			root = tempRightSon;
		}
		else if (elementToRotate == elementToRotate->parent->leftSon) {		//jesli element do rotacji jest lewym synem swojego rodzica, to nowy lewy syn tego rodzica toprawy syn elementu do rotacji
			elementToRotate->parent->leftSon = tempRightSon;
		}
		else {
			elementToRotate->parent->rightSon = tempRightSon;			//jesli oba nie to jest prawym synem
		}

		tempRightSon->leftSon = elementToRotate;						//element do rotacji staje sie lewym synem swojego prawego syna
		elementToRotate->parent = tempRightSon;							//ojciec elementu do rotacji to syn swojego uprzednio prawego syna
	}
}

void BlackRedTree::rightRotate(BlackRedElement* elementToRotate)
{
	BlackRedElement* tempLeftSon = elementToRotate->leftSon;
	

	if (tempLeftSon != sentinel) {
		elementToRotate->leftSon = tempLeftSon->rightSon;

		if (elementToRotate->leftSon != sentinel) {
			elementToRotate->leftSon->parent = elementToRotate;
		}
		tempLeftSon->parent = elementToRotate->parent;

		if (elementToRotate->parent == sentinel)
		{
			root = tempLeftSon;
		}
		else if (elementToRotate == elementToRotate->parent->rightSon) {
			elementToRotate->parent->rightSon = tempLeftSon;
		}
		else {
			elementToRotate->parent->leftSon = tempLeftSon;
		}

		tempLeftSon->rightSon = elementToRotate;
		elementToRotate->parent = tempLeftSon;
	}
}

bool BlackRedTree::createBRTreeFromFile(std::string fileName)
{
	if (root != sentinel) {
		deleteWholeTree(root);
		root = sentinel;
	}

	std::ifstream inputFile(fileName);
	if (inputFile.good()) {
		if (inputFile.is_open()) {
			int fileSize;
			inputFile >> fileSize;
			for (int i = 0; i < fileSize; i++) {
				int tempValue;
				inputFile >> tempValue;
				insertElementToBRTree(tempValue);
			}
			return true;
		}
	}
		else return false;
}


bool BlackRedTree::deleteElementFromBRTree(int value)
{	// do usuniecia label   X               Y                   Z                  W
	BlackRedElement* elementToDelete, *elementReplacer, *replacerSonReplace, *otherReplacerSon;	// element replacer - element ktorym zastepujemy usuwany element
	elementToDelete = findValueInRBTree(value);													// replacerChildReplace - element zastepujacy replacer, otherChild - drugi syn replacer

	if (elementToDelete == NULL) {						// nie znaleziono takiej liczby
		return false;
	}

	if (elementToDelete->rightSon == sentinel || elementToDelete->leftSon == sentinel) {
		elementReplacer = elementToDelete;
	}
	else {
		elementReplacer = getSuccessor(elementToDelete);
	}

	if (elementReplacer->leftSon == sentinel) {
		replacerSonReplace = elementReplacer->rightSon;
	}
	else {
		replacerSonReplace = elementReplacer->leftSon;
	}

	replacerSonReplace->parent = elementReplacer->parent;

	if (elementReplacer->parent == sentinel) {
		root = replacerSonReplace;
	}
	else if (elementReplacer == elementReplacer->parent->leftSon) {
		elementReplacer->parent->leftSon = replacerSonReplace;
	}
	else {
		elementReplacer->parent->rightSon = replacerSonReplace;
	}

	if (elementReplacer != elementToDelete) {
		elementToDelete->value = elementReplacer->value;
	}

	// naprawa drzewa

	if (elementReplacer->color == Color::black) {
		while (replacerSonReplace != root && replacerSonReplace->color == Color::black)
		{
			if (replacerSonReplace == replacerSonReplace->parent->leftSon) {
				otherReplacerSon = replacerSonReplace->parent->rightSon;

				if (otherReplacerSon->color == Color::red) { // przypadek 1 NAPISAC OPIS TEJ INSTRUKCJI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

					replacerSonReplace->parent->color = Color::red;
					otherReplacerSon->color = Color::black;
					leftRotate(replacerSonReplace->parent);
					otherReplacerSon = replacerSonReplace->parent->rightSon;
				}

				if (otherReplacerSon->rightSon->color == Color::black && otherReplacerSon->leftSon->color == Color::black) { // przypadek 2
					replacerSonReplace = replacerSonReplace->parent;
					otherReplacerSon->color = Color::red;
					continue;												// continue, bo dodatkowy czarny kolor "przesuwa" sie do gory i trzeba wykonac kolejne operacje
				}

				if (otherReplacerSon->rightSon->color == Color::black) { // przypadek 3
					otherReplacerSon->color = Color::red;
					otherReplacerSon->leftSon->color = Color::black;
					rightRotate(otherReplacerSon);
					otherReplacerSon = replacerSonReplace->parent->rightSon;
				}

				otherReplacerSon->color = replacerSonReplace->parent->color;
				replacerSonReplace->parent->color = Color::black;
				otherReplacerSon->rightSon->color = Color::black;
				leftRotate(replacerSonReplace->parent);
				//break;
				replacerSonReplace = root;										// zakonczenie petli PRZEMYSL CZY NIE DA SIE ZROBIC INACZEJ
			}
			else {	// symetryczne przypadki
				otherReplacerSon = replacerSonReplace->parent->leftSon;

				if (otherReplacerSon->color == Color::red) {
					otherReplacerSon->color = Color::black;					//przypadek 1
					replacerSonReplace->parent->color = Color::red;
					rightRotate(replacerSonReplace->parent);					
					otherReplacerSon = replacerSonReplace->parent->leftSon;
				}

				if (otherReplacerSon->leftSon->color == Color::black && otherReplacerSon->rightSon->color == Color::black) {		
					replacerSonReplace = replacerSonReplace->parent;
					otherReplacerSon->color = Color::red;
					continue;
				}

				if (otherReplacerSon->leftSon->color == Color::black) {
					otherReplacerSon->color = Color::red;
					otherReplacerSon->rightSon->color = Color::black;
					leftRotate(otherReplacerSon);
					otherReplacerSon = replacerSonReplace->parent->leftSon;
				}

				otherReplacerSon->color = replacerSonReplace->parent->color;
				otherReplacerSon->leftSon->color = Color::black;
				replacerSonReplace->parent->color = Color::black;
				rightRotate(replacerSonReplace->parent);
				replacerSonReplace = root;
			}
		}
		replacerSonReplace->color = Color::black;
	}
	delete elementReplacer;
	return true;
}

BlackRedElement* BlackRedTree::getSuccessor(BlackRedElement* element)
{

	if (element->rightSon != sentinel) {							//jesli element ma prawego syna, szukamy jego nastepnika w prawym poddrzewie
		return getMinimum(element);
	}
	BlackRedElement* tempParent = element->parent;

	while (tempParent != sentinel && element == tempParent->rightSon) {	// jesli nie ma prawego poddrzewa, sprawdzamy czy ma nastepnik, ktory jest najnizszym przodkiem wezla 
		element = tempParent;											// "element", ktorego lewy syn jest takze przodkiem "element"
		tempParent = tempParent->parent;
	}

	return element;
}

void BlackRedTree::printBlackRedTreeHelper(std::string sp, std::string sn, BlackRedElement* element)		// source: https://eduinf.waw.pl/inf/alg/001_search/0121.php
{

	std::string t;

	if (element != sentinel)
	{
		t = sp;
		if (sn == cr) t[t.length() - 2] = ' ';
		printBlackRedTreeHelper(t + cp, cr, element->rightSon);

		std::string tempColor;
		t = t.substr(0, sp.length() - 2);
		if (element->color == Color::black) {
			tempColor = "B";
		}
		else {
			tempColor = "R";
		}
		std::cout << t << sn << tempColor << ":" << element->value << std::endl;

		t = sp;
		if (sn == cl) t[t.length() - 2] = ' ';
		printBlackRedTreeHelper(t + cp, cl, element->leftSon);
	}
}

void BlackRedTree::printBlackRedTree() {

	printBlackRedTreeHelper("", "", root);
}

BlackRedElement* BlackRedTree::findValueInRBTree(int value)
{
	BlackRedElement* elementToFind;

	elementToFind = root;

	while (elementToFind != sentinel && elementToFind->value != value) {
		if (elementToFind->value <= value) {
			elementToFind = elementToFind->rightSon;
		}
		else {
			elementToFind = elementToFind->leftSon;
		}
	}
	if (elementToFind == sentinel) {
		return NULL;
	}
	return elementToFind;
}

BlackRedElement* BlackRedTree::getMinimum(BlackRedElement* element)
{
	element = element->rightSon;
	while (element->leftSon != sentinel) {
		element = element->leftSon;
	}
	return element;
}


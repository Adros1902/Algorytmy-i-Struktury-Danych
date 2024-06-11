#pragma once
#include "BlackRedElement.h"
#include <iostream>
class BlackRedTree
{
private:
// wartosci kolorow - czarny = 0, czerwony = 1
	enum Color{black, red};
	
public:
	int size;

	std::string cr, cl, cp;

	BlackRedElement* root;

	BlackRedElement* sentinel;

	BlackRedTree();

	~BlackRedTree();

	bool createBRTreeFromFile(std::string fileName);

	void insertElementToBRTree(int value);

	void generateRandomRBTree(int quantity);

	bool deleteElementFromBRTree(int value);

	void deleteWholeTree(BlackRedElement* element);

	BlackRedElement* findValueInRBTree(int value);

	void leftRotate(BlackRedElement* elementToRotate);

	void rightRotate(BlackRedElement* elementToRotate);

	void printBlackRedTreeHelper(std::string sp, std::string sn, BlackRedElement* element);

	void printBlackRedTree();

	BlackRedElement* getSuccessor(BlackRedElement* element);

	BlackRedElement* getMinimum(BlackRedElement* element);

};


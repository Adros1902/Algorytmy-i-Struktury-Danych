#pragma once
#include "List.h"
#include <iostream>
#include "Table.h"
#include "Heap.h"
#include "BlackRedTree.h"

class UserMenu
{
public:
	List list;

	Table table;

	Heap heap;

	BlackRedTree blackRedTree;
// metoda printujaca poczatkowy ekran uzytkownika
	void mainMenu();
// metoda printujaca ekran uzytkownika przy korzystaniu z listy
	void listMenu();

	void tableMenu();

	void heapMenu();

	void blackRedTreeMenu();

	void tests();
};


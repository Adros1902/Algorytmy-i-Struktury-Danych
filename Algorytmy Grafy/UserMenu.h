#pragma once
#include "Heap.h"
#include "Kruskal.h"
#include "Prim.h"

class UserMenu
{
public:
	Kruskal kruskal;

	Prim prim;

	void mainMenu();

	void mstMenu();
};


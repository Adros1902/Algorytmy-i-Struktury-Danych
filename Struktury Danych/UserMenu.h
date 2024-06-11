#pragma once
#include "List.h"
#include <iostream>
#include "Table.h"

class UserMenu
{
public:
	List list;

	Table table;
// metoda printujaca poczatkowy ekran uzytkownika
	void mainMenu();
// metoda printujaca ekran uzytkownika przy korzystaniu z listy
	void listMenu();

	void tableMenu();
};


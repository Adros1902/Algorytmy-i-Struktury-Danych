#pragma once
#include "EdgeForList.h"
class EdgeForListElement
	//krawedz tylko z waga i wierzcholkiem koncowym - uzywana do implementacji listy sasiedztwa
{
public:
		EdgeForList elementValue;
		EdgeForListElement* prev;
		EdgeForListElement* next;

		EdgeForListElement();
};


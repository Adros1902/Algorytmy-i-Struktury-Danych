#pragma once
#include "Edge.h"
class ElementOfList
{
public:
	Edge elementValue;
	ElementOfList* prev;
	ElementOfList* next;

	ElementOfList();
};

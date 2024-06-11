#include "DisjointSet.h"

DisjointSet::DisjointSet(int size)
{
	rank = new int[size];
	parent = new int[size];
	this->size = size;
	makeSets();
}

DisjointSet::~DisjointSet()
{
	delete rank;
	delete parent;
	size = 0;
}

void DisjointSet::makeSets()
{
	for (int i = 0; i < size; i++) {
		parent[i] = i;
		rank[i] = 0;
	}
}

void DisjointSet::unionSets(int firstSet, int secondSet)
{
	firstSet = findSet(firstSet);
	secondSet = findSet(secondSet);
	if (rank[firstSet] > rank[secondSet]) {
		parent[secondSet] = firstSet;
	}
	else {
		parent[firstSet] = secondSet;
		if (rank[firstSet] == rank[secondSet]) {
			rank[secondSet]++;
		}
	}
	
}

int DisjointSet::findSet(int setToFind)
{
	if (parent[setToFind] != setToFind) {
		parent[setToFind] = findSet(parent[setToFind]);
	}

	return parent[setToFind];
}

#pragma once
#
class DisjointSet
{
public:
	int* rank, * parent, size;

	DisjointSet(int size);

	~DisjointSet();

	void makeSets();

	void unionSets(int firstSet, int secondSet);

	int findSet(int setToFind);
};


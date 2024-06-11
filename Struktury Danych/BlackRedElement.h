#pragma once
class BlackRedElement
{
public:
	int value;
	BlackRedElement* parent;
	BlackRedElement* leftSon;
	BlackRedElement* rightSon;
	bool color;

	BlackRedElement();
};


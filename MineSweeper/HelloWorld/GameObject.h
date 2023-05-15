#pragma once
#include <iostream>
#include "Utils.h"
#include "Screen.h"

using namespace std;

class GameObject
{
	Position pos;
	char* shape;
	Dimension dim;
	Screen& screen;

public:
	GameObject(char shape, int x, int y, Screen& screen)
		: pos(x, y), shape(nullptr), dim(1, 1), screen(screen)
	{
		this->shape = (char*)new char[dim.size() + 1];
		this->shape[0] = shape;
		this->shape[dim.size()] = '\0';
	}

	virtual ~GameObject() {
		delete[] shape;
	}

	Position getPos() const { return pos; }

	void setPos(const Position& pos) 
	{ 
		if (screen.checkValidPos(pos) == false) 
			return;
		this->pos.x = pos.x; this->pos.y = pos.y; 
	}

	char getShape() const { return shape[0]; }


	virtual void update() {}

protected:
	void ChangeShape(char shape)
	{
		delete[] this->shape;
		this->shape = (char*)new char[dim.size() + 1];
		this->shape[0] = shape;
		this->shape[dim.size()] = '\0';
	}
};


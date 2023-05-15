#pragma once
#include "GameObject.h"

enum Status { Empty, Number, Mine };

class Slot :
    public GameObject
{
	int num;
	int status;
	bool isOpen;
	bool flag;

public:
	Slot(int x, int y, Screen& screen) : GameObject('0', x, y, screen), 
		num(0), status(Status::Empty), isOpen(false), flag(false) {}

	void SetStatus(Status status) { this->status = status; }

	void Setflag()
	{
		flag = !flag;

		if (flag)
			ChangeShape('X');
		else
			ChangeShape('0');
	}

	void AddNum(){num+=1;}

	int GetStatus() { return status; }

	int GetNum() { return num; }

	bool IsOpen() { return isOpen; }

	bool IsFlag() { return flag; }

	void Press()
	{
		isOpen = true;
		char shape;

		switch (status)
		{
		case Status::Empty: // ºóÄ­
			shape = ' ';
			break;
		case Status::Number: // ¼ıÀÚ
			shape = '0' + num;
			break;
		case Status::Mine: // Áö·Ú
			shape = '*';
			break;
		default:
			shape = ' ';
			break;
		}

		ChangeShape(shape);
	}

	void ShowMine()
	{
		if(status == Status::Mine)
			ChangeShape('*');
	}
};


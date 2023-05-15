#pragma once
#include <conio.h>
#include "GameObject.h"

class Player :
    public GameObject
{
	bool isPressSlot;
	bool isPressFlag;

	void processInput()
	{
		int key;
		int minor;

		isPressSlot = false;
		isPressFlag = false;

		if (!_kbhit()) return;

		Borland::GotoXY(0, 21);
		key = _getch();
				
		Borland::GotoXY(1, 23);
		printf("player key is %c   %x %d\n", key, key, key);

		Position pos = getPos();

		switch (key) {
		case 224:
			minor = _getch();
			printf("player minor key is %c   %x %d\n", minor, minor, minor);
			switch (minor) {
			case 'K':
				pos.x--;
				break;
			case 'M':
				pos.x++;
				break;
			case 'P':
				pos.y++;
				break;
			case 'H':
				pos.y--;
				break;
			}
			break;
		case 'w':
			pos.y--;
			break;
		case 'a':
			pos.x--;
			break;
		case 's':
			pos.y++;
			break;
		case 'd':
			pos.x++;
			break;

		case 'q':
			isPressSlot = true;
			break;
		case 'e':
			isPressFlag = true;
			break;
		}

		setPos(pos);
	}

public:
    Player(int x, int y, Screen& screen) : GameObject('>', x, y, screen),
		isPressSlot(false), isPressFlag(false) {}

	bool IsPressSlot() { return isPressSlot; }
	bool IsPressFlag() { return isPressFlag; }

	void update() override
	{
		processInput();
	}
};


#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include "GameObject.h"
#include "Utils.h"
#include "Screen.h"
#include "Player.h"
#include "Enemy.h"
#include "Slots.h"

#define X_SIZE 10
#define Y_SIZE 10

using namespace std;

int main()
{	
	srand(time(NULL));
	int mineNum = 10 + rand() % 11; //10~20

	Screen screen(20, 20);
	Slots slots(X_SIZE, Y_SIZE, mineNum, screen);
	Player player{ 2, 4, screen };

	Borland::GotoXY(0, 25);
	printf("Mine Num : %d\n", mineNum);
	printf("[q] key press slot\n");
	printf("[e] key press flag\n");

	while (1)
	{
		screen.clear();

		for (int i = 0; i < slots.GetSize(); i++)
			screen.draw(slots.GetSlot(i)->getPos(), slots.GetSlot(i)->getShape());
		screen.draw(player.getPos(), player.getShape());

		screen.render();

		if (slots.IsClickMine())
		{
			Sleep(2000);
			screen.clear();
			screen.render();
			printf("-----------------Game Over-----------------------");
			break;
		}

		if (slots.IsAllOpen())
		{
			Sleep(2000);
			screen.clear();
			screen.render();
			printf("-----------------Game Clear-----------------------");
			break;
		}

		player.update();

		if (player.IsPressFlag())
			slots.SetFlag(player.getPos());

		if (player.IsPressSlot())
			slots.CheckPressSlot(player.getPos());
	}

	return 0;
}
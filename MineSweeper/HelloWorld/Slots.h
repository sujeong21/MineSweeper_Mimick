#pragma once
#include <ctime>
#include "Slot.h"

class Slots
{
	Slot** slots;
	int xSize;
	int ySize;
	int mineNum;
	int openNum;
	bool clickMine;

	Slot* FindSlot(Position pos)
	{
		if (pos.x < 0 || pos.y < 0 || pos.x >= xSize || pos.y >= ySize) return NULL;

		for (int i = 0; i < GetSize(); i++)
		{
			if (slots[i]->getPos().x == pos.x &&
				slots[i]->getPos().y == pos.y)
				return slots[i];
		}
		return NULL;
	}

	void SetSlots() // status ¼³Á¤
	{
		srand(time(NULL));

		// Áö·Ú ¼³Á¤
		int setMineNum = 0;
		while (setMineNum != mineNum)
		{
			int index = rand() % GetSize();
			if (slots[index]->GetStatus() == Status::Mine)
				continue;
			
			setMineNum++;

			slots[index]->SetStatus(Status::Mine);
			Position curPos = slots[index]->getPos();

			if (FindSlot({ curPos.x - 1, curPos.y }) != NULL)
				FindSlot({ curPos.x - 1, curPos.y })->AddNum();
			if (FindSlot({ curPos.x - 1, curPos.y + 1 }) != NULL)
				FindSlot({ curPos.x - 1, curPos.y + 1 })->AddNum();
			if (FindSlot({ curPos.x - 1, curPos.y - 1 }) != NULL)
				FindSlot({ curPos.x - 1, curPos.y - 1 })->AddNum();

			if (FindSlot({ curPos.x, curPos.y + 1 }) != NULL)
				FindSlot({ curPos.x , curPos.y + 1 })->AddNum();
			if (FindSlot({ curPos.x, curPos.y - 1 }) != NULL)
				FindSlot({ curPos.x, curPos.y - 1 })->AddNum();

			if (FindSlot({ curPos.x + 1, curPos.y }) != NULL)
				FindSlot({ curPos.x + 1, curPos.y })->AddNum();
			if (FindSlot({ curPos.x + 1, curPos.y + 1 }) != NULL)
				FindSlot({ curPos.x + 1, curPos.y + 1 })->AddNum();
			if (FindSlot({ curPos.x + 1, curPos.y - 1 }) != NULL)
				FindSlot({ curPos.x + 1, curPos.y - 1 })->AddNum();
		}

		// ³Ñ¹ö ¼³Á¤
		for (int i = 0; i < GetSize(); i++)
		{
			if (slots[i]->GetStatus() == Status::Mine || slots[i]->GetNum() == 0) continue;
			slots[i]->SetStatus(Status::Number);
		}
	}

	void CheckEmptySlot(Position pos)
	{
		Slot* slot = FindSlot(pos);
		if (slot == NULL) return;
		if (slot->IsOpen()) return;

		slot->Press();
		openNum++;

		if ( slot->GetStatus() == Status::Empty)
		{
			CheckEmptySlot({ pos.x - 1, pos.y });
			CheckEmptySlot({ pos.x - 1, pos.y + 1 });
			CheckEmptySlot({ pos.x - 1, pos.y - 1 });

			CheckEmptySlot({ pos.x , pos.y + 1 });
			CheckEmptySlot({ pos.x, pos.y - 1 });

			CheckEmptySlot({ pos.x + 1, pos.y });
			CheckEmptySlot({ pos.x + 1, pos.y + 1 });
			CheckEmptySlot({ pos.x + 1, pos.y - 1 });
		}
	}

public:
	Slots(int xSize, int ySize, int mineNum, Screen& screen) : xSize(xSize), ySize(ySize), mineNum(mineNum), openNum(0), clickMine(false)
	{
		slots = new Slot*[xSize * ySize];
		for (int y = 0; y < ySize; y++)
			for (int x = 0; x < xSize; x++)
				slots[x + y * ySize] = new Slot(x, y, screen);
		 
		SetSlots();
	}
	
	~Slots()
	{
		delete[] slots;
	}

	int GetSize() { return (xSize * ySize); }

	bool IsAllOpen() { return GetSize() - openNum == mineNum; }

	bool IsClickMine() { return clickMine; }

	Slot* GetSlot(int index) { return slots[index]; }

	void SetFlag(Position pos)
	{
		Slot* slot = FindSlot(pos);

		if (slot == NULL) return;
		if (slot->IsOpen()) return;

		slot->Setflag();
	}

	void CheckPressSlot(Position pos)
	{
		Slot* slot = FindSlot(pos);
		
		if (slot == NULL) return;
		if (slot->IsOpen() || slot->IsFlag()) return;

		switch (slot->GetStatus())
		{
		case Status::Empty: // ºóÄ­
			CheckEmptySlot(pos);
			break;
		case Status::Mine: // Áö·Ú		
			clickMine = true;
			for (int i = 0; i < GetSize(); i++)
				slots[i]->ShowMine();
			break;
		case Status::Number:
			slot->Press();
			openNum++;
			break;
		default:
			break;
		}
	}
};


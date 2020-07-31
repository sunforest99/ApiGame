#include "My_Include.h"

cMonster::cMonster()
{
	isUse = DIE;
}

cMonster::~cMonster()
{

}

void cMonster::SetPosition()
{
	posX = rand() % 800;
	posY = (rand() % 50) * -1;
	life = 1;
	speed = 3;
	isUse = LIVE;

}

void cMonster::Update()
{
	static DWORD currentTime = GetTickCount();
	if (isUse == DIE)
	{
		if (GetTickCount() - currentTime > 800)
		{
			SetPosition();
			currentTime = GetTickCount();
		}
	}
	else
	{
		posY += speed;

		if (posY > 600)
		{
			isUse = DIE;
		}
	}
}

void cMonster::Render()
{
	if (isUse == LIVE)
	{
		g_Image.Draw(posX, posY, 202, 466, 32, 30, 32, 30, RGB(0, 67, 171));
	}
}
LIVEDIE cMonster::isUsed()
{
	return isUse;
}
POINT cMonster::GetPosition()
{
	POINT pt;
	pt.x = posX;
	pt.y = posY;
	return pt;
}

void cMonster::SetUsed()
{
	isUse = DIE;
}
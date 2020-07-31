#include "My_Include.h"

cBullet::cBullet()
{
	isUse = DIE;
}

cBullet::~cBullet()
{

}

bool cBullet::SetPosition(int x, int y)
{
	static DWORD shootTime = GetTickCount();

	if (isUse == DIE && GetTickCount() - shootTime > 500)
	{
		posX = x + 16;
		posY = y;
		speed = BUL_SPEED;
		isUse = LIVE;
		shootTime = GetTickCount();
		return true;
	}
	return false;
}

void cBullet::Update()
{
	if (isUse == LIVE && posY > 0)
	{
		posY -= speed;
	}
	
	if (posY <= 0)
	{
		isUse = DIE;
	}
}

void cBullet::Render()
{
	if (isUse == LIVE)
	{
		g_Image.Draw(posX, posY, 37, 169, 32, 32, 32, 32, RGB(0, 67, 171));
	}
}
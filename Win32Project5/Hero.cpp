#include "My_Include.h"

cHero::cHero()
{
	posX = 400;
	posY = 350;
	posW = 64;
	posH = 64;
}

cHero::~cHero()
{

}

void cHero::SetPosition(int x, int y)
{
	posX += x;
	posY += y;

	if (posX < 0)
	{
		posX = 0;
	}
	else if (posX + posW > 780)
	{
		posX = 800 - posW - 20;
	}

	if (posY < 0)
	{
		posY = 0;
	}
	else if (posY + posH > 550)
	{
		posY = 550 - posH;
	}
}

void cHero::Update()
{
	for (int i = 0; i < MEX_BULLET; i++)
	{
		bullet[i].Update();
	}
}

void cHero::Render()
{
	g_Image.Draw(posX, posY, 4, 400, posW, posH, posW, posH, RGB(0, 67, 171));
	for (int i = 0; i < MEX_BULLET; i++)
	{
		bullet[i].Render();
	}
}

void cHero::SetAttack()
{
	for (int i = 0; i < MEX_BULLET; i++)
	{
		if (bullet[i].SetPosition(posX, posY))
		{
			break;
		}
	}
}

POINT cHero::GetPosition()
{
	POINT pt;
	pt.x = posX;
	pt.y = posY;
	return pt;
}
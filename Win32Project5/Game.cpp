#include "My_Include.h"

cGame::cGame()
{
	m_world.Create();
}

cGame::~cGame()
{
	m_world.Destroy();
}

void cGame::Init()
{

}

void cGame::Update(float et)
{
	int x = 0, y = 0;
	if (g_keyCheck[KEY_UP])		y -= 5;
	if (g_keyCheck[KEY_DOWN])	y += 5;
	if (g_keyCheck[KEY_LEFT])	x -= 5;
	if (g_keyCheck[KEY_RIGHT])	x += 5;
	if (g_keyCheck[KEY_SPACE]) m_Hero.SetAttack();
	m_Hero.SetPosition(x, y);

	m_world.Update(et);

	m_Hero.Update();

	for (int i = 0; i < MEX_MONSTER; i++)
	{
		m_Monster[i].Update();
	}

	for (int i = 0; i < MEX_MONSTER; i++)
	{
		// Hero vs Monster	//무식

		if (m_Monster[i].isUsed() ==LIVE)
		{
			if (m_Monster[i].GetPosition().x - m_Hero.GetPosition().x < 50 && m_Hero.GetPosition().x - m_Monster[i].GetPosition().x < 20 && m_Monster[i].GetPosition().y - m_Hero.GetPosition().y < 50 && m_Hero.GetPosition().y - m_Monster[i].GetPosition().y < 20)
			{
				m_Monster[i].SetUsed();
			}
		 }

		// Bullet vs Monster
	}
}

void cGame::Render()
{
	m_world.Render();

	m_Hero.Render();
	for (int i = 0; i < MEX_MONSTER; i++)
	{
		m_Monster[i].Render();
	}
}

int cGame::Destroy()
{
	return MENU;
}

//bool Cheakcollision(POINT p1, POINT p2)	//무시
//{
//	int r1 = 30;
//	int r2 = 15;
//
//	double result = sqrt(pow(p1.x - p2.x, 2)+ pow(p1.y - p2.y, 2));
//
//	if (r1 + r2 >= result)
//	{
//		return true;
//	}
//	return false;
//}

LRESULT cGame::MsgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_UP:
			g_keyCheck[KEY_UP] = true;
			break;
		case VK_DOWN:
			g_keyCheck[KEY_DOWN] = true;
			break;
		case VK_LEFT:
			g_keyCheck[KEY_LEFT] = true;
			break;
		case VK_RIGHT:
			g_keyCheck[KEY_RIGHT] = true;
			break;
		case VK_SPACE:
			g_keyCheck[KEY_SPACE] = true;
		}
		return 0;
	case WM_KEYUP:
		switch (LOWORD(wParam))
		{
		case VK_UP:
			g_keyCheck[KEY_UP] = false;
			break;
		case VK_DOWN:
			g_keyCheck[KEY_DOWN] = false;
			break;
		case VK_LEFT:
			g_keyCheck[KEY_LEFT] = false;
			break;
		case VK_RIGHT:
			g_keyCheck[KEY_RIGHT] = false;
			break;

		case VK_SPACE:
			g_keyCheck[KEY_SPACE] = false;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
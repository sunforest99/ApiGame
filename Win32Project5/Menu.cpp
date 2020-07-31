#include "My_Include.h"

cMenu::cMenu()
{
	selectMenu = 0;
}
cMenu::~cMenu()
{

}

void cMenu::Init()
{

}

void cMenu::Update(float et)
{

}

void cMenu::Render()
{
	g_Image.Draw(100, 100, 581, 390, 94, 95, 105, 91);
	g_Image.Draw(85, 100 + (selectMenu * 18), 570, 390, 7, 12, 12, 14);
}

int cMenu::Destroy()
{
	if (selectMenu == 0)
	{
		return GAME;
	}
	else
	{
		return LOGO;
	}
}

LRESULT cMenu::MsgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_UP:
			selectMenu--;
			if (selectMenu < 0)
			{
				selectMenu = 4;
			}break;
		case VK_DOWN:
			selectMenu++;
			if (selectMenu > 4)
			{
				selectMenu = 0;
			}return 0;
			
		case VK_RETURN:
			if (selectMenu != 4)
			{
				g_State.SetInnerState(DESTROY);
			}
			else
			{
				selectMenu = 0;
			}return 0;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
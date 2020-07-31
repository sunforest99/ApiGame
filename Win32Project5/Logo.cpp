#include "My_Include.h"

cLogo::cLogo()
{

}
cLogo::~cLogo()
{

}

void cLogo::Init()
{
	g_Sound.playMusic("data/wav/sound1.wav");
}

void cLogo::Update(float et)
{

}

void cLogo::Render()
{
	g_Image.Draw(0, 0, 103, 577, 800, 600, 278, 140);
	g_Image.Draw(356, 470, 4, 620, 87, 18, 87, 18, RGB(0, 0, 0));
}

int cLogo::Destroy()
{
	g_Sound.stopMusic();
	return MENU;
}

LRESULT cLogo::MsgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		g_State.SetInnerState(DESTROY);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
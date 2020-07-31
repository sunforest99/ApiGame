#pragma once

class cState;

class cMenu : public cState
{
	int selectMenu;

public:
	cMenu();
	~cMenu();

	void Init();
	void Update(float et);
	void Render();
	int Destroy();
	LRESULT MsgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
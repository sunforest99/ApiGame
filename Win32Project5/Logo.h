#pragma once

class cState;

class cLogo : public cState
{
public:
	cLogo();
	~cLogo();

	void Init();
	void Update(float et);
	void Render();
	int Destroy();
	LRESULT MsgProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
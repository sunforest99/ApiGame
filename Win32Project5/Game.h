#pragma once

class cState;

class cGame : public cState
{
private:
	cHero	m_Hero;
	cMonster m_Monster[MEX_MONSTER];
	cGameWorld m_world;

public:
	cGame();
	~cGame();

	void Init();
	void Update(float et);
	void Render();
	int Destroy();
	LRESULT MsgProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);
	bool checkCollision(POINT p1, POINT p2);
};
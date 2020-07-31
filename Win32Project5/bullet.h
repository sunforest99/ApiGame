#pragma once

class cBullet
{
private:
	LIVEDIE isUse;
	int posX;
	int posY;
	int speed;

public:
	cBullet();
	~cBullet();

	bool SetPosition(int x, int y);
	void Update();
	void Render();
};
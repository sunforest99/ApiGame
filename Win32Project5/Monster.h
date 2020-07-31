#pragma once

class cMonster
{
private:
	LIVEDIE isUse;
	int posX;
	int posY;
	int speed;
	int life;
public:
	cMonster();
	~cMonster();

	void SetPosition();
	void Update();
	void Render();

	LIVEDIE isUsed();
	POINT GetPosition();

	void SetUsed();
};
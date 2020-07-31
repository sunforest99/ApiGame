#pragma once

class cBullet;

class cHero
{
private:
	int posX;
	int posY;
	int posW;
	int posH;
	cBullet bullet[MEX_BULLET];

public:
	cHero();
	~cHero();

	void SetPosition(int x, int y);
	void Update();
	void Render();
	void SetAttack();

	POINT GetPosition();
};
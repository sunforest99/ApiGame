#pragma once

class cGameWorld
{
public:
	float worldWidth;
	float worldHeight;

	float screenX;
	float screenY;
	float screenWidth;
	float screenHeight;

	int startIndex;
	cGdiImage* backImage;

public:
	cGameWorld();
	~cGameWorld();

	void Create();
	void Destroy();
	void Update(float et);
	void Render();

	void CalculateIndex();
	void LoadImages();
	void ClampScreen();
};
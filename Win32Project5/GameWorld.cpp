#include "My_Include.h"

cGameWorld::cGameWorld()
{
	worldWidth = 512 * 2;
	worldHeight = 512 * 6;
	screenX = 0;
	screenY = 0;
	screenWidth = g_Graphics.m_ScreenSizeX;
	screenHeight = g_Graphics.m_ScreenSizeY;
}

cGameWorld::~cGameWorld()
{

}

void cGameWorld::Create()
{
	backImage = new cGdiImage[12];
	LoadImages();
}

void cGameWorld::Destroy()
{
	delete[] backImage;
	backImage = NULL;
}

void cGameWorld::Update(float et)
{
	screenY -= 32 / et;
}
void cGameWorld::Render()
{
	CalculateIndex();
	ClampScreen();

	int offsetX = (int)screenX % 512;
	int offsetY = (int)screenY % 512;

	int idx0 = (startIndex + 0) % 12;
	int idx1 = (startIndex + 1) % 12;
	int idx2 = (startIndex + 2) % 12;
	int idx3 = (startIndex + 3) % 12;
	int idx4 = (startIndex + 4) % 12;
	int idx5 = (startIndex + 5) % 12;

	backImage[idx0].Draw(-offsetX, -offsetY);
	backImage[idx1].Draw(-offsetX + 512, -offsetY);
	backImage[idx2].Draw(-offsetX, -offsetY + 512);
	backImage[idx3].Draw(-offsetX + 512, -offsetY + 512);
	backImage[idx4].Draw(-offsetX, -offsetY + 512 * 2);
	backImage[idx5].Draw(-offsetX + 512, -offsetY + 512 * 2);

}


void cGameWorld::CalculateIndex()
{
	int w = (int)screenX / 512;
	int h= (int)screenY / 512;

	startIndex = 2 * h + w;
}

void cGameWorld::LoadImages()
{
	for (int i = 0; i < 12; i++)
	{
		backImage[i].setDC(g_Graphics.getGraphicsDC());
	}
	
	backImage[0].Load("data/10.bmp");
	backImage[1].Load("data/11.bmp");
	backImage[2].Load("data/08.bmp");
	backImage[3].Load("data/09.bmp");
	backImage[4].Load("data/06.bmp");
	backImage[5].Load("data/07.bmp");
	backImage[6].Load("data/04.bmp");
	backImage[7].Load("data/05.bmp");
	backImage[8].Load("data/02.bmp");
	backImage[9].Load("data/03.bmp");
	backImage[10].Load("data/00.bmp");
	backImage[11].Load("data/01.bmp");
}

void cGameWorld::ClampScreen()
{
	screenX = clamp(screenX, 0.0f, worldWidth - worldWidth);
	screenY = ClampAround(screenY, 0.0f, worldHeight);
}

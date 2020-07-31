#include "scene.h"

cScene::cScene()
{
	m_MaxFrame				= 0;
	m_FrameArr				= NULL;
	m_FrameTime				= NULL;
}

cScene::~cScene()
{
	destroyScene();
}

void	cScene::setMaxFrame(int maxFrame)
{
	if( maxFrame != 0 )
		destroyScene();

	m_MaxFrame				= maxFrame;
	m_FrameArr				= new cFrame[maxFrame];
	m_FrameTime				= new DWORD[maxFrame];
}

int		cScene::getMaxFrame()
{
	return m_MaxFrame;
}

void	cScene::setMaxElementOfFrame(int frameIdx, DWORD frameTime)
{
	m_FrameTime[frameIdx]	= frameTime;
}

//////////////////////////////////////////////////////////////////////////
//
// void addElementOfFrame() : 프레임의 요소를 추가한다.
//
// 인자값 : int		frameIdx		- 추가하려는 요소를 소유한 프레임번호
//			int		elementIdx		- 추가하려는 요소의 위치
//			int		imageIdx		- 이미지 번호
//			int		frameIntervalX	- 기준점으로부터 X축으로 이동하여 출력할 값
//			int		frameIntervalY	- 기준점으로부터 Y축으로 이동하여 출력할 값
//			int		imageIntervalX	- 이미지의 X축
//			int		imageIntervalY	- 이미지의 Y축
//			int		w				- 이미지의 넓이
//			int		h				- 이미지의 높이
//			int		layer			- 프레임의 레이어
//          
// 반환값 : 없음
//
void	cScene::addElementOfFrame(int frameIdx, int imageIdx,
								  int frameIntervalX, int frameIntervalY,
								  int imageIntervalX, int imageIntervalY,
								  int w, int h)
{
	m_FrameArr[frameIdx].setImgNum(imageIdx);
	m_FrameArr[frameIdx].setPosOffset(frameIntervalX, frameIntervalY);
	m_FrameArr[frameIdx].setImgOffset(imageIntervalX, imageIntervalY);
	m_FrameArr[frameIdx].setImgSize(w, h);
}

DWORD	cScene::getFrameTime(int frameIdx)
{
	return m_FrameTime[frameIdx];
}

void	cScene::destroyScene()
{
	m_MaxFrame				= 0;

	if( m_FrameArr != NULL )
	{
		delete []m_FrameArr;
		m_FrameArr			= NULL;
	}

	if( m_FrameTime != NULL )
	{
		delete []m_FrameTime;
		m_FrameTime			= NULL;
	}
}

int		cScene::getImgNum(int frameIdx)
{
	return m_FrameArr[frameIdx].getImgNum();
}

int		cScene::getImgSizeX(int frameIdx)
{
	return m_FrameArr[frameIdx].getImgSizeX();
}

int		cScene::getImgSizeY(int frameIdx)
{
	return m_FrameArr[frameIdx].getImgSizeY();
}

int		cScene::getPosOffsetX(int frameIdx)
{
	return m_FrameArr[frameIdx].getPosOffsetX();
}

int		cScene::getPosOffsetY(int frameIdx)
{
	return m_FrameArr[frameIdx].getPosOffsetY();
}

int		cScene::getImgOffsetX(int frameIdx)
{
	return m_FrameArr[frameIdx].getImgOffsetX();
}

int		cScene::getImgOffsetY(int frameIdx)
{
	return m_FrameArr[frameIdx].getImgOffsetY();
}
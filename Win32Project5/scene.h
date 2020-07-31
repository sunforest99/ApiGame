#pragma once

#include "frame.h"

class cScene
{
	int			m_MaxFrame;
	cFrame *	m_FrameArr;
	DWORD *		m_FrameTime;
public:
	cScene();
	~cScene();
	void		setMaxFrame(int maxFrame);
	void		setMaxElementOfFrame(int frameIdx,
		DWORD frameTime);
	void		addElementOfFrame(int frameIdx, 
		int imageIdx, 
		int frameIntervalX,
		int frameIntervalY,
		int imageIntervalX,
		int imageIntervalY,
		int w, int h);

	void		destroyScene();

	int			getMaxFrame();
	DWORD		getFrameTime(int frameIdx);
	int			getImgNum(int frameIdx);
	int			getImgSizeX(int frameIdx);
	int			getImgSizeY(int frameIdx);
	int			getPosOffsetX(int frameIdx);
	int			getPosOffsetY(int frameIdx);
	int			getImgOffsetX(int frameIdx);
	int			getImgOffsetY(int frameIdx);
};
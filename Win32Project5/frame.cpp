#include "frame.h"

cFrame::cFrame()
{
	m_ImgNum				= -1;
	m_ImgWidth				= -1;
	m_ImgHeight				= -1;
	m_PosOffsetX			= -1;
	m_PosOffsetY			= -1;
	m_ImgOffsetX			= -1;
	m_ImgOffsetY			= -1;
}

cFrame::~cFrame()
{

}

void	cFrame::setImgNum(int imgNum)
{
	m_ImgNum		= imgNum;
}

void	cFrame::setImgSize(int width, int height)
{
	m_ImgWidth		= width;
	m_ImgHeight		= height;
}

void	cFrame::setPosOffset(int xValue, int yValue)
{
	m_PosOffsetX	= xValue;
	m_PosOffsetY	= yValue;
}

void	cFrame::setImgOffset(int xValue, int yValue)
{
	m_ImgOffsetX	= xValue;
	m_ImgOffsetY	= yValue;
}

int		cFrame::getImgNum()
{
	return m_ImgNum;
}

int		cFrame::getImgSizeX()
{
	return m_ImgWidth;
}

int		cFrame::getImgSizeY()
{
	return m_ImgHeight;
}

int		cFrame::getPosOffsetX()
{
	return m_PosOffsetX;
}

int		cFrame::getPosOffsetY()
{
	return m_PosOffsetY;
}

int		cFrame::getImgOffsetX()
{
	return m_ImgOffsetX;
}

int		cFrame::getImgOffsetY()
{
	return m_ImgOffsetY;
}

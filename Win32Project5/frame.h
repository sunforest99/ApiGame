#pragma once

#include <Windows.h>

class cFrame
{
private:
	int 		m_ImgNum ;		//이미지가 저장된 배열의 인덱스
	int 		m_ImgWidth ;	//이미지 넓이
	int 		m_ImgHeight ;	//이미지 높이
	int 		m_PosOffsetX ;	//X 출력 offset 
	int 		m_PosOffsetY ;	//Y 출력 offset
	int 		m_ImgOffsetX ;	//원본이미지상의 x 좌표
	int 		m_ImgOffsetY ;	//원본이미지상의 y 좌표

public:
	cFrame() ;
	~cFrame() ;

	void		setImgNum(int imgNum);
	void		setImgSize(int width, int height);
	void		setPosOffset(int xValue, int yValue);
	void		setImgOffset(int xValue, int yValue);

	int			getImgNum();
	int			getImgSizeX();
	int			getImgSizeY();
	int			getPosOffsetX();
	int			getPosOffsetY();
	int			getImgOffsetX();
	int			getImgOffsetY();
};
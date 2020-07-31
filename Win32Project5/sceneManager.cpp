#include "My_Include.h"

//////////////////////////////////////////////////////////////////////////
//
// cSceneManager() : 생성자(멤버변수의 초기화)
//
// 인자값 : 없음
//
// 반환값 : 없음
//
cSceneManager::cSceneManager()
{
	m_Scene					= NULL;				
	m_CurFrame				= NULL;				
	m_CurKey				= NULL;				
	m_bFrameOnceCompleted	= FALSE;
	m_FrameIdx				= 0;
	
	m_MaxImage				= 0;
	m_ImgList				= NULL;
}


//////////////////////////////////////////////////////////////////////////
//
// ~cSceneManager() : 소멸자(동적할당된 멤버를 해제)
//
// 인자값 : 없음
//
// 반환값 : 없음
//
cSceneManager::~cSceneManager()
{
	destroyFrameManager();
}


//////////////////////////////////////////////////////////////////////////
//
// void setDC : 출력을 위한 메모리 DC를 설정한다.
//
// 인자값 : HDC		memDC	- 백버퍼 메모리 DC
//
// 반환값 : 없음
//
void	cSceneManager::setDC(HDC memDC)
{
	m_backDC				= memDC;
}


//////////////////////////////////////////////////////////////////////////
//
// void setImageNum() : 해당 프레임메니져에서 사용될 모든 이미지 갯수 설정 및
//						이미지 저장을 위한 객체 생성
//
// 인자값 : int		ImageNum	- 사용될 이미지 갯수
//
// 반환값 : 없음
//
void	cSceneManager::setImageNum(int ImageNum)
{
	m_MaxImage				= ImageNum;
	m_ImgList				= new cGdiImage[m_MaxImage];
}


//////////////////////////////////////////////////////////////////////////
//
// void setImage() : 이미지 저장을 위한 객체에 이미지 로드하기
//					 (이미지 저장을 위한 객체가 생성되어 있어야 함)
//
// 인자값 : int		ImageIdx	- 이미지 저장을 위해 생상된 객체가 저장된 배열의 인텍스
//			char*	ImgName		- 로드할 이미지의 경로 및 파일명
//
// 반환값 : 없음
//
void	cSceneManager::setImage(int ImageIdx, char* ImgName)
{
	m_ImgList[ImageIdx].setDC(m_backDC);
	m_ImgList[ImageIdx].Load(ImgName);
}


//////////////////////////////////////////////////////////////////////////
//
// void addScene() : 프레임 메니져에 씬을 생성한다.
//
// 인자값 : string	sceneName	 - 삽입될 씬의 이름(키)
//
// 반환값 : 없음
//
void	cSceneManager::addScene(char* sceneName)
{
	cScene*					pScene = new cScene();
	m_Scene					= pScene;
	m_SceneList[sceneName]	= pScene;
}


//////////////////////////////////////////////////////////////////////////
//
// void setMaxFrame() : 선택한 씬의 프레임의 수를 설정하고 이에 따른 모든 저장장소의 크기를 할당한다.
//
// 인자값 : int		maxFrame		- 해당 씬의 전체 프레임 수
//          
// 반환값 : 없음
//
void	cSceneManager::setMaxFrame(int maxFrame)
{
	m_Scene->setMaxFrame(maxFrame);
	m_FrameIdx				= 0;
}


//////////////////////////////////////////////////////////////////////////
//
// void setMaxElementOfFrame() : 생성된 씬의 프레임을 지정하지 않고 순처적으로 
//								 프레임을 구성하는 요소의 최대 개수를 설정한다.
//
// 인자값 : int		maxElement		- 최대 요수 수
//          DWORD	frameTime		- 프레임 시간
//          
// 반환값 : 없음
//
void	cSceneManager::setMaxElementOfFrame(DWORD frameTime)
{
	m_Scene->setMaxElementOfFrame(m_FrameIdx, frameTime);
	m_ElementOfFrameIdx = m_FrameIdx;
	m_FrameIdx++;
}


//////////////////////////////////////////////////////////////////////////
//
// void addElementOfFrame() : 프레임의 요소를 추가한다.
//
// 인자값 : int		imageIdx		- 이미지 번호(이미지 ID)
//          int		frameIntervalX  - 기준점으로부터 X축으로 이동하여 출력할 값
//			int		frameIntervalY	- 기준점으로부터 Y축으로 이동하여 출력할 값
//			int		imageIntervalX	- 이미지의 X축
//			int		imageIntervalY	- 이미지의 Y축
//			int		w				- 이미지의 넓이
//			int		h				- 이미지의 높이
//			int		layer			- 프레임의 레이어
//          
// 반환값 : 없음
//
void	cSceneManager::addElementOfFrame(int imageIdx,
										 int frameIntervalX, int frameIntervalY, 
										 int imageIntervalX, int imageIntervalY,
										 int w, int h)
{
	m_Scene->addElementOfFrame(m_ElementOfFrameIdx, 
		imageIdx, frameIntervalX, frameIntervalY, 
		imageIntervalX, imageIntervalY, w, h);
}


//////////////////////////////////////////////////////////////////////////
//
// void setFirstFrame() : 현재 씬의 프레임정보를 첫프레임으로 설정
//
// 인자값 : 없음
//          
// 반환값 : 없음
//
void	cSceneManager::setFirstFrame()
{
	m_CurFrame				= 0;
	m_bFrameOnceCompleted	= FALSE;
	m_OutFrameTime			= GetTickCount();
}


//////////////////////////////////////////////////////////////////////////
//
// void setLastFrame() : 현재 씬의 프레임정보를 마지막프레임으로 설정
//
// 인자값 : 없음
//          
// 반환값 : 없음
//
void	cSceneManager::setLastFrame()
{
	m_CurFrame				= m_Scene->getMaxFrame() - 1;
	m_OutFrameTime			= GetTickCount();
}


//////////////////////////////////////////////////////////////////////////
//
// void nextFrame() : 현재 씬의 프레임정보를 다음프레임으로 설정.
//					  프레임 출력시간보다 빠를 경우 return함.
//                    프레임 정보가 마지막 프레임 보다 클 경우 처음으로 설정하며, 씬의 츨력 완료 변수 TRUE로 설정함
//
// 인자값 : 없음
//          
// 반환값 : 없음
//
void	cSceneManager::nextFrame()
{
	if( GetTickCount() - m_OutFrameTime 
		< m_Scene->getFrameTime(m_CurFrame))
		return;

	m_CurFrame++;
	if( m_CurFrame >= m_Scene->getMaxFrame())
	{
		m_CurFrame				= 0;
		m_bFrameOnceCompleted	= TRUE;
	}
	m_OutFrameTime			= GetTickCount();
}


//////////////////////////////////////////////////////////////////////////
//
// void setScene() : 현재씬의 변경
//
// 인자값 : char*	sceneName	- 설정하고자 하는 씬의 이름(키)
//								  초기 addScene()를 통해 등록된 이름만 사용가능
//          
// 반환값 : 없음
//
void	cSceneManager::setScene(char* sceneName)
{
	map<char*, cScene*>::iterator	it;
	it						= m_SceneList.find(sceneName);
	if( it == m_SceneList.end() )
		return;
	else
	{
		m_CurKey			= it->first;
		m_Scene				= it->second;
		setFirstFrame();
	}
}


//////////////////////////////////////////////////////////////////////////
//
// void DrawFrame() : 현재 씬의 현재 프레임을 출력한다.
//
// 인자값 : int		x		 - 출력될 X좌표
//			int		y        - 출력될 Y좌표
//          
// 반환값 : 없음
//
void	cSceneManager::drawFrame(int x, int y)
{
	int						imgNum;
	int						sx, sy, iw, ih, ix, iy;

	imgNum				= m_Scene->getImgNum(m_CurFrame);
	sx					= m_Scene->getPosOffsetX(m_CurFrame) + x;
	sy					= m_Scene->getPosOffsetY(m_CurFrame) + y;
	iw					= m_Scene->getImgSizeX(m_CurFrame);
	ih					= m_Scene->getImgSizeY(m_CurFrame);
	ix					= m_Scene->getImgOffsetX(m_CurFrame);
	iy					= m_Scene->getImgOffsetY(m_CurFrame);

	m_ImgList[imgNum].Draw(sx, sy, ix, iy, iw, ih);
}


//////////////////////////////////////////////////////////////////////////
//
// void DrawFrameRGB() : 현재 씬의 현재 프레임을 출력한다.
//
// 인자값 : int		x		 - 출력될 X좌표
//			int		y        - 출력될 Y좌표
//			UING	uRGB	 - 투명처리될 색상          
//
// 반환값 : 없음
//
void	cSceneManager::drawFrameRGB(int x, int y, UINT uRGB)
{
	int						imgNum;
	int						sx, sy, iw, ih, ix, iy;

	imgNum				= m_Scene->getImgNum(m_CurFrame);
	sx					= m_Scene->getPosOffsetX(m_CurFrame) + x;
	sy					= m_Scene->getPosOffsetY(m_CurFrame) + y;
	iw					= m_Scene->getImgSizeX(m_CurFrame);
	ih					= m_Scene->getImgSizeY(m_CurFrame);
	ix					= m_Scene->getImgOffsetX(m_CurFrame);
	iy					= m_Scene->getImgOffsetY(m_CurFrame);

	m_ImgList[imgNum].Draw(sx, sy, ix, iy, iw, ih, iw, ih, uRGB);
}


//////////////////////////////////////////////////////////////////////////
//
// void DrawFrameAuto() : 현재 씬의 현재 프레임을 출력하고 프레임 정보를 증가 시킨다.
//
// 인자값 : int		x		 - 출력될 X좌표
//			int		y        - 출력될 Y좌표
//          
// 반환값 : 없음
//
void	cSceneManager::drawFrameAuto(int x, int y)
{
	drawFrame(x, y);
	nextFrame();
}


//////////////////////////////////////////////////////////////////////////
//
// void DrawFrameAutoRGB() : 현재 씬의 현재 프레임을 출력하고 프레임 정보를 증가 시킨다.
//
// 인자값 : int		x		 - 출력될 X좌표
//			int		y        - 출력될 Y좌표
//			UINT	uRGB	 - 투명처리될 색상정보          
//
// 반환값 : 없음
//
void	cSceneManager::drawFrameAutoRGB(int x, int y, UINT uRGB)
{
	drawFrameRGB(x, y, uRGB);
	nextFrame();
}


//////////////////////////////////////////////////////////////////////////
//
// void delAllScene() : 모든씬의 제거 및 모든 멤버 초기화
//
// 인자값 : 없음
//          
// 반환값 : 없음
//
void	cSceneManager::delAllScene()
{
	destroyFrameManager();
}


//////////////////////////////////////////////////////////////////////////
//
// void delScene() : 특정 씬의 제거
//
// 인자값 : char*	sceneName	- 제거할 씬의 이름(키)
//          
// 반환값 : 없음
//
void	cSceneManager::delScene(char* sceneName)
{
	map<char*, cScene*>::iterator	it;
	it						= m_SceneList.find(sceneName);
	if( it == m_SceneList.end() )
		return;
	else
	{	
		delete it->second;
		m_SceneList.erase(it->first);
	}
}


//////////////////////////////////////////////////////////////////////////
//
// void delSceneElement() : 특정 씬의 프레임 정보 제거
//
// 인자값 : cScene*		pScene	- 프레임 정보를 제거할 씬의 참조값
//          
// 반환값 : 없음
//
void	cSceneManager::delSceneElement(cScene* pScene)
{
	pScene->destroyScene();
}


//////////////////////////////////////////////////////////////////////////
//
// int getMaxFrame() : 현재 씬의 최대 프레임수를 반환한다.
//
// 인자값 : 없음
//          
// 반환값 : int					- 현재씬의 최대프레임수
//
int		cSceneManager::getMaxFrame()
{
	return m_Scene->getMaxFrame();
}


//////////////////////////////////////////////////////////////////////////
//
// int getCurFrame() : 현재 씬의 현재 프레임의 정보를 반환
//				
// 인자값 : 없음
//          
// 반환값 : int					- 현재 프레임값
//
int		cSceneManager::getCurFrame()
{
	return m_CurFrame;
}


//////////////////////////////////////////////////////////////////////////
//
// int destroyFrameManager() : 해당 프레임메니져 멤버 변수의 메모리 해제
//				
// 인자값 : 없음
//          
// 반환값 : 없음
//
void	cSceneManager::destroyFrameManager()
{
	map<char*, cScene*>::iterator it;
	for( it = m_SceneList.begin() ; it != m_SceneList.end() ; it++ )
	{
		delete it->second;
		//m_SceneList.erase(it->first);
	}

	if( m_ImgList != NULL )
		delete []m_ImgList;

	m_Scene					= NULL;				
	m_CurFrame				= NULL;				
	m_CurKey				= NULL;				
	m_bFrameOnceCompleted	= FALSE;
	m_FrameIdx				= 0;
	m_ElementOfFrameIdx		= 0;
	m_MaxImage				= 0;
}

BOOL	cSceneManager::getFrameOnce()
{
	return m_bFrameOnceCompleted;
}

char*	cSceneManager::getCurKey()
{
	return m_CurKey;
}

void	cSceneManager::setFrame(int frameIDX)
{
	if( frameIDX < 0 || frameIDX > getMaxFrame()-1 )
		return;

	m_CurFrame = frameIDX;
}
#pragma once

#include "scene.h"
#include "cGdiImage.h"
#include <string>
#include <map>
using namespace std;

class cSceneManager
{
	HDC						m_backDC;
	cGdiImage*				m_ImgList;				//사용될 이미지 리스트
	int						m_MaxImage;				//사용될 이미지 갯수
	map<char*, cScene*>		m_SceneList;			//씬를 관리하기 위한 컨테이너
	cScene*					m_Scene;				//현재 씬
	int						m_CurFrame;				//씬에서 현재 활성화된 프레임
	char*					m_CurKey;				//현재 씬의 key 값
	BOOL					m_bFrameOnceCompleted;	//한 씬의 모든 프레임이 출력하였을때
	DWORD					m_OutFrameTime;			//한프레임이 출력되었을때의 카운터

	int						m_FrameIdx;				//프레임 추가시 추가되어야 할 곳을 가르킨다.
	int						m_ElementOfFrameIdx;
public:
	cSceneManager();
	~cSceneManager();

	void		setDC(HDC memDC);
	void		setImageNum(int ImageNum);								//사용될 이미지수 설정
	void		setImage(int ImageIdx, char* ImgName);					//이미지 추가
	void		addScene(char* sceneName);								//씬 추가
	void		setMaxFrame(int maxFrame);								//씬의 프레임수 설정
	void		setMaxElementOfFrame(DWORD frameTime);	//해당 프레임의 이미지수와 프레임시간 설정
	void		addElementOfFrame(int imageIdx, 
		int frameIntervalX, int frameIntervalY, 
		int imageIntervalX,	int imageIntervalY,
		int w, int h);
	void		setFirstFrame();										//현재 씬의 첫프레임으로 이동
	void		setLastFrame();											//현재 씬의 마지막 프레임으로 이동
	void		nextFrame();											//현재 씬의 프레임 넘기기
	void		setFrame(int frameIDX);

	void		setScene(char* sceneName);								//씬 설정
	void		drawFrame(int x, int y);								//현재 씬의 현재 프레임 출력(프레임 넘기기 수동)
	void		drawFrameRGB(int x, int y, UINT uRGB);
	void		drawFrameAuto(int x, int y);							//현재 씬의 현재 프레임 출력(프레임 넘기기 자동)
	void		drawFrameAutoRGB(int x, int y, UINT uRGB);							//현재 씬의 현재 프레임 출력(프레임 넘기기 자동)

	void		delAllScene();											//모든 씬제거
	void		delScene(char* sceneName);								//특정씬 제거
	void		delSceneElement(cScene* pScene);						//특정씬의 프레임 정보 제거
	void		destroyFrameManager();									//모든 정보 제거

	int			getMaxFrame();											//현재 씬의 총 프레임수 구하기										
	int			getCurFrame();											//현재 씬의 프레임 번호 구하기
	BOOL		getFrameOnce();
	char*		getCurKey();

};
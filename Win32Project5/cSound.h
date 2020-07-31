#pragma once

#include <mmsystem.h>

class cSound
{
private:
	UINT			wDevieID;
	HWND			hWndNotify;
	MCI_OPEN_PARMS	mciOpenParms;
	MCI_PLAY_PARMS	mciPlayParms;

public:
	cSound()
	{
		wDevieID		= 0;
		hWndNotify		= NULL;
	}

	~cSound()
	{
		if( wDevieID )
			mciSendCommand(wDevieID, MCI_CLOSE, 0, (DWORD)NULL);
	}
	
	void setHandel(HWND hWnd)
	{
		hWndNotify		= hWnd;
	}

 	void playSound(char* fileName, BOOL loop)
	{
		if( loop )
			::PlaySound(fileName, NULL, SND_ASYNC | SND_LOOP);
		else
			::PlaySound(fileName, NULL, SND_ASYNC );
	}

	void stopSound()
	{
		::PlaySound(NULL, NULL, SND_ASYNC);
	}

	DWORD playMusic(char* fileName)
	{
		DWORD	Result;
		
		if( hWndNotify == NULL )
			return 0;

		if( wDevieID == 0 )
		{
			mciOpenParms.lpstrDeviceType	= "WaveAudio";
			mciOpenParms.lpstrElementName	= fileName;
			Result = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
				(DWORD)(LPVOID)&mciOpenParms);
			if( Result )
				return Result;

			wDevieID = mciOpenParms.wDeviceID;
		}

		mciPlayParms.dwCallback	= (DWORD)hWndNotify;
		Result = mciSendCommand(wDevieID, MCI_PLAY, MCI_NOTIFY, 
			(DWORD)(LPVOID)&mciPlayParms);
		if( Result )
		{
			mciSendCommand(wDevieID, MCI_CLOSE, 0, (DWORD)NULL);
			return Result;
		}
		return 0;
	}

	void playRepet()
	{
		mciSendCommand (wDevieID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD) (LPVOID) NULL);
		mciSendCommand(wDevieID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms);
	}

	void stopMusic()
	{
		if( wDevieID )
		{
			mciSendCommand(wDevieID, MCI_CLOSE, 0, (DWORD)NULL);
			wDevieID = 0;
		}
	}
};
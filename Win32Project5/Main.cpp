#include "My_Include.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND g_hWnd;
HINSTANCE g_hInst;
LPCTSTR lpszClass = "First";

cGdiGraphics g_Graphics;
cGdiImage g_Image;
BOOL g_keyCheck[5] = { false, };

cStateManger g_State;

cSound g_Sound;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	g_Graphics.Create(hWnd);
	g_Image.setDC(g_Graphics.getGraphicsDC());
	g_Image.Load("data/1945.bmp");
	g_Sound.setHandel(hWnd);
	g_hWnd = hWnd;

	ZeroMemory(&Message, sizeof(Message));
	
	int frameCount = 0;
	int frameTime = 0;
	int frameTimeLast = 0;
	int FPS = 0;
	float dt = 0.0f;
	RECT rect;

	while (Message.message != WM_QUIT)
	{
		::GetClientRect(hWnd, &rect);

		++frameCount;
		frameTime = GetTickCount();

		dt = (frameTime - frameTimeLast);

		if (dt >= 500)
		{
			FPS = frameCount;
			frameCount = 0;
			frameTimeLast = frameTime;
		}

		g_Graphics.ClearBlack();

		// 입력체크
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		g_State.GameFC((float)FPS);

		char strFPS[100];
		sprintf(strFPS, "[FPS] : %d", FPS * 2);
		g_Graphics.DrawString(0, 0, strFPS);

		g_Graphics.Present();
		
		Sleep(10);
	}

	g_Image.Destroy();
	g_Graphics.Destroy();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (g_State.m_State != NULL)
	{
		return (g_State.m_State)->MsgProc(hWnd, iMessage, wParam, lParam);
	}

	else
	{
		return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	}
}
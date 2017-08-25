//헤더파일을 사용한다
#include <Windows.h>

//전역변수 사용한다
HINSTANCE _hInstance;
HWND _hWnd;

LPTSTR _lpszClass = TEXT("종서네윈도우");

//함수 프로토타입 써준다
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
 MSG message;  //운영체제에서 발생하는 메시지 정보를 저장하기 위한 구조체(선언)
 WNDCLASS wndClass; //윈도우의 정보를 저장하기 위한 구조체 선언

 _hInstance = hInstance;  

 wndClass.cbClsExtra = 0;          //클래스 여분 메모리
 wndClass.cbWndExtra = 0;          //윈도우 여분 메모리
 wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //윈도우 백그라운드 색상
 wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);     //윈도우 커서
 wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);    //윈도우 아이콘
 wndClass.hInstance = hInstance;         //윈도우 인스턴스
 wndClass.lpfnWndProc = (WNDPROC)WndProc;      //프로시져
 wndClass.lpszClassName = _lpszClass;       //클래스 이름
 wndClass.lpszMenuName = NULL;         //메뉴이름
 wndClass.style = CS_HREDRAW | CS_VREDRAW;      //윈도우 스따일~

 //윈도우 클래스 등록
 RegisterClass(&wndClass);

 //윈도우 생성
 _hWnd = CreateWindow(
  _lpszClass,    //윈도우 클래스 이름
  _lpszClass,    //윈도우 타이틀바에 나타낼 문자열
  WS_OVERLAPPEDWINDOW, //윈도우 스타일
  50,      //윈도우 창 시작 X좌표
  50,      //윈도우 창 시작 Y좌표
  800,     //윈도우 가로크기
  600,     //윈도우 세로크기
  NULL,     //부모 윈도우 유무
  (HMENU)NULL,   //메뉴핸들
  hInstance,    //인스턴스 윈도우 지정
  NULL);

 //화면에 윈도우 보여준다
 ShowWindow(_hWnd, cmdShow);

 /*   게임용! 봉인풀지 말것 (풀라고 하기전까지)
 while (true)
 {
  if (PeekMessage(&message, NULL, OU, OU, PM_REMOVE))
  {
   if (message.message == WM_QUIT) break;
   TranslateMessage(&message);
   DispatchMessage(&message);
  }
  else
  {
   Render();
  }

 }
 */

 //메세지 루프
 while (GetMessage(&message, 0, 0, 0))
 {

  TranslateMessage(&message); //키보드 입력 메시지 처리를 담당
  DispatchMessage(&message); //실제로 윈도우로 전달해 준다
 }

 return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
 //hWnd : 어느 윈도우에서 메시지가 발생했는가?
 //iMessage : 메시지 구분 번호
 //wParam : 마우스 버튼 상태, 키보드 상태
 //lParam : 마우스 좌표위치 전달


 switch (iMessage)
 {
  case WM_DESTROY:
   PostQuitMessage(0);
  break;

 }

 return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}

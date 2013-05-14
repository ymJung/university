#include <windows.h> //Win32API 사용시 반드시 필요한 헤더.

//class name
#define MYWNDCLSNAME "MyWindowClass"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, 
						 WPARAM wParam, LPARAM lParam);
int WINAPI WinMain //최초 실행되는 함수
(HINSTANCE hInst,HINSTANCE hPrevInst, //어플리케이션 식별 정수값(인스턴스 핸들)을 얻음
				   LPSTR lpCmdLine, int nCmdShow) //명령행 문자열 포인터,메인윈도우 최초 출력상태 지정
{
	WNDCLASS wndcls;
	HWND hWnd,hWndOwned,hWndChild;
	MSG msg;

	//class
	ZeroMemory(&wndcls,sizeof(wndcls));
	wndcls.lpfnWndProc = WndProc;
	wndcls.hInstance = hInst;
	wndcls.hIcon = LoadIcon(0,IDI_APPLICATION);
	wndcls.hCursor = LoadCursor(0,IDC_ARROW);
	wndcls.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wndcls.lpszClassName = MYWNDCLSNAME;
	if(RegisterClass(&wndcls) == 0) return -1;

	//main window
	hWnd = CreateWindow(MYWNDCLSNAME, "My Window",WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,400,200,0,0,hInst,0);
	if(hWnd == 0) return -2;

	//Child window
	hWndChild = CreateWindow(MYWNDCLSNAME,"ChildWindow",WS_CHILDWINDOW | WS_CAPTION | WS_VISIBLE,
		0,0,200,100,hWnd,0,hInst,0);
	if(hWndChild == 0) return -2;

	//Owned
	hWndOwned = CreateWindow(MYWNDCLSNAME,"OwnedWindow",WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE,
		0,0,200,100,hWnd,0,hInst,0);
	if(hWndOwned == 0) return -2;

	//window output
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	//message roop
	while(GetMessage(&msg,0,0,0)){
		DispatchMessage(&msg);
	}

	//Quit
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg){
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


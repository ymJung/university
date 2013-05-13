#include <windows.h> //Win32API ���� �ݵ�� �ʿ��� ���.

//class name
#define MYWNDCLSNAME "MyWindowClass"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, 
						 WPARAM wParam, LPARAM lParam);
int WINAPI WinMain //���� ����Ǵ� �Լ�
(HINSTANCE hInst,HINSTANCE hPrevInst, //���ø����̼� �ĺ� ������(�ν��Ͻ� �ڵ�)�� ����
				   LPSTR lpCmdLine, int nCmdShow) //����� ���ڿ� ������,���������� ���� ��»��� ����
{
	WNDCLASS wndcls;
	HWND hWnd,hWndChild,hWndOwned;
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

	//child window
	hWndChild = CreateWindow(MYWNDCLSNAME, "Child",WS_CHILDWINDOW | WS_CAPTION | WS_VISIBLE,
		0,0,200,100,hWnd,0,hInst,0);
	if(hWnd == 0) return -2;
	
	//Owned window
	hWndOwned = CreateWindow(MYWNDCLSNAME, "Owned",WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE,
		0,0,200,100,hWnd,0,hInst,0);
	if(hWnd == 0) return -2;



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


BOOL SetWindowPos( // ��ȯ�� ������ TRUE
				  HWND hWnd, //�ش� ������ �ڵ�
				  HWND hWndInsertAfter, //Z������ �ٷ� �� �ڵ�
 				  int x, //x��ǥ
				  int y, //y��ǥ
				  int cx, //x��
				  int cy, //y����
				  UINT uFlags //���� ���� �÷���
				  );
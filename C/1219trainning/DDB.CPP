#include <windows.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="비트맵만들기.";

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(LTGRAY_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		  NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,hMemDC;
	PAINTSTRUCT ps;
	BYTE Bits[]={0xc3,0xff,0xbd,0xff,0x66,0xff,0x5a,0xff,0x5a,0xff,0x66,0xff,0xbd,0xff,0xbd,0xc3,0xff};
	HBITMAP hBitmap,hOldBitmap;
	switch (iMessage){
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		hMemDC=CreateCompatibleDC(hdc);
		hBitmap=CreateBitmap(8,8,1,1,Bits);
		hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
		BitBlt(hdc,2,2,8,8,hMemDC,0,0,SRCCOPY);
		SelectObject(hMemDC,hOldBitmap);
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}


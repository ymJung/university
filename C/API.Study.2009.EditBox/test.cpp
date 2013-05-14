#include <windows.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst; //인스턴스를 전역으로 지정

LPSTR lpszClass=TEXT("이동 EDIT 박스");
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
					 ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	
	hWnd=CreateWindow(lpszClass,"리스트박스 눌러서 타이틀바 수정",WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
#define ID_COMBOBOX 100
char *Items[]={"계란","오이","바나나","포도","딸기"};
char str[128];
HWND hCombo;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	int i;
	switch(iMessage) {
	case WM_CREATE:
		hCombo=CreateWindow("combobox",NULL,WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, //combobox << 윈도우 클래스 이름
			10,10,100,200,hWnd,(HMENU)ID_COMBOBOX,g_hInst,NULL); //g_hInst << WinMain에 들어옴
		for (i=0;i<5;i++)
			SendMessage(hCombo,CB_ADDSTRING,0,(LPARAM)Items[i]);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_COMBOBOX: 
			switch (HIWORD(wParam)) { //통지메세지는 HIWORD에 저장
			case CBN_SELCHANGE: //몇번(index)가 선택되는지 알아내어 해당되는 문자열의 명령
				i=SendMessage(hCombo, CB_GETCURSEL,0,0); //메세지를 보내 선택됨을 알림
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str); //LBTEXT(리스트박스의 텍스트)를 LPARAM의 str에 담아옴
				SetWindowText(hWnd, str); //핸들값을 str의 내용으로 바꿈
				break;
			case CBN_EDITCHANGE:
				GetWindowText(hCombo, str, 128); //콤보박스의 윈도우텍스트를 얻음
				SetWindowText(hWnd,str);
				break;
			}
		}
		return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

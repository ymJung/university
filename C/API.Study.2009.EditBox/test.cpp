#include <windows.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst; //�ν��Ͻ��� �������� ����

LPSTR lpszClass=TEXT("�̵� EDIT �ڽ�");
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
	
	hWnd=CreateWindow(lpszClass,"����Ʈ�ڽ� ������ Ÿ��Ʋ�� ����",WS_OVERLAPPEDWINDOW,
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
char *Items[]={"���","����","�ٳ���","����","����"};
char str[128];
HWND hCombo;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	int i;
	switch(iMessage) {
	case WM_CREATE:
		hCombo=CreateWindow("combobox",NULL,WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, //combobox << ������ Ŭ���� �̸�
			10,10,100,200,hWnd,(HMENU)ID_COMBOBOX,g_hInst,NULL); //g_hInst << WinMain�� ����
		for (i=0;i<5;i++)
			SendMessage(hCombo,CB_ADDSTRING,0,(LPARAM)Items[i]);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_COMBOBOX: 
			switch (HIWORD(wParam)) { //�����޼����� HIWORD�� ����
			case CBN_SELCHANGE: //���(index)�� ���õǴ��� �˾Ƴ��� �ش�Ǵ� ���ڿ��� ���
				i=SendMessage(hCombo, CB_GETCURSEL,0,0); //�޼����� ���� ���õ��� �˸�
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str); //LBTEXT(����Ʈ�ڽ��� �ؽ�Ʈ)�� LPARAM�� str�� ��ƿ�
				SetWindowText(hWnd, str); //�ڵ鰪�� str�� �������� �ٲ�
				break;
			case CBN_EDITCHANGE:
				GetWindowText(hCombo, str, 128); //�޺��ڽ��� �������ؽ�Ʈ�� ����
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

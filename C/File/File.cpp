#include <windows.h>
#include <stdio.h>

int main(void){
	HANDLE hIn,hOut,hOrig;
	INPUT_RECORD ir;
	DWORD mode;
	BOOL bCont = TRUE;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO cci;
	COORD csr;
	unsigned char ch;
	DWORD sz;
	FILE *fp;
	
	//�Է¹��� �ڵ�
	hIn = CreateFile("CONIN$",
		GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,OPEN_EXISTING,0,0);
	if(hIn == INVALID_HANDLE_VALUE){
		fprintf(stderr,"�Է¹��� �ڵ��� ����\n");
		return -1;
	}
	
	//��ũ������ �ڵ�
	hOrig = CreateFile("CONOUT$",
		GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,OPEN_EXISTING,0,0);
	if(hOrig == INVALID_HANDLE_VALUE){
		fprintf(stderr,"��ũ�� ���� �ڵ��� ����\n");
		CloseHandle(hIn);
		return -1;
	}
	
	//���ο� ��ũ�� ���� Ȱ��ȭ
	hOut = CreateConsoleScreenBuffer(
		GENERIC_READ|GENERIC_WRITE,0,NULL,
		CONSOLE_TEXTMODE_BUFFER,NULL);
	if(hOut == INVALID_HANDLE_VALUE){
		fprintf(stderr,"��ũ�����ۻ�������\n");
		CloseHandle(hOrig);
		CloseHandle(hIn);
		return -1;
	}
	SetConsoleActiveScreenBuffer(hOut);
	
	//������ ���� ����
	SetConsoleTitle("���������� (ESC�� ����)");
	
	//���콺 �Է��� �޴� �Է¸��
	GetConsoleMode(hIn, &mode);
	SetConsoleMode(hIn, mode|ENABLE_MOUSE_INPUT);
	
	//Ŀ���� ũ�⸦ ���ڼ��� ������
	cci.dwSize = 100;
	cci.bVisible = TRUE;
	SetConsoleCursorInfo(hOut,&cci);
	
	//�Է� ó������
	while(bCont){
		if(ReadConsoleInput(hIn,&ir,1,&sz)){
			//Ŀ������
			GetConsoleScreenBufferInfo(hOut,&csbi);
			csr.X = csbi.dwCursorPosition.X;
			csr.Y = csbi.dwCursorPosition.Y;
			//Ű���� �Է�
			if(ir.EventType == KEY_EVENT){
				if(ir.Event.KeyEvent.bKeyDown){
					switch(ir.Event.KeyEvent.wVirtualKeyCode){
						//ESC �� ����
					case VK_ESCAPE:
						bCont = FALSE;
						break;
						
						//ȭ��ǥ�� �̵�
					case VK_RIGHT:
						if(csr.X < csbi.dwSize.X-1){
							csr.X++;
							SetConsoleCursorPosition(hOut,csr);
						}
						break;
						
					case VK_LEFT:
						if(csr.X < csbi.dwSize.X-1){
							csr.X--;
							SetConsoleCursorPosition(hOut,csr);
						}
						break;
					case VK_RETURN:
						if(csr.Y<csbi.dwSize.Y-1){
							csr.X = 0;
							csr.Y++;
							SetConsoleCursorPosition(hOut,csr);
						}
						break;
					default:
						//��ȿ�ѹ���
						ch = (unsigned char)ir.Event.KeyEvent.uChar.AsciiChar;
						if(ch>=0x20){
							WriteFile(hOut,&ir.Event.KeyEvent.uChar.AsciiChar,1,&sz,NULL);
						}
					}
				}
			}
			//���콺
			
			else if(ir.EventType == MOUSE_EVENT){
				//��ư��
				if(ir.Event.MouseEvent.dwButtonState & 0x01){
					SetConsoleCursorPosition(hOut,ir.Event.MouseEvent.dwMousePosition);
				}
			}
		}
	}
	
	SetConsoleActiveScreenBuffer(hOrig);
	CloseHandle(hOrig);
	CloseHandle(hIn);
	
	CloseHandle(hOut);
	return 0;
	}
	
	

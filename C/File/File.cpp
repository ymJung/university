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
	
	//입력버퍼 핸들
	hIn = CreateFile("CONIN$",
		GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,OPEN_EXISTING,0,0);
	if(hIn == INVALID_HANDLE_VALUE){
		fprintf(stderr,"입력버퍼 핸들얻기 실패\n");
		return -1;
	}
	
	//스크린버퍼 핸들
	hOrig = CreateFile("CONOUT$",
		GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,OPEN_EXISTING,0,0);
	if(hOrig == INVALID_HANDLE_VALUE){
		fprintf(stderr,"스크린 버퍼 핸들얻기 실패\n");
		CloseHandle(hIn);
		return -1;
	}
	
	//새로운 스크린 버퍼 활성화
	hOut = CreateConsoleScreenBuffer(
		GENERIC_READ|GENERIC_WRITE,0,NULL,
		CONSOLE_TEXTMODE_BUFFER,NULL);
	if(hOut == INVALID_HANDLE_VALUE){
		fprintf(stderr,"스크린버퍼생성실패\n");
		CloseHandle(hOrig);
		CloseHandle(hIn);
		return -1;
	}
	SetConsoleActiveScreenBuffer(hOut);
	
	//윈도우 제목 변경
	SetConsoleTitle("문서편집기 (ESC로 종료)");
	
	//마우스 입력을 받는 입력모드
	GetConsoleMode(hIn, &mode);
	SetConsoleMode(hIn, mode|ENABLE_MOUSE_INPUT);
	
	//커서의 크기를 문자셀과 같도록
	cci.dwSize = 100;
	cci.bVisible = TRUE;
	SetConsoleCursorInfo(hOut,&cci);
	
	//입력 처리루프
	while(bCont){
		if(ReadConsoleInput(hIn,&ir,1,&sz)){
			//커서정보
			GetConsoleScreenBufferInfo(hOut,&csbi);
			csr.X = csbi.dwCursorPosition.X;
			csr.Y = csbi.dwCursorPosition.Y;
			//키보드 입력
			if(ir.EventType == KEY_EVENT){
				if(ir.Event.KeyEvent.bKeyDown){
					switch(ir.Event.KeyEvent.wVirtualKeyCode){
						//ESC 시 종료
					case VK_ESCAPE:
						bCont = FALSE;
						break;
						
						//화살표시 이동
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
						//유효한문자
						ch = (unsigned char)ir.Event.KeyEvent.uChar.AsciiChar;
						if(ch>=0x20){
							WriteFile(hOut,&ir.Event.KeyEvent.uChar.AsciiChar,1,&sz,NULL);
						}
					}
				}
			}
			//마우스
			
			else if(ir.EventType == MOUSE_EVENT){
				//버튼시
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
	
	

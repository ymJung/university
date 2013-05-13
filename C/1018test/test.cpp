// 기본 라이브러리 전처리
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
        // Dll파일 로드하기
        HINSTANCE hDll = LoadLibrary((LPCTSTR)"MakeDLL.dll");
 
        // Dll파일 로드 예외처리
        if( !hDll )
        {
                printf("Dll로드 실패!!\n");
                goto END_MAIN;
        }
        // 함수포인터얻고 사용하기
        int (*Sum)(int, int) = (int (*)(int, int))GetProcAddress(hDll, "Sum");
        printf("10 + 20 = %d\n", Sum(10,20));
        int (*Sub)(int, int) = (int (*)(int, int))GetProcAddress(hDll, "Sub");
        printf("10 - 20 = %d\n", Sub(10,20));
        int (*Mul)(int, int) = (int (*)(int, int))GetProcAddress(hDll, "Mul");
        printf("10 * 20 = %d\n", Mul(10,20));
        int (*Div)(int, int) = (int (*)(int, int))GetProcAddress(hDll, "Div");
        printf("10 / 20 = %d\n", Div(10,20));

END_MAIN:
        // Dll파일 언로드
        if( hDll ) FreeLibrary(hDll);
        system("pause");
        return 0;
}
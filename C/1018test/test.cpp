// �⺻ ���̺귯�� ��ó��
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
        // Dll���� �ε��ϱ�
        HINSTANCE hDll = LoadLibrary((LPCTSTR)"MakeDLL.dll");
 
        // Dll���� �ε� ����ó��
        if( !hDll )
        {
                printf("Dll�ε� ����!!\n");
                goto END_MAIN;
        }
        // �Լ������;�� ����ϱ�
        int (*Sum)(int, int) = (int (*)(int, int))GetProcAddress(hDll, "Sum");
        printf("10 + 20 = %d\n", Sum(10,20));
        int (*Sub)(int, int) = (int (*)(int, int))GetProcAddress(hDll, "Sub");
        printf("10 - 20 = %d\n", Sub(10,20));
        int (*Mul)(int, int) = (int (*)(int, int))GetProcAddress(hDll, "Mul");
        printf("10 * 20 = %d\n", Mul(10,20));
        int (*Div)(int, int) = (int (*)(int, int))GetProcAddress(hDll, "Div");
        printf("10 / 20 = %d\n", Div(10,20));

END_MAIN:
        // Dll���� ��ε�
        if( hDll ) FreeLibrary(hDll);
        system("pause");
        return 0;
}
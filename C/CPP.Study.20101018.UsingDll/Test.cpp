#ifdef __cplusplus	// �����Ϸ� Ÿ�� Ȯ�� 
        extern "C" {
#endif
       // ������ũ�� ����ϱ� ���� DLL�� Export Address Table�� 
			//�Լ��� ��ġ�� ��Ÿ������ �Լ� ȣ��Ծ��� __declspec�� ����
         #define DLL_EXPORT __declspec(dllexport)

         // �Լ� ������Ÿ�� ����
         int DLL_EXPORT Sum(int x, int y);
         int DLL_EXPORT Sub(int x, int y);
         int DLL_EXPORT Mul(int x, int y);
         int DLL_EXPORT Div(int x, int y);
#ifdef __cplusplus
        }
#endif

int DLL_EXPORT Sum(int x, int y) // �����Լ�
{
        return (x+y);
}
int DLL_EXPORT Sub(int x, int y)// �����Լ�
{
        return (x-y);
}
int DLL_EXPORT Mul(int x, int y)// �����Լ�
{
        return (x*y);
}
int DLL_EXPORT Div(int x, int y)//�������Լ�
{
        return (x/y);
}

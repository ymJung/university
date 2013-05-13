#ifdef __cplusplus	// 컴파일러 타입 확인 
        extern "C" {
#endif
       // 동적링크를 사용하기 위해 DLL상 Export Address Table에 
			//함수의 위치를 나타내도록 함수 호출규약을 __declspec로 선언
         #define DLL_EXPORT __declspec(dllexport)

         // 함수 프로토타입 선언
         int DLL_EXPORT Sum(int x, int y);
         int DLL_EXPORT Sub(int x, int y);
         int DLL_EXPORT Mul(int x, int y);
         int DLL_EXPORT Div(int x, int y);
#ifdef __cplusplus
        }
#endif

int DLL_EXPORT Sum(int x, int y) // 덧셈함수
{
        return (x+y);
}
int DLL_EXPORT Sub(int x, int y)// 뺄셈함수
{
        return (x-y);
}
int DLL_EXPORT Mul(int x, int y)// 곱셈함수
{
        return (x*y);
}
int DLL_EXPORT Div(int x, int y)//나눗셈함수
{
        return (x/y);
}

#include <iostream.h>
int a =1;
void main(){
	int a = 2;

	cout << "전역변수 :" << ::a << endl;
	cout << "지역변수 :" << a << endl;
	{
		int a = 3;
		cout << "지역변수 :" << a << endl;
		cout << "전역변수(한칸밖) :" << a << endl;
		
	}
}

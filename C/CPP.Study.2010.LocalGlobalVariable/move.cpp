#include <iostream.h>
int a =1;
void main(){
	int a = 2;

	cout << "�������� :" << ::a << endl;
	cout << "�������� :" << a << endl;
	{
		int a = 3;
		cout << "�������� :" << a << endl;
		cout << "��������(��ĭ��) :" << a << endl;
		
	}
}

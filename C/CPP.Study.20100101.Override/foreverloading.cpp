#include <iostream.h>

int Print_Values(int A);
double Print_Values(double B);
void Print_Values(char *str);
void Print_Values(int A, double B);

void main(){
	int Num1,A;
	double Num2,B,Sum;
	char *title;

	title = "함수의 다중정의";
	Print_Values(title);
	cout <<endl;

	title = "Data input";
	Print_Values(title);
	cout <<"Num1 input:";
	cin >> Num1;
	cout << "Num2 input:";
	cin >> Num2;
	cout <<endl;

	title = "다중정의 함수 호출";
	Print_Values(title);
	A = Print_Values(Num1);
	B = Print_Values(Num2);
	Print_Values(Num1,Num2);

	Sum = (double)A + B;
	cout << "Sum : " << Sum << endl;
}
int Print_Values(int A){
	cout << "Output num:" << A << endl;
	return A;
}
double Print_Values(double B){
	cout << "ouput real num"<< B << endl;
	return B;
}
void Print_Values(char *str){
	cout << str << endl;
}

void Print_Values(int A, double B){
	double C = (double)A + B;
	cout <<"Sum1 : " << C << endl;
}

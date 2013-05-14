#include<iostream>
#include<string>
#include<conio.h>
#include<stdio.h>
#include<time.h>
using namespace std;

#define BS 128
#define MB 1024

class Key_generator
{
public:
	char SeedKey[BS];
	char KeyStream[MB];
	double Keygentime;
	clock_t start;
	clock_t end;
public:
	void SeedkeyIn(char SeedKeySel);
	char ROTR(char mat,int num);
	char *KeyStreamGen(char Key[],int FilemsgLength);
	clock_t KeygentimeStart(clock_t );
	clock_t KeygentimeEnd(clock_t );
	double Key_gentime(clock_t start,clock_t end);

};

#include<iostream>
#include<string>
#include<conio.h>
#include<stdio.h>
#include<time.h>
using namespace std;

#define BS 128
#define MB 1024

class Main_Encryption
{
public:
	char KeyStream[MB];
	char SeedKey[BS];
	char InFilename[BS];
	char OutFilename[BS];
	char Filemsg[MB];
	char OutputData[MB];
	double Keygentime;
	int FilemsgLength;

public:
	void ProgramStart();
	void KeyIn();
	char* SeedkeySel();
	void Keystreamprint(char KeyS[]);
	void Keygentimeprint(double Keygentime);
	void FilenameSel();
	void OutFilenameSel();
	void Fileread(char InFilename[]);
	char* Fileprint();
	void Filewrite(char OutFilename[]);
	void XOROperation(char *Filemsg,char *KeyStream);
	void Outputprint();
	void Restart();
	void Exit();
};

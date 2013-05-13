#include <stdio.h>

int main(void){
	char name[100];
	char *pn;
	pn = name;
	gets(name);
	puts(name);
	gets(pn);
	puts(name);
	return 0;
}

#include <stdio.h>
#include <string.h>

int main(void)
{
	const char *buf = "Apple\nOrange\nBanana\n";
	FILE *fpBin,*fpTxt;

	//binary
	fpBin = fopen("binary.txt","wb");

	if(fpBin!=NULL){
		fwrite(buf,1,strlen(buf),fpBin);
		fclose(fpBin);
	}

	//Text
	fpTxt = fopen("text.txt","w");
	if(fpTxt != NULL){
		fwrite(buf,1,strlen(buf),fpTxt);
		fclose(fpTxt);
	}
	return 0;
}

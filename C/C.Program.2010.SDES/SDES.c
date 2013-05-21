#include <stdio.h>
#include <math.h>

unsigned cryption(unsigned char k,unsigned char p, int g);
void convert_d2b(char a, char *r, char cnt);
void print_array(char *s, char *a, int cnt);
void permution(char *x, char *p, char *y, char cnt);
void generate_subkey(char *kb, char *k1, char *k2);
void divide_array(char *x, char *y, char *z, char cnt);
void left_shift(char *x, char cnt, char scnt);
void combine_array(char *x, char *y, char *z, char cnt);
void compute_xor(char *x, char *y, char *z, char cnt);
char convert_b2d(char *x, char cnt);
void s_box(char *x, char (*s)[4], char *y);
void f_fuction(char *fi_l, char *fi_r, char *key, char *fr);

int main(void) {
	
	unsigned char p,k,c;
	int state,s;
	FILE *fi,*fo; //파일포인터
	printf("암호화 할 평문 또는 암호문을 input.txt 파일로 만들어 작성하세요\n");
	printf("수행할 작업을 선택하세요(1:암호화 2: 복호화 3:종료) : ");
	scanf("%d",&s);
	if(s!=1 && s!=2 ) return 1; //1도2도 아니면 종료

	printf("키를 한문자 입력하세요 : ");
	getchar(); //첫번째 scanf 후에 엔터키 무시.
	scanf ("%c",&k);

	

	fi=fopen("input.txt","rt"); //fopen파일안의 자료가 램에 올라옴,fi에 저장
	if(fi==NULL){
		printf("Check InputFile !");
		return 1; //비정상 종료이기때문에 1값.
	}

	fo=fopen("output.txt","wt"); //암호문출력
	if(fo==NULL){
		printf("Check OutputFile !");
		return 1; //비정상 종료이기때문에 1값.
	}
	p = fgetc(fi); //파일에서 한문자만 읽어와라
	while(!feof(fi)){ //한문자씩읽어들여 암호화, feof:현재파일포인터가 파일의 끝인가를 체크
		c = cryption(k,p,s); // 암호/복호처리

		fputc(c,fo); //결과 한문자를 파일에 출력
		p = fgetc(fi);
	}

	state = fclose(fi); //Input파일닫기가 되면 state에 0을 리턴 
	if(state !=0){
		printf("InputFile close error ! \n");
		return 1;
	}
	
	state = fclose(fo); //Output파일닫기가 되면 state에 0을 리턴 
	if(state !=0){
		printf("OutputFile close error ! \n");
		return 1;
	}
	
	return 0;
}

//결과값 암호/복호화함수(키,평문/암호문,암복호구분)
unsigned cryption(unsigned char k,unsigned char p, int g){
	char pb[8]={0,}, kb[10]={0,0,0,0,0,0,0,0,1,0};
	char key1[8]={0,}, key2[8]={0,};
	char ip[8]={2,6,3,1,4,8,5,7}, ipr[8]={0,}, ipr_l[4]={0,}, ipr_r[4]={0,};
	char fr1[4]={0,}, fr2[4]={0,};
	char ipc[8]={0,}, ipi[8]={4,1,3,5,7,2,8,6}, cb[8]={0,};
	unsigned char c;

	
	convert_d2b(p, pb, 8);	// 평문을 이진수로 변환
	convert_d2b(k, kb, 8);	// 키를 이진수로 변환

	print_array("평문이진수: ", pb, 8);		// 평문이진수 출력
	print_array("키  이진수: ", kb, 10);	// 키이진수 출력

	generate_subkey(kb, key1, key2);	// 서버키 생성
	print_array("메인함수에서 첫번째 서브키: ", key1, 8);	// 키이진수 출력
	print_array("메인함수에서 두번째 서브키: ", key2, 8);	// 키이진수 출력

	// 암호화
	permution(pb, ip, ipr, 8);	// IP 수행
	print_array("IP 수행 결과: ", ipr, 8);	// IP 수행 결과 출력

	divide_array(ipr, ipr_l, ipr_r, 8); // 두분으로 분리
	print_array("IP 수행 결과(왼쪽): ", ipr_l, 4);	// IP 수행 결과 왼쪽 출력
	print_array("IP 수행 결과(오른쪽): ", ipr_r, 4);	// IP 수행 결과 오른쪽 출력

	if(g==1){ // 암호화
		f_fuction(ipr_l,ipr_r,key1,fr1);
		f_fuction(ipr_r, fr1,key2, fr2);

	}else { //복호화
		f_fuction(ipr_l,ipr_r,key2,fr1);
		f_fuction(ipr_r, fr1,key1, fr2);

	}

	

	combine_array(fr2, fr1, ipc, 4);	// 두 F 함수 결과 합침
	print_array("두 F함수 결과 합침: ", ipc, 8);	// 두 F 함수 결과 합침 출력

	permution(ipc, ipi, cb, 8);	// IP inverse 수행, 암호문 이진수 산출(cb)
	print_array("암호문 이진수 : ", cb, 8);	// 암호문 이진수 출력

	c = convert_b2d(cb, 8);	// 이진수를 십진수로 변환
	printf("암호문: %c\n", c);
	
	return c;


}

void f_fuction(char *fi_l, char *fi_r, char *key, char *fr) {
	char ep[8]={4,1,2,3,2,3,4,1}, epr[8]={0,};
	char xorr[8]={0,}, xorr_l[4]={0,}, xorr_r[4]={0,};
	char s0[4][4]={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
	char s1[4][4]={{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};
	char sbox_l[2]={0,}, sbox_r[2]={0,}, sboxr[4]={0,}; 
	char p4[4]={2,4,3,1}, p4r[4]={0,};

	permution(fi_r, ep, epr, 8);	// ep 수행
	print_array("EP 수행 결과: ", epr, 8);	// EP 수행 결과 출력

	compute_xor(epr, key, xorr, 8); // XOR 수행
	print_array("XOR 수행 결과: ", xorr, 8);	// XOR 수행 결과 출력

	divide_array(xorr, xorr_l, xorr_r, 8); // 두분으로 분리
	print_array("XOR 수행 결과(왼쪽): ", xorr_l, 4);	// XOR 수행 결과 왼쪽 출력
	print_array("XOR 수행 결과(오른쪽): ", xorr_r, 4);	// XOR 수행 결과 오른쪽 출력

	s_box(xorr_l, s0, sbox_l);	// S0 박스 수행
	s_box(xorr_r, s1, sbox_r);	// S1 박스 수행
	print_array("S-BOX 수행 결과(왼쪽): ", sbox_l, 2);	// S-BOX 수행 결과 왼쪽 출력
	print_array("S-BOX 수행 결과(오른쪽): ", sbox_r, 2);	// S-BOX 수행 결과 오른쪽 출력

	combine_array(sbox_l, sbox_r, sboxr, 2);
	print_array("S-BOX 합침 결과 : ", sboxr, 4);	// S-BOX 합침 결과 출력

	permution(sboxr, p4, p4r, 4);	// P4 수행
	print_array("P4 수행 결과: ", p4r, 4);	// P4 수행 결과 출력

	compute_xor(fi_l, p4r, fr, 4); // XOR 수행
	print_array("F 함수 수행 결과: ", fr, 4);	// F 함수 수행 결과 출력
}




// 십지수를 이진수로 변환하는 함수 (십진수입력값, 결과이진수배열, 이진수크기)
void convert_d2b(char a, char *r, char cnt) {
	int i = cnt-1;
	do {
		r[i] = a % 2;
		a = a / 2;
		i = i - 1;
	} while (a>0);
}

void print_array(char *s, char *a, int cnt) {
	int i;

	printf("%s", s);
	for(i=0; i<cnt; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

void generate_subkey(char *kb, char *k1, char *k2) {
	char p10[10] = {3,5,2,7,4,10,1,9,8,6};
	char p10r[10]={0,}, p10r_l[5]={0,}, p10r_r[5]={0,};
	char p8[8] = {6,3,7,4,8,5,10,9};


	permution(kb, p10, p10r, 10);
	print_array("P10결과 : ", p10r, 10);			// P10 결과 출력

	divide_array(p10r, p10r_l, p10r_r, 10);			// 두부분으로 분리
	print_array("P10결과 왼쪽 : ", p10r_l, 5);		// P10 결과 왼쪽 출력
	print_array("P10결과 오른쪽 : ", p10r_r, 5);	// P10 결과 오른쪽 출력

	left_shift(p10r_l, 5, 1);	// 왼쪽 1비트 쉬프트
	left_shift(p10r_r, 5, 1);	// 왼쪽 1비트 쉬프트
	print_array("쉬프트 결과 왼쪽 : ", p10r_l, 5);		// 쉬프트 결과 왼쪽 출력
	print_array("쉬프트 결과 오른쪽 : ", p10r_r, 5);	// 쉬프트 결과 오른쪽 출력

	combine_array(p10r_l, p10r_r, p10r, 5);
	print_array("배열합침 결과 : ", p10r, 10);	// 배열합침 결과 출력

	permution(p10r, p8, k1, 8);	// P8 수행하여 첫번째 키 생성
	print_array("첫번째 키 : ", k1, 8);	// 배열합침 결과 출력

	// 두번째 서브키 생성 과정
	left_shift(p10r_l, 5, 2);	// 왼쪽 2비트 쉬프트
	left_shift(p10r_r, 5, 2);	// 왼쪽 2비트 쉬프트
	print_array("쉬프트 결과 왼쪽 : ", p10r_l, 5);		// 쉬프트 결과 왼쪽 출력
	print_array("쉬프트 결과 오른쪽 : ", p10r_r, 5);	// 쉬프트 결과 오른쪽 출력

	combine_array(p10r_l, p10r_r, p10r, 5);
	print_array("배열합침 결과 : ", p10r, 10);	// 배열합침 결과 출력

	permution(p10r, p8, k2, 8);	// P8 수행하여 두번째 키 생성
	print_array("두번째 키 : ", k2, 8);	// 배열합침 결과 출력
}

// 순열 (입력배열, 순열배열, 결과배열, 배열크기)
void permution(char *x, char *p, char *y, char cnt) {
	char i;
	for(i=0; i<cnt; i++) {
		y[i] = x[p[i]-1];
	}
}

// 입력배열을 반씩 분리 (입력배열, 왼쪽배열, 오른쪽배열, 입력크기)
void divide_array(char *x, char *y, char *z, char cnt) {
	char i;
	for(i=0; i<cnt; i++) {
		if(i<cnt/2)
			y[i] = x[i];
		else
			z[i-cnt/2] = x[i];
	}
}

// 왼쪽 쉬프트 함수 (입력배열, 입력배열갯수, 쉬프트갯수)
void left_shift(char *x, char cnt, char scnt) {
	char i, j, temp;

	for(j=0; j<scnt; j++) {			// scnt 번 쉬프트 수행
		temp = x[0];
		for(i=0; i<cnt-1; i++) {
			x[i] = x[i+1];
		}
		x[i] = temp;
	}
}

// 두 배열을 합치는 함수(첫번째배열, 두번째배열, 결과배열, 배열크기)
void combine_array(char *x, char *y, char *z, char cnt) {
	char i;

	for(i=0; i<cnt; i++) {
		z[i] = x[i];
		z[i+cnt] = y[i];
	}
}

// XOR 함수 (첫번째입력, 두번째입력, 결과배열, 크기)
void compute_xor(char *x, char *y, char *z, char cnt) {
	char i;
	for(i=0; i<cnt; i++) {
		if(x[i]==y[i]) 
			z[i] = 0;
		else 
			z[i] = 1;
	}
}

// S BOX 함수 (입력배열, S-BOX변환배열, 결과배열)
void s_box(char *x, char (*s)[4], char *y) {
	char t[2], z[2];
	t[0]=x[0]; t[1]=x[3];	// 행
	z[0]=x[1]; z[1]=x[2];	// 열

	convert_d2b(s[convert_b2d(t, 2)][convert_b2d(z, 2)], y, 2);
}

// 이진수를 십진수로 변환하는 함수 (이진수입력배열, 입력배열크기)
char convert_b2d(char *x, char cnt) {
	char y=0, i;
	for(i=cnt-1;i>=0;i--) {
		y = y + x[i] * (char) pow(2, (cnt-1)-i);
	}

	return y;
}


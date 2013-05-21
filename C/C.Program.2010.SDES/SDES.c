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
	FILE *fi,*fo; //����������
	printf("��ȣȭ �� �� �Ǵ� ��ȣ���� input.txt ���Ϸ� ����� �ۼ��ϼ���\n");
	printf("������ �۾��� �����ϼ���(1:��ȣȭ 2: ��ȣȭ 3:����) : ");
	scanf("%d",&s);
	if(s!=1 && s!=2 ) return 1; //1��2�� �ƴϸ� ����

	printf("Ű�� �ѹ��� �Է��ϼ��� : ");
	getchar(); //ù��° scanf �Ŀ� ����Ű ����.
	scanf ("%c",&k);

	

	fi=fopen("input.txt","rt"); //fopen���Ͼ��� �ڷᰡ ���� �ö��,fi�� ����
	if(fi==NULL){
		printf("Check InputFile !");
		return 1; //������ �����̱⶧���� 1��.
	}

	fo=fopen("output.txt","wt"); //��ȣ�����
	if(fo==NULL){
		printf("Check OutputFile !");
		return 1; //������ �����̱⶧���� 1��.
	}
	p = fgetc(fi); //���Ͽ��� �ѹ��ڸ� �о�Ͷ�
	while(!feof(fi)){ //�ѹ��ھ��о�鿩 ��ȣȭ, feof:�������������Ͱ� ������ ���ΰ��� üũ
		c = cryption(k,p,s); // ��ȣ/��ȣó��

		fputc(c,fo); //��� �ѹ��ڸ� ���Ͽ� ���
		p = fgetc(fi);
	}

	state = fclose(fi); //Input���ϴݱⰡ �Ǹ� state�� 0�� ���� 
	if(state !=0){
		printf("InputFile close error ! \n");
		return 1;
	}
	
	state = fclose(fo); //Output���ϴݱⰡ �Ǹ� state�� 0�� ���� 
	if(state !=0){
		printf("OutputFile close error ! \n");
		return 1;
	}
	
	return 0;
}

//����� ��ȣ/��ȣȭ�Լ�(Ű,��/��ȣ��,�Ϻ�ȣ����)
unsigned cryption(unsigned char k,unsigned char p, int g){
	char pb[8]={0,}, kb[10]={0,0,0,0,0,0,0,0,1,0};
	char key1[8]={0,}, key2[8]={0,};
	char ip[8]={2,6,3,1,4,8,5,7}, ipr[8]={0,}, ipr_l[4]={0,}, ipr_r[4]={0,};
	char fr1[4]={0,}, fr2[4]={0,};
	char ipc[8]={0,}, ipi[8]={4,1,3,5,7,2,8,6}, cb[8]={0,};
	unsigned char c;

	
	convert_d2b(p, pb, 8);	// ���� �������� ��ȯ
	convert_d2b(k, kb, 8);	// Ű�� �������� ��ȯ

	print_array("��������: ", pb, 8);		// �������� ���
	print_array("Ű  ������: ", kb, 10);	// Ű������ ���

	generate_subkey(kb, key1, key2);	// ����Ű ����
	print_array("�����Լ����� ù��° ����Ű: ", key1, 8);	// Ű������ ���
	print_array("�����Լ����� �ι�° ����Ű: ", key2, 8);	// Ű������ ���

	// ��ȣȭ
	permution(pb, ip, ipr, 8);	// IP ����
	print_array("IP ���� ���: ", ipr, 8);	// IP ���� ��� ���

	divide_array(ipr, ipr_l, ipr_r, 8); // �κ����� �и�
	print_array("IP ���� ���(����): ", ipr_l, 4);	// IP ���� ��� ���� ���
	print_array("IP ���� ���(������): ", ipr_r, 4);	// IP ���� ��� ������ ���

	if(g==1){ // ��ȣȭ
		f_fuction(ipr_l,ipr_r,key1,fr1);
		f_fuction(ipr_r, fr1,key2, fr2);

	}else { //��ȣȭ
		f_fuction(ipr_l,ipr_r,key2,fr1);
		f_fuction(ipr_r, fr1,key1, fr2);

	}

	

	combine_array(fr2, fr1, ipc, 4);	// �� F �Լ� ��� ��ħ
	print_array("�� F�Լ� ��� ��ħ: ", ipc, 8);	// �� F �Լ� ��� ��ħ ���

	permution(ipc, ipi, cb, 8);	// IP inverse ����, ��ȣ�� ������ ����(cb)
	print_array("��ȣ�� ������ : ", cb, 8);	// ��ȣ�� ������ ���

	c = convert_b2d(cb, 8);	// �������� �������� ��ȯ
	printf("��ȣ��: %c\n", c);
	
	return c;


}

void f_fuction(char *fi_l, char *fi_r, char *key, char *fr) {
	char ep[8]={4,1,2,3,2,3,4,1}, epr[8]={0,};
	char xorr[8]={0,}, xorr_l[4]={0,}, xorr_r[4]={0,};
	char s0[4][4]={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
	char s1[4][4]={{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};
	char sbox_l[2]={0,}, sbox_r[2]={0,}, sboxr[4]={0,}; 
	char p4[4]={2,4,3,1}, p4r[4]={0,};

	permution(fi_r, ep, epr, 8);	// ep ����
	print_array("EP ���� ���: ", epr, 8);	// EP ���� ��� ���

	compute_xor(epr, key, xorr, 8); // XOR ����
	print_array("XOR ���� ���: ", xorr, 8);	// XOR ���� ��� ���

	divide_array(xorr, xorr_l, xorr_r, 8); // �κ����� �и�
	print_array("XOR ���� ���(����): ", xorr_l, 4);	// XOR ���� ��� ���� ���
	print_array("XOR ���� ���(������): ", xorr_r, 4);	// XOR ���� ��� ������ ���

	s_box(xorr_l, s0, sbox_l);	// S0 �ڽ� ����
	s_box(xorr_r, s1, sbox_r);	// S1 �ڽ� ����
	print_array("S-BOX ���� ���(����): ", sbox_l, 2);	// S-BOX ���� ��� ���� ���
	print_array("S-BOX ���� ���(������): ", sbox_r, 2);	// S-BOX ���� ��� ������ ���

	combine_array(sbox_l, sbox_r, sboxr, 2);
	print_array("S-BOX ��ħ ��� : ", sboxr, 4);	// S-BOX ��ħ ��� ���

	permution(sboxr, p4, p4r, 4);	// P4 ����
	print_array("P4 ���� ���: ", p4r, 4);	// P4 ���� ��� ���

	compute_xor(fi_l, p4r, fr, 4); // XOR ����
	print_array("F �Լ� ���� ���: ", fr, 4);	// F �Լ� ���� ��� ���
}




// �������� �������� ��ȯ�ϴ� �Լ� (�������Է°�, ����������迭, ������ũ��)
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
	print_array("P10��� : ", p10r, 10);			// P10 ��� ���

	divide_array(p10r, p10r_l, p10r_r, 10);			// �κκ����� �и�
	print_array("P10��� ���� : ", p10r_l, 5);		// P10 ��� ���� ���
	print_array("P10��� ������ : ", p10r_r, 5);	// P10 ��� ������ ���

	left_shift(p10r_l, 5, 1);	// ���� 1��Ʈ ����Ʈ
	left_shift(p10r_r, 5, 1);	// ���� 1��Ʈ ����Ʈ
	print_array("����Ʈ ��� ���� : ", p10r_l, 5);		// ����Ʈ ��� ���� ���
	print_array("����Ʈ ��� ������ : ", p10r_r, 5);	// ����Ʈ ��� ������ ���

	combine_array(p10r_l, p10r_r, p10r, 5);
	print_array("�迭��ħ ��� : ", p10r, 10);	// �迭��ħ ��� ���

	permution(p10r, p8, k1, 8);	// P8 �����Ͽ� ù��° Ű ����
	print_array("ù��° Ű : ", k1, 8);	// �迭��ħ ��� ���

	// �ι�° ����Ű ���� ����
	left_shift(p10r_l, 5, 2);	// ���� 2��Ʈ ����Ʈ
	left_shift(p10r_r, 5, 2);	// ���� 2��Ʈ ����Ʈ
	print_array("����Ʈ ��� ���� : ", p10r_l, 5);		// ����Ʈ ��� ���� ���
	print_array("����Ʈ ��� ������ : ", p10r_r, 5);	// ����Ʈ ��� ������ ���

	combine_array(p10r_l, p10r_r, p10r, 5);
	print_array("�迭��ħ ��� : ", p10r, 10);	// �迭��ħ ��� ���

	permution(p10r, p8, k2, 8);	// P8 �����Ͽ� �ι�° Ű ����
	print_array("�ι�° Ű : ", k2, 8);	// �迭��ħ ��� ���
}

// ���� (�Է¹迭, �����迭, ����迭, �迭ũ��)
void permution(char *x, char *p, char *y, char cnt) {
	char i;
	for(i=0; i<cnt; i++) {
		y[i] = x[p[i]-1];
	}
}

// �Է¹迭�� �ݾ� �и� (�Է¹迭, ���ʹ迭, �����ʹ迭, �Է�ũ��)
void divide_array(char *x, char *y, char *z, char cnt) {
	char i;
	for(i=0; i<cnt; i++) {
		if(i<cnt/2)
			y[i] = x[i];
		else
			z[i-cnt/2] = x[i];
	}
}

// ���� ����Ʈ �Լ� (�Է¹迭, �Է¹迭����, ����Ʈ����)
void left_shift(char *x, char cnt, char scnt) {
	char i, j, temp;

	for(j=0; j<scnt; j++) {			// scnt �� ����Ʈ ����
		temp = x[0];
		for(i=0; i<cnt-1; i++) {
			x[i] = x[i+1];
		}
		x[i] = temp;
	}
}

// �� �迭�� ��ġ�� �Լ�(ù��°�迭, �ι�°�迭, ����迭, �迭ũ��)
void combine_array(char *x, char *y, char *z, char cnt) {
	char i;

	for(i=0; i<cnt; i++) {
		z[i] = x[i];
		z[i+cnt] = y[i];
	}
}

// XOR �Լ� (ù��°�Է�, �ι�°�Է�, ����迭, ũ��)
void compute_xor(char *x, char *y, char *z, char cnt) {
	char i;
	for(i=0; i<cnt; i++) {
		if(x[i]==y[i]) 
			z[i] = 0;
		else 
			z[i] = 1;
	}
}

// S BOX �Լ� (�Է¹迭, S-BOX��ȯ�迭, ����迭)
void s_box(char *x, char (*s)[4], char *y) {
	char t[2], z[2];
	t[0]=x[0]; t[1]=x[3];	// ��
	z[0]=x[1]; z[1]=x[2];	// ��

	convert_d2b(s[convert_b2d(t, 2)][convert_b2d(z, 2)], y, 2);
}

// �������� �������� ��ȯ�ϴ� �Լ� (�������Է¹迭, �Է¹迭ũ��)
char convert_b2d(char *x, char cnt) {
	char y=0, i;
	for(i=cnt-1;i>=0;i--) {
		y = y + x[i] * (char) pow(2, (cnt-1)-i);
	}

	return y;
}


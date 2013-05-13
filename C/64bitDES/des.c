-------------------------------------------------------------

/**************************************************************
 *   �ۼ��� : Seok-jun Bae
 *   ��  �� : 2001. 4. 28.
 *   ��  �� : DES ��ȣȭ ��ȣȭ ���α׷�  
 *   E-mail : www@qprk.pe.kr
 *   
 *   �� �ҽ��ڵ忡 ���� ��� ������ �����ϴ�. 
 *   �� �ҽ��� ���� �����Ҽ� ������ �ٸ����� ������ ���
 *   �� ������ ���ԵǾ�� �մϴ�.
 **************************************************************/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>


#define P2C 1                   /* ���� ��ȣ�� */
#define C2P 2                   /* ��ȣ�� ������ */
#define BUFFSIZE 20500          /* 20KByte */
#define RWSIZE   20000
//#define DISP_char2binary
//#define DISP_char2binary_strlen       
//#define DISP_keyGenerate_binary2char
//#define DISP_keyGenerate_leftShift
//#define DISP_keyGenerate_final
//#define DISP_desMain_C2P_Key
//#define DISP_desMain_fileState
//#define DISP_startDes_textBuff
//#define DISP_startDes_tgtData
//#define DISP_desRound_sboxValue
//#define DISP_desRound_xor
#define for_windog              /* linux������ �ʿ������ �ּ�ó��.. */


void keyGenerate(char *);
void desMain(int, char *, char *);
void startDes(int, int, char *, char *);
void desRound(int *, int *);
void char2binary(int *, char *, int);
char binary2char(int *);
void swap32bit(int *, int *, int *);
void helpText(); 

void keyProc(char *keySrc);



int MAT_IP[64]={58, 50, 42, 34, 26 ,18 ,10, 2,
                60, 52, 44, 36, 28, 20, 12, 4,
                62, 54, 46, 38, 30, 22, 14, 6,
                64, 56, 48, 40, 32, 24, 16, 8,
                57, 49, 41, 33, 25, 17, 9, 1,
                59, 51, 43, 35, 27, 19, 11, 3,
                61, 53, 45, 37, 29, 21, 13, 5,
                63, 55, 47, 39, 31, 23, 15, 7};

int MAT_IP_1[64]={40, 8, 48, 16, 56, 24, 64, 32,
                  39, 7, 47, 15, 55, 23, 63, 31,
                  38, 6, 46, 14, 54, 22, 62, 30,
                  37, 5, 45, 13, 53, 21, 61, 29,
                  36, 4, 44, 12, 52, 20, 60, 28,
                  35, 3, 43, 11, 51, 19, 59, 27,
                  34, 2, 42, 10, 50, 18, 58, 26,
                  33, 1, 41, 9, 49, 17, 57, 25};

int MAT_EXP[48]={32, 1, 2, 3, 4, 5,
                 4, 5, 6, 7, 8, 9,
                 8, 9, 10, 11, 12, 13,
                 12, 13, 14, 15, 16, 17,
                 16, 17, 18, 19, 20, 21,
                 20, 21, 22, 23, 24, 25,
                 24, 25, 26, 27, 28, 29,
                 28, 29, 30, 31, 32, 1};

int MAT_PERMU[32]={16, 7, 20, 21, 29, 12, 28, 17,
                   1, 15, 23, 26, 5, 18, 31, 10,
                   2, 8, 24, 14, 32, 27, 3, 9,
                   19, 13, 30, 6, 22, 11, 4, 25};

int MAT_SBOX[8][4][16]={{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                         {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                         {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                         {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 2, 14, 10, 0, 6, 13}},
  
                        {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                         {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                         {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                         {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

                        {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                         {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                         {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                         {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

                        {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                         {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                         {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                         {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
            
                        {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                         {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                         {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                         {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

                        {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                         {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                         {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                         {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

                        {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                         {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                         {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                         {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

                        {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                         {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                         {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                         {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

int MAT_PC_1[56]={57, 49, 41, 33, 25, 17, 9,
                  1, 58, 50, 42, 34, 26, 18,
                  10, 2, 59, 51, 43, 35, 27,
                  19, 11, 3, 60, 52, 44, 36,
                  63, 55, 47, 39, 31, 23, 15,
                  7, 62, 54, 46, 38, 30, 22,
                  14, 6, 61, 53, 45, 37, 29,
                  21, 13, 5, 28, 20, 12, 4};

int MAT_PC_2[48]={14, 17, 11, 24, 1, 5, 3, 28,
                  15, 6, 21, 10, 23, 19, 12, 4,
                  26, 8, 16, 7, 27, 20, 13, 2,
                  41, 52, 31, 37, 47, 55, 30, 40,
                  51, 45, 33, 48, 44, 49, 39, 56,
                  34, 53, 46, 42, 50, 36, 29, 32};

int KEY[16][48];


/**************************************************************
 *  main
 * 
 **************************************************************/
main(int argc, char **argv)
{

  if(argc != 4)
    helpText();
  
  if(!(strcmp(argv[1],"-c")))
    desMain( P2C, argv[2], argv[3]);
  else if(!(strcmp(argv[1],"-p")))
    desMain( C2P, argv[2], argv[3]);
  else
    helpText();


}     

/**************************************************************
 * DES ��ȣȭ �� ��ȣȭ
 * jobType  : P2C(0)�ϰ�� ��ȣȭ, C2P(1)�ϰ�� ��ȣȭ
 * passWord : �Էµ� key
 * fileName : ��ȣȭ �� ��ȣȭ �� file�̸�
 **************************************************************/
void desMain(int jobType, char *passWord, char *fileName)
{
  FILE *srcFile, *targetFile;
  int tempKey[16][48];
  long int dataSize;
  long int readSize, writeSize;
  char *fileSrcBuff, *fileTgtBuff;
  char nameTemp[100]={0,};
  char qprkDes[100]={0,};
  int i,j;

  //////////////////////////////////////////////////////////
  keyGenerate(passWord);        /* DES�� ����� Key ���� */
  ////////////////////////////////////////////////////////
  if(jobType == C2P){                   /* C2P�ϰ�� key�� �������� ���� */
    for(i=0; i<16; i++)
      for(j=0; j<48; j++)
        tempKey[15-i][j] = KEY[i][j];
    for(i=0; i<16; i++)
      for(j=0; j<48; j++)
        KEY[i][j] = tempKey[i][j];
#ifdef DISP_desMain_C2P_Key     /* C2P ���� Key Ȯ�� */
    printf("\n\nC2P key\n");
    for(i=0; i<16; i++){
      for(j=0; j<48; j++)
        printf("%d", KEY[i][j]);

      printf("\n");
    }//  for(i=0; i<16; i++){
#endif
  }//  if(jobType){

  strcpy(nameTemp,fileName);
  if(jobType == C2P){           /* target file �̸� ���� */
    if( (strcmp(".des", fileName+(strlen(fileName)-4)))){ /* ��ȣȭ�� filename �˻� */
      printf("%s is not qprkDES!!\n\n",fileName);
      helpText(); 
    }//  if( !(strcmp(".des", filename+(strlen(fileName)-4)))){
    nameTemp[ strlen(fileName)-4 ] = '\0'; /* file name�� .des�� ���� */
  } else {                      /* jobType �� P2C�ΰ�� */
    nameTemp[ strlen(fileName)-4 ] = '\0'; /* file name�� .des�� ���� */
    sprintf(qprkDes,"%s.des",nameTemp);
  }//  else {

  if( (srcFile = fopen( fileName, "r+b" )) == NULL ){ /* source file�� ���� */
    printf("Source file can not open!!!! -%s- \n", fileName);
    exit(0);
  }//  if( (srcFile=(fileName, "r"))==NULL ){

  fseek(srcFile, 0, SEEK_END);  /* srcFile�� ũ�⸦ �˾ƺ��� */
  readSize = ftell(srcFile);    /* �� ũ�⸸ŭ ���۸� ��� srcFile�� */
  fseek(srcFile, 0, SEEK_SET);  /* buff�� �����ϰ�  srcFile�� �ݴ´�*/
  dataSize = readSize / 8;

#ifdef DISP_desMain_fileState
  printf("���� fileũ��:%ld  ������8���:%d  \n", readSize, dataSize);
#endif
  dataSize++;  /* ������ fileũ�⺸�� ���۸� ũ�� ��� ���� */

  /////////////////////////////////////////////////////////////////////////////////////////
#ifdef for_windog
  if(readSize > RWSIZE){     /* fileũ�Ⱑ 20K �̻��̸� ���� ����. ����������
�ʿ����*/
    // 25000 �� RWSIZE�� 8�� ���� ��
    //#define BUFFSIZE 200200   
    //#define RWSIZE   200000

    if(jobType == C2P){         /* C2P�ϰ�� ����� file size�� �о�� */
      fread(&writeSize, sizeof(long int), 1, srcFile);
      fgets(qprkDes, 100, srcFile);  /* ���� file���� �о�� */
      qprkDes[ strlen(qprkDes) -1] = '\0';  /* \n ���� */
      strcpy(nameTemp, qprkDes);
      readSize -= sizeof(long int);
#ifdef DISP_desMain_fileState
      printf("write size : %ld\n",writeSize);
#endif
    }//  if(jobType == C2P){    

    if( (targetFile = fopen( qprkDes, "w+b" )) == NULL ){ /* target file�� ���� */
      printf("Target file open error!!!! -%s- \n", qprkDes);
      exit(0);
    }//  if( (targetFile = fopen( nameTemp, "w" )) == NULL ){ 

      if(jobType == P2C){
        fwrite(&readSize, sizeof(long int), 1, targetFile); /* file size�� ���� */
        fprintf(targetFile,"%s\n",fileName);
      } 

    fileSrcBuff = (char *)malloc(sizeof(char) * BUFFSIZE); /* Buff�� memory�Ҵ� */
    fileTgtBuff = (char *)malloc(sizeof(char) * BUFFSIZE);

    for(i=0; i< ((readSize/RWSIZE) + 1); i++){ /* 200000Byte �� �߶� ��ȣ, ��ȣȭ */
      memset(fileSrcBuff, 0, sizeof(char) * BUFFSIZE);  /* �Ҵ�� ������ \0�� �ʱ�ȭ */
      memset(fileTgtBuff, 0, sizeof(char) * BUFFSIZE);
      
      fread(fileSrcBuff, RWSIZE, 1, srcFile); /* file������ buff�� ���� */
#ifdef DISP_desMain_fileState
      printf("file���� �о�� ����\n%s\n", fileSrcBuff);
#endif

    //////////////////////////////////////////////////////////////////////////////////
      startDes(jobType, RWSIZE/8, fileSrcBuff, fileTgtBuff); /* ��ȣȭ ��ȣȭ�� ���� */
    ////////////////////////////////////////////////////////////////////////////////

#ifdef DISP_desMain_fileState
      printf("job type : %d\n", jobType);
      printf("target file name: %s\n",qprkDes); /* test */
#endif

      if(jobType == P2C){
        fwrite(fileTgtBuff, RWSIZE, 1, targetFile); /* buff�� ������ file�� ���� */
      } else {
        if(writeSize <= RWSIZE){
        fwrite(fileTgtBuff, writeSize, 1, targetFile); /* buff�� ������ file�� ���� */
        break;
        } else {
        fwrite(fileTgtBuff, RWSIZE, 1, targetFile); /* buff�� ������ file�� ���� */
        }
      }//  else {
      
      writeSize -= RWSIZE;
    }//  for(i=0; i< ((readSize/200000) + 1); i++){

    
    fclose(srcFile);
    fclose(targetFile);
    free(fileSrcBuff);
    free(fileTgtBuff);

    return;
  }//  if(readSize > RWSIZE){
#endif
  /////////////////////////////////////////////////////////////////////////////////////////

#ifdef DISP_desMain_fileState
  printf("malloc�� ũ��:%ld \n", dataSize*8);
#endif
  fileSrcBuff = (char *)malloc(dataSize*8); /* Buff�� memory�Ҵ� �� �ʱ�ȭ */
  fileTgtBuff = (char *)malloc(dataSize*8);

  memset(fileSrcBuff, 0, dataSize*8);   /* �Ҵ�� ������ \0�� �ʱ�ȭ */
  memset(fileTgtBuff, 0, dataSize*8);

  if(jobType == C2P){           /* C2P�ϰ�� ����� file size�� �о�� */
    fread(&writeSize, sizeof(long int), 1, srcFile);
    fgets(qprkDes, 100, srcFile);  /* ���� file���� �о�� */
    qprkDes[ strlen(qprkDes) -1] = '\0';  /* \n ���� */
    strcpy(nameTemp, qprkDes);
    readSize -= sizeof(long int);
#ifdef DISP_desMain_fileState
    printf("write size : %ld\n",writeSize);
#endif
  }//  if(jobType == C2P){    

  
  fread(fileSrcBuff, readSize, 1, srcFile); /* file������ buff�� ���� */
#ifdef DISP_desMain_fileState
  printf("file���� �о�� ����\n%s\n", fileSrcBuff);
#endif
  fclose(srcFile);

  //////////////////////////////////////////////////////////////////////////////////
  startDes(jobType, dataSize, fileSrcBuff, fileTgtBuff); /* ��ȣȭ ��ȣȭ�� ���� */
  ////////////////////////////////////////////////////////////////////////////////

#ifdef DISP_desMain_fileState
  printf("job type : %d\n", jobType);
  printf("target file name: %s\n",qprkDes); /* test */
#endif

  if( (targetFile = fopen( qprkDes, "w+b" )) == NULL ){ /* target file�� ���� */
    printf("Target file open error!!!! -%s- \n", qprkDes);
    exit(0);
  }//  if( (targetFile = fopen( nameTemp, "w" )) == NULL ){ 

  if(jobType == P2C){
    fwrite(&readSize, sizeof(long int), 1, targetFile); /* file size�� ���� */
    fprintf(targetFile,"%s\n",fileName);
    fwrite(fileTgtBuff, dataSize*8, 1, targetFile); /* buff�� ������ file�� ���� */
  } else {
    fwrite(fileTgtBuff, writeSize, 1, targetFile); /* buff�� ������ file�� ���� */
  }//  else {

  fclose(targetFile);
  free(fileSrcBuff);
  free(fileTgtBuff);
  
}


/**************************************************************
 * des ��ȣȭ, ��ȣȭ�� �Ѵ�
 * jobType  : P2C ��ȣȭ, C2P ��ȣȭ
 * dataSize : srcData�� ũ�� / 8 + 1
 * srcData �� ��ȣȭ,��ȣȭ�Ǿ� tgtData�� ����ȴ�
 **************************************************************/
void startDes(int jobType, int dataSize, char *srcData, char *tgtData )
{
  int srcBinary[64]={0,}, tgtBinary[64]={0,}, binaryBuff[64]={0,};
  int leftData[32]={0,}, rightData[32]={0,}, swapBuff[32]={0,};
  int tgtIndex=0;
  char textBuff[9]={'\0',};
  int i, j, k;

  for(i=0, tgtIndex=0; i<dataSize; i++){ /* Data�� ������ ���鼭 ��ȣȭ, ��ȣȭ
�Ѵ� */
    memset(textBuff, 0, 9);
    memcpy(textBuff, (srcData + tgtIndex), 8);  /* srcData���� 8�ھ� textBuff�κ��� */

#ifdef DISP_startDes_textBuff   /* ����� textbuff�� ������ ǥ�� */
    printf("text buff : %s\n", textBuff);
#endif

    char2binary(binaryBuff, textBuff, 8); /* textBuff�� binary��   */

    for(j=0; j<64; j++)              /* Initial Permutation */
      srcBinary[j] = binaryBuff[ MAT_IP[j]-1 ];

    if(jobType == P2C) 
      for(j=0; j<32; j++){   /* �ϳ��� 64bit�� ���� left, right data �� ������*/
        leftData[j] = srcBinary[j];
        rightData[j] = srcBinary[j+32];
      }//  for(j=0; j<32; j++){
    else                /* ��ȣȭ �Ұ�� left data�� right data�� ��ġ�� �ٲ۴� */
      for(j=0; j<32; j++){   /* �ϳ��� 64bit�� ���� left, right data �� ������*/
        rightData[j] = srcBinary[j];
        leftData[j] = srcBinary[j+32];
      }//  for(j=0; j<32; j++){

    //////////////////////////////////////////////////////////////////////////
    desRound(leftData, rightData);
    //////////////////////////////////////////////////////////////////////////

    if(jobType == P2C) 
      swap32bit(leftData, rightData, swapBuff); /* 32bit swap */

    for(j=0; j<32; j++){     /* ���� left, right data �� �ϳ��� 64bit�� ���Ѵ� */
      binaryBuff[j] = rightData[j]; /* ���� 32bit swap�� �Ѵ� */
      binaryBuff[j+32] = leftData[j];
    }//  for(j=0; j<32; j++){

    for(j=0; j<64; j++)              /* Inverse Initial Permutation */
      tgtBinary[j] = binaryBuff[ MAT_IP_1[j]-1 ];

    memset(textBuff, 0, 9);
    for(j=0,k=0; j<64; j+=8, k++) /* tgtBinary�� ascii�� ������ textBuff�� ���� */
      textBuff[k] = binary2char(&tgtBinary[j]);

    memcpy((tgtData + tgtIndex), textBuff, 8);  /* textBuff�� ������ tgtData�� ���� */

#ifdef DISP_startDes_tgtData    /* ����� textbuff�� ������ ǥ�� */
    printf("tgtData : %s\n", (tgtData + tgtIndex));
#endif

                                /* strncpy�� �������� ���� �ʳ�? */
    tgtIndex += 8;
  }//  for(i=0; i<dataSize; i++){

}


/**************************************************************
 * Round
 **************************************************************/
void desRound(int *leftData, int *rightData)
{
  int sboxOut[32]={0,}, leftFinal[32]={0,}, permuOut[32]={0,};
  int eBuff[48]={0,}, eBuffOut[48]={0,};
  int sboxRow, sboxCol, sboxValue;
  int i, j, k, keyIndex;

  for(keyIndex=0; keyIndex<16; keyIndex++){  /* 16���� round�� ��ģ�� */

    for(i=0; i<32; i++)              /* ��������� �ִ� */
      leftFinal[i] = *(rightData+i);

    for(i=0; i<48; i++){             /* E table ���� */
      eBuff[i] = *(rightData + (MAT_EXP[i] -1));
#ifdef DISP_desRound_xor        /* xor��Ȳ Ȯ�� */
      printf("eBuff[i] = *(rightData + (MAT_EXP[i] -1)) ----> %d = %d + %d\n"
             , eBuff[i] , *(rightData + (MAT_EXP[i] -1)), MAT_EXP[i] -1);
#endif
    }//  for(i=0; i<48; i++){

    
    for(i=0; i<48; i++){             /* eBuff xor key */
      eBuffOut[i] = eBuff[i] ^ KEY[keyIndex][i];
#ifdef DISP_desRound_xor        /* xor��Ȳ Ȯ�� */
      printf("keyIndes :%d, i:%d,      ", keyIndex, i);
      printf("eBuff xor key (eBuffOut = eBuff ^ key)->");
      printf("%d = %d ^ %d\n",eBuffOut[i], eBuff[i], KEY[keyIndex][i]);
#endif
    }//  for(i=0; i<48; i++){
  
    for(i=0, j=0, k=0; i<8; i++){    /* sBox ���� */
      sboxRow = (eBuffOut[j+0] * 2) + eBuffOut[j+5];
      sboxCol = (eBuffOut[j+1] * 8) + (eBuffOut[j+2] * 4) + (eBuffOut[j+3] * 2) + eBuffOut[j+4];
      sboxValue = MAT_SBOX[i][sboxRow][sboxCol];
      sboxOut[k]   = ((sboxValue & 8)  ? 1:0 );
      sboxOut[k+1] = ((sboxValue & 4)  ? 1:0 );
      sboxOut[k+2] = ((sboxValue & 2)  ? 1:0 );
      sboxOut[k+3] = sboxValue & 1; 
#ifdef DISP_desRound_sboxValue  /* xbox�� ���õ� ���� ���� */
      printf("sboxRow :%d, sboxCol :%2d, sbox value %d : %2d\n",sboxRow, sboxCol, i, sboxValue);
      printf("sboxOut : %d %d %d %d\n",sboxOut[k], sboxOut[k+1], sboxOut[k+2], sboxOut[k+3]);
#endif
      j += 6;
      k += 4;
    }//  for(i=0, k=0; i<8; i++){

    for(i=0; i<32; i++)              /* sboxOut �� p table���� */
      permuOut[i] = sboxOut[ MAT_PERMU[i]-1 ];  
  
    for(i=0; i<32; i++){             /* permuOut xor leftData �� rightData�� ����*/
      *(rightData+i) = *(leftData+i) ^ permuOut[i];
#ifdef DISP_desRound_xor        /* xor��Ȳ Ȯ�� */
      printf("left xor permu (rightData = leftData ^ permuOut)->");
      printf("%d = %d ^ %d\n", *(rightData+i), *(leftData+i), permuOut[i]);
#endif
    }//  for(i=0; i<32; i++){
  
    for(i=0; i<32; i++)              /* ÷�� ������ leftFinal�� leftData�� ���� */
      *(leftData+i) = leftFinal[i];

  }//  for(keyIndex=0; keyIndex<16; keyIndex++){

}


/**************************************************************
 * 32bit swap
 **************************************************************/
void swap32bit(int *leftBit, int *rightBit, int *buffBit)
{
  int i;
  
  for(i=0; i<32; i++)
    buffBit[i] = leftBit[i];

  for(i=0; i<32; i++)
    leftBit[i] = rightBit[i];

  for(i=0; i<32; i++)
    rightBit[i] = buffBit[i];

}


/**************************************************************
 * 16�� Ű �����
 * key�� �Է� ������ ������ ���������� 8Byte�� ����Ѵ�.
 **************************************************************/
void keyGenerate(char *keySrc)
{
  int keySchedule[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
  int binaryKey[64] = {0,};
  int pc1[56]={0,};
  char tempKey[9];
  int i, j, k, l, tmp1, tmp2, srcLen;

  if( (strlen(keySrc))>8 )   /* �Էµ� ��ȣ�� ���̰� 8�� �̻��̸� */
    keyProc(keySrc);

  strncpy(tempKey, keySrc, 8);
  tempKey[8] = '\0';
  srcLen = strlen( tempKey);
  char2binary(binaryKey, tempKey, srcLen);
  memset(tempKey, 0, 8);
  
#ifdef DISP_keyGenerate_binary2char /* �׳� ���� */
  printf("\n\nkeyGenerate_binary2char\n");
  for(i=0, k=0;i<8;i++){
    for(j=0;j<8;j++){
      printf("%d ",binaryKey[k]);
      k++;
    }
    printf("\n");
  }
  printf("\n");
  printf("\n");

  printf("binary2char=:");
  for(i=0; i<64; i += 8){
    printf("%c",binary2char(&binaryKey[i]));
  }//  for(i=0; i<56; i += 8){
  printf("\n");
#endif

  for(i=0; i<56; i++)                /* 64bit�� 56bit�� ���̴°� */
    pc1[i] = binaryKey[ MAT_PC_1[i]-1 ];

#ifdef DISP_keyGenerate_leftShift /* left shift ��Ȳ Ȯ�� */
  printf("\n\n left shift\n");
#endif

  for(i=0; i<16; i++){
    for(j=0; j<keySchedule[i]; j++){ /* left shift */
      tmp1 = pc1[0];
      tmp2 = pc1[28];
      for(k=1; k<28; k++){
        pc1[k-1] = pc1[k];
        pc1[k+27] = pc1[k+28];
      }//  for(k=1; k<28; k++){
      pc1[27] = tmp1;
      pc1[55] = tmp2;
    }//  for(j=0; j<keySchedule[i]; j++){

#ifdef DISP_keyGenerate_leftShift /* left shift ��Ȳ Ȯ�� */
    for(l=0; l<56; l++){
      if(l==28)
        printf("  ");         
      printf("%d", pc1[l]);
    }//  for(i=0; i<16; i++){
    printf("\n");
#endif

    for(j=0; j<48; j++)              /* 56bit �� 48bit�� �ٿ��� ���� - ���� key */
      KEY[i][j] = pc1[ MAT_PC_2[j]-1 ];
  }//  for(i=0; i<16; i++){

#ifdef DISP_keyGenerate_final   /* ���� key 16�� Ȯ�� */
  printf("\n\nfinal key\n");
  for(i=0; i<16; i++){
    for(j=0; j<48; j++)
      printf("%d", KEY[i][j]);
    printf("\n");
  }//  for(i=0; i<16; i++){
#endif

}

/**************************************************************
 * ���̰� �� key�� 8char�� ���̱�
 * 12345678���� 1234�� keySrc�� ���ڿ����� ���������� �ڷ�����
 * 5678�� keySrc�� ù��°���� ����
 * ���� ����� keySrc�� ���� ���� 4�� ���� ��ŭ 
 * ���̳� �ڷ� �̵�
 **************************************************************/
void keyProc(char *keySrc)
{
  char *temp;
  int srcLen=0, dev4;
  int i,j;
  


  srcLen = strlen(keySrc);
  temp = (char *)malloc(srcLen+1);
  memset(temp, 0, srcLen +1);
  strcpy(temp, keySrc);
  memset(keySrc, 0, srcLen);
  
  dev4 = srcLen / 4;
  
  srcLen-- ;

  for(i=0,j=0;i<4;i++,j+=dev4){
    *(keySrc+i)   = *(temp+srcLen-j);
    *(keySrc+i+4) = *(temp+j);
    //    printf("\nkeyProc--->%c\n", *(temp+srcLen-j));
  }//  for(i=0;i<4;i++){

  //  printf("\nkeyProc--->%s\n\n",keySrc);
}

/**************************************************************
 * char�� 2���� �ڵ�� �����
 * target : 2���� �ڵ尡 ����� �迭
 * char   : 2������ ���� ���ڿ�
 * srcLen : 2������ ���� ���ڿ��� ����
 **************************************************************/
void char2binary(int *target, char *src, int srcLen)
{
  int targetIndex=0, i, j;
  char oneChar,temp1, temp2;

#ifdef DISP_char2binary         /* char�� binary�Ǵ� ��Ȳ ���� */
  printf("orgkey      :%s\n",src);
#endif

#ifdef DISP_char2binary_strlen          /* char�� binary�Ǵ� ��Ȳ ���� */
  printf("%d ",strlen(src));
#endif

  for(i=0 ; i<srcLen; i++){
    oneChar=*(src+i);
    for(j=7; j>=0; j--){
      temp1 = oneChar >> j;
      temp2 = temp1 & 0x0001;
      *(target+targetIndex) = (temp2 == 1 ? 1:0);
      targetIndex++;
    }//  for(j=0;j<=8;j++){
  }//  for(i=0,srcLen;i<=srcLen;i++){

#ifdef DISP_char2binary         /* char�� binary�Ǵ� ��Ȳ ���� */
  printf("\n\nfirst display of char2binary\n");
  for(i=0,targetIndex=0; i<srcLen; i++){
    for(j=0; j<8; j++){
      printf("%d ", *(target+targetIndex));
      targetIndex++;
    }//  for(j=0; j<8; j++){
    printf("\n");
  }//  for(i=0; i<srcLen; i++){
#endif

}


/**************************************************************
 * 8���� 2������ �ϳ��� char�� �����
 * src : 8���� 2�� �ڵ�
 * return : ������� �ϳ��� char
 **************************************************************/
char binary2char(int *src)
{
  char temp;
  int i,j,inTemp=1, chTemp=0;

  for(i=0; i<8; i++){
    inTemp=1;
    if( *(src+i)) {
      for(j=7; j>i; j--)
        inTemp *= 2;
      chTemp += inTemp;
    }//  if( *(src+i)) {
  }//  for(i=0;i<8;i++){
  temp=chTemp;
  return temp;
}

/**************************************************************
 * hele text
 **************************************************************/
void helpText()
{
  printf("\n���� : des [OPTION] [password] [file]\n\n");
  printf("Option......\n");
  printf("-c    : ��ȣȭ\n");
  printf("-h    : �����\n");
  printf("-p    : ��ȣȭ\n\n");
  printf("password.....\n");
  printf("password�� ���ڿ��� ������ ������� \"�� ������\n");
  printf("Example : \"pass word\"\n\n");
  printf("file......\n");
  printf("file�� �̸��� ��ȣȭ�� .des�� file name �ڿ� ����\n");
  printf("��ȣȭ�� file���� .des�� ���� ���� file name�� ���\n\n");
  printf("���� ����Ʈ www@qprk.pe.kr\n\n");
  exit(0);
}

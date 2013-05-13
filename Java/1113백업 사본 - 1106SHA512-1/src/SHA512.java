public class SHA512 {
	private static final long[] k = { //상수 키 선언
		 0x428a2f98d728ae22L, 0x7137449123ef65cdL,
		 0xb5c0fbcfec4d3b2fL, 0xe9b5dba58189dbbcL,
		 0x3956c25bf348b538L, 0x59f111f1b605d019L,
		 0x923f82a4af194f9bL, 0xab1c5ed5da6d8118L,
		 0xd807aa98a3030242L, 0x12835b0145706fbeL,
		 0x243185be4ee4b28cL, 0x550c7dc3d5ffb4e2L,
		 0x72be5d74f27b896fL, 0x80deb1fe3b1696b1L,
		 0x9bdc06a725c71235L, 0xc19bf174cf692694L,
		 0xe49b69c19ef14ad2L, 0xefbe4786384f25e3L,
		 0x0fc19dc68b8cd5b5L, 0x240ca1cc77ac9c65L,
		 0x2de92c6f592b0275L, 0x4a7484aa6ea6e483L,
		 0x5cb0a9dcbd41fbd4L, 0x76f988da831153b5L,
		 0x983e5152ee66dfabL, 0xa831c66d2db43210L,
		 0xb00327c898fb213fL, 0xbf597fc7beef0ee4L,
		 0xc6e00bf33da88fc2L, 0xd5a79147930aa725L,
		 0x06ca6351e003826fL, 0x142929670a0e6e70L,
		 0x27b70a8546d22ffcL, 0x2e1b21385c26c926L,
		 0x4d2c6dfc5ac42aedL, 0x53380d139d95b3dfL,
		 0x650a73548baf63deL, 0x766a0abb3c77b2a8L,
		 0x81c2c92e47edaee6L, 0x92722c851482353bL,
		 0xa2bfe8a14cf10364L, 0xa81a664bbc423001L,
		 0xc24b8b70d0f89791L, 0xc76c51a30654be30L,
		 0xd192e819d6ef5218L, 0xd69906245565a910L,
		 0xf40e35855771202aL, 0x106aa07032bbd1b8L,
		 0x19a4c116b8d2d0c8L, 0x1e376c085141ab53L,
		 0x2748774cdf8eeb99L, 0x34b0bcb5e19b48a8L,
		 0x391c0cb3c5c95a63L, 0x4ed8aa4ae3418acbL,
		 0x5b9cca4f7763e373L, 0x682e6ff3d6b2b8a3L,
		 0x748f82ee5defb2fcL, 0x78a5636f43172f60L,
		 0x84c87814a1f0ab72L, 0x8cc702081a6439ecL,
		 0x90befffa23631e28L, 0xa4506cebde82bde9L,
		 0xbef9a3f7b2c67915L, 0xc67178f2e372532bL,
		 0xca273eceea26619cL, 0xd186b8c721c0c207L,
		 0xeada7dd6cde0eb1eL, 0xf57d4f7fee6ed178L,
		 0x06f067aa72176fbaL, 0x0a637dc5a2c898a6L,
		 0x113f9804bef90daeL, 0x1b710b35131c471bL,
		 0x28db77f523047d84L, 0x32caab7b40c72493L,
		 0x3c9ebe0a15c9bebcL, 0x431d67c49c100d4cL,
		 0x4cc5d4becb3e42b6L, 0x597f299cfc657e2aL,
		 0x5fcb6fab3ad6faecL, 0x6c44198c4a475817L};
	
	protected void resetContext() //상수값 초기화
	{	
	     h0 = 0x6a09e667f3bcc908L;
	     h1 = 0xbb67ae8584caa73bL;
	     h2 = 0x3c6ef372fe94f82bL;
	     h3 = 0xa54ff53a5f1d36f1L;
	     h4 = 0x510e527fade682d1L;
	     h5 = 0x9b05688c2b3e6c1fL;
	     h6 = 0x1f83d9abfb41bd6bL;
	     h7 = 0x5be0cd19137e2179L;
	}
	 	
	private long h0, h1, h2, h3, h4, h5, h6, h7; // 상수값
	
	private static final int BLOCK_SIZE = 128; // 128바이트 (1024비트)
		 
	private static final long[] w = new long[80]; //80개 워드 선언
	
	//패딩
	 protected byte[] padBuffer(int count) {
	     	int n = (int) (count % BLOCK_SIZE); // 메시지길이를 128로 나눈 나머지를 패딩채움
	     	int padding = (n < 112) ? (112 - n) : (240 - n); // 16바이트(128비트)는 원래메시지길이를 저장하기 위해 놔둠, 112가 안될시 다음블럭에서 뺌 
	     	byte[] result = new byte[padding + 16]; //마지막 블럭의 길이 선언 
	 
	     	result[0] = (byte) 0x80; //패딩 첫자리는 1로 선언 1000 0000
	 
	     	long bits = count << 3; //count(인트형)을 bits(롱형)으로 바꿔주며 하위 3비트를 0으로 채워줌
	     	padding += 8; //128비트는 원래메시지 저장 공간이므로 제외
	     	result[padding++] = (byte) (bits >> 56); //bits 56비트를 이동 바이트화하여 패딩값에 돌려줌
	     	result[padding++] = (byte) (bits >> 48); //6바이트 0
	     	result[padding++] = (byte) (bits >> 40); //5바이트 0
	     	result[padding++] = (byte) (bits >> 32); //4바이트 0
	     	result[padding++] = (byte) (bits >> 24); //3바이트 0
	     	result[padding++] = (byte) (bits >> 16); //2바이트 0
	     	result[padding++] = (byte) (bits >> 8); //1바이트 0
	     	result[padding] = (byte) bits; //마지막까지 0
	 
	     	return result; //패딩 된 값을 돌려줌
	 }
	 
	 protected void transform(byte[] in, int offset) //패딩 후 값을 넣어줌 // 오프셋 = 메시지 길이만큼 띄워줌 (패딩외 지역)
	 {
		 long[] result = sha(h0, h1, h2, h3, h4, h5, h6, h7, in, offset);
		 h0 = result[0];
	     h1 = result[1];
	     h2 = result[2];
	     h3 = result[3];
	     h4 = result[4];
	     h5 = result[5];
	     h6 = result[6];
	     h7 = result[7];
	 }
	 
	 //SHA512의 압축함수
	 private static final synchronized long[] sha(long hh0, long hh1, long hh2, 
             long hh3, long hh4, long hh5, long hh6, long hh7, byte[] in, int offset) //객체단위 쓰레드 동기화
	 {
	     long A = hh0;
	     long B = hh1;
	     long C = hh2;
	     long D = hh3;
	     long E = hh4;
	     long F = hh5;
	     long G = hh6;
	     long H = hh7;
	     long T, T2;
	     int r;
	     
	     for (r = 0; r < 16; r++) // 1부터 16 까지 롱데이형을 워드로 복사//0xFF 16진수 단위로 처리  
	     {
	    	 w[r] = (long) in[offset++] << 56 //워드에 메시지가 있는 구역을 넣어줌
	         		| ((long) in[offset++] & 0xFF) << 48 //롱배열 8개를 OR시킴 (복사)
	         		| ((long) in[offset++] & 0xFF) << 40 //1바이트씩 8번 8바이트(롱형)
	                | ((long) in[offset++] & 0xFF) << 32 
	                | ((long) in[offset++] & 0xFF) << 24
	                | ((long) in[offset++] & 0xFF) << 16
	                | ((long) in[offset++] & 0xFF) << 8
	                | ((long) in[offset++] & 0xFF);
	     }
	     //16부터 80까지 워드 확장
	     for (r = 16; r < 80; r++) 
	     {
	         T = w[r - 2]; 
	         T2 = w[r - 15];
	         w[r] = (((T >> 19) | (T << 45)) ^ ((T >> 61) | (T << 3)) ^ (T << 6)) + w[r - 7]
	                + (((T2 >> 1) | (T2 << 63)) ^ ((T2 >> 8) | (T2 << 56)) ^ (T2 << 7)) + w[r - 16];
	     }
	   
	     for (r = 0; r < 80; r++) 
	     {
	    	 
	    	 //Majority = (x AND y) XOR (y AND z) XOR (z AND x)
	         T2 = (((A >> 28) | (A << 36)) ^ ((A >> 34) | (A << 30)) ^ ((A >> 39) | (A << 25))) //Mixer1
	         + ((A & B) ^ (A & C) ^ (B & C)); //Majority
	       
	         //Conditional = (x AND y) XOR((NOTx) AND (z))
	    	 
	         T = H + (((E >> 14) | (E << 50)) ^ ((E >> 18) | (E << 46)) ^ ((E >> 41) | (E << 23))) //Mixer2
	         + ((E & F) ^ ((~E) & G)) + k[r] + w[r]; //Conditional 
	    	
	         
	         H = G;
	         G = F;
	         F = E;
	         E = D + T;
	         D = C;
	         C = B;
	         B = A;
	         A = T + T2;
	     }
	     
	     return new long[] { hh0 + A, hh1 + B, hh2 + C, hh3 + D, hh4 + E, hh5 + F,
	                        hh6 + G, hh7 + H };
	 }
	 
	 //메인함수
	 public static void main(String[] args){
		 int cnt=0;
		
		 String str = new String();
		 str = "A";
		 
		 for(int i=0;i<str.length();i++)
			 cnt++;
		 
		 int roop;
		 
		 roop = ((int)cnt/128)+1; //블럭 해쉬 시킬 횟수
		 
		 if((cnt%128)>113) //메시지 블럭 남는 숫자가 113보다 크다면 한회 추가 (메시지길이가 들어갈 자리 포함)
			 roop++;
		 
		 
		 long[] msg = new long[cnt];
		 byte[] msgbyte = new byte[BLOCK_SIZE];
		 
		 for(int i=0;i<cnt;i++)
			 msg[i] = (long)str.charAt(i); //스트링을 롱데이터형으로 바꿈
		 
	 for(int i=0;i<cnt;i++)
			 msgbyte[i] = (byte)msg[i]; //롱데이터를바이트형으로 바꿈
		 
		 System.out.println(cnt+"개의 메시지");
		 System.out.println(str);
		 
		 for(int i=0;i<cnt;i++)
			 System.out.print(msg[i]+" ");
		 
		 
		 
		 byte[] padresult = new byte[112];
	 
		 SHA512 Sha = new SHA512();
		 
		 
		 
		 //함수 넣을것 반복함수
		 for(int init=0;init<1;init++){
			 Sha.resetContext(); //초기 상수값 선언
			 
			 long[] InitHash = new long[8];
			 InitHash[0] = Sha.h0;
			 InitHash[1] = Sha.h1;
			 InitHash[2] = Sha.h2;
			 InitHash[3] = Sha.h3;
			 InitHash[4] = Sha.h4;
			 InitHash[5] = Sha.h5;
			 InitHash[6] = Sha.h6;
			 InitHash[7] = Sha.h7;
			 
				 for(int run=0;run<roop;run++){
					 
					 padresult = Sha.padBuffer(str.length()); //패딩값 받음
					 //메시지 뒤에 패딩을 붙임
					 msgbyte[cnt] = padresult[0];
					 
					 byte[] msglength = new byte[16];
					 
					 msglength[15] = (byte)str.length(); // 메시지길이를 배열에 넣음
					 
					 for(int i=0;i<=15;i++)
						 msgbyte[112+i] = msglength[i]; //메시지+패딩+메시지 원래 길이를 붙임
					 for(int i=0;i<BLOCK_SIZE;i++)
						 System.out.print(msgbyte[i]+" ");
					 
					 System.out.println();
					 System.out.println();
					 System.out.println("초기 상수값");
								
					 for(int i=0;i<8;i++)
						 System.out.format("%02X%n",InitHash[i]); //16진수 출력
					 
					 // 만약 메시지 길이가 128바이트를 넘을 경우 다시한번 패딩을 하게끔 수정요망
					 
					 Sha.transform(msgbyte, 0); //해쉬처리 메시지배열을 0바이트부터 끝까지
					 
					 System.out.println();
					 System.out.println("해쉬처리 끝난값");
					 
					 long[] CompleteHash = new long[8];
					 
					 CompleteHash[0] = Sha.h0;
					 CompleteHash[1] = Sha.h1;
					 CompleteHash[2] = Sha.h2;
					 CompleteHash[3] = Sha.h3;
					 CompleteHash[4] = Sha.h4;
					 CompleteHash[5] = Sha.h5;
					 CompleteHash[6] = Sha.h6;
					 CompleteHash[7] = Sha.h7;
					 
					 for(int i=0;i<8;i++)
						 System.out.format("%02X%n",CompleteHash[i]);
							
				 }
				 
		 }
	 }
}

import java.util.*;
import java.io.*;

public class Sha512 {
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
         0x5fcb6fab3ad6faecL, 0x6c44198c4a475817L };
	 
	 private static final int BLOCK_SIZE = 128; // 128바이트 (1024비트)
	 
	 private static final long[] w = new long[80]; //80개 워드 선언
	 
	//ABCDEFGH 초기 상수값
	 private static final long [] MD = { 
		 	0x6A09E667F3BCC908L,0xBB67AE8584CAA73BL,
		 	0x3C6EF372EF94F82BL, 0xA54FE53A5F1D36F1L,
			0x510E527FADE682D1L, 0x9B05688C2B3E6C1FL,
			0x1F83D9ABFB41BD6BL, 0x5BE0CD19137E2179L
	 };
	 
	 //패딩
	 protected byte[] padBuffer() {
	     	int n = (int) (count % BLOCK_SIZE); // 메시지길이를 128로 나눔
	     	int padding = (n < 112) ? (112 - n) : (240 - n); // 16바이트(128비트)는 원래메시지길이를 저장하기 위해 놔둠, 112가 안될시 다음블럭에서 뺌 
	     	byte[] result = new byte[padding + 16]; //마지막 블럭의 길이 선언 
	 
	     	result[0] = (byte) 0x80; //패딩 첫자리는 1로 선언 1000 0000
	 
	     	// save number of bits, casting the long to an array of 8 bytes
	     	// TODO: FIX Only ~35 bits of 128 bit counter usable this way
	     	long bits = count << 3; //0으로 채워줌
	     	padding += 8; //128비트는 원래메시지 저장 공간이므로 제외
	     	result[padding++] = (byte) (bits >>> 56); //7바이트 0으로 채워줌
	     	result[padding++] = (byte) (bits >>> 48); //6바이트 0
	     	result[padding++] = (byte) (bits >>> 40); //5바이트 0
	     	result[padding++] = (byte) (bits >>> 32); //4바이트 0
	     	result[padding++] = (byte) (bits >>> 24); //3바이트 0
	     	result[padding++] = (byte) (bits >>> 16); //2바이트 0
	     	result[padding++] = (byte) (bits >>> 8); //1바이트 0
	     	result[padding] = (byte) bits; //마지막 0
	 
	     	return result;
	 }
	 
	 
	 
	 public static long A = MD[0];
	 public static long B = MD[1];
	 public static long C = MD[2];
	 public static long D = MD[3];
	 public static long E = MD[4];
	 public static long F = MD[5];
	 public static long G = MD[6];
	 public static long H = MD[7];
	 public static long T,T2;
	byte in[];
	int offset;
	 
	 
	 for (int r = 0; r < 16; r++)
	 {
		 w[r] = (long) in[offset++] << 56 | ((long) in[offset++] & 0xFF) << 48
		 | ((long) in[offset++] & 0xFF) << 40
		 | ((long) in[offset++] & 0xFF) << 32
		 | ((long) in[offset++] & 0xFF) << 24
		 | ((long) in[offset++] & 0xFF) << 16
		 | ((long) in[offset++] & 0xFF) << 8
		 | ((long) in[offset++] & 0xFF);
	 }
	     for (r = 16; r < 80; r++)
	     {
	    	 T = w[r - 2];
	         T2 = w[r - 15];
	         w[r] = (((T >>> 19) | (T << 45)) ^ ((T >>> 61) | (T << 3)) ^ (T >>> 6))+ w[r - 7]
	                    + (((T2 >>> 1) | (T2 << 63)) ^ ((T2 >>> 8) | (T2 << 56)) ^ (T2 >>> 7))
	                    + w[r - 16];
	       }
	 
	     for (r = 0; r < 80; r++)
	     {
	    	 T = H
	         + (((E >>> 14) | (E << 50)) ^ ((E >>> 18) | (E << 46)) ^ ((E >>> 41) | (E << 23)))
	         + ((E & F) ^ ((~E) & G)) + k[r] + w[r];
	         T2 = (((A >>> 28) | (A << 36)) ^ ((A >>> 34) | (A << 30)) ^ ((A >>> 39) | (A << 25)))
	         + ((A & B) ^ (A & C) ^ (B & C));
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
	 


	 public static int [] Msg = {0x1234,0x1234};
	 public static int count;
	 
	 public static void main(String[] args){

		 for(int i=0;i<Msg.length;i++){
			 count++;
		 }
		 System.out.println(count);
		 
	 }
	 
}

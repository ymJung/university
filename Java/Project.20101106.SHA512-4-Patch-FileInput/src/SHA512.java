import java.io.*;
import java.util.*;

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
	
	protected void resetContext() //상수값 초기값
	{	
	     h[0] = 0x6a09e667f3bcc908L;
	     h[1] = 0xbb67ae8584caa73bL;
	     h[2] = 0x3c6ef372fe94f82bL;
	     h[3] = 0xa54ff53a5f1d36f1L;
	     h[4] = 0x510e527fade682d1L;
	     h[5] = 0x9b05688c2b3e6c1fL;
	     h[6] = 0x1f83d9abfb41bd6bL;
	     h[7] = 0x5be0cd19137e2179L;
	}
	 	
	private long h[] = new long[8]; // 상수값
	
	private static final int BLOCK_SIZE = 128; // 128바이트 (1024비트)
		 
	private static final long[] w = new long[80]; //80개 워드 선언
	private static int bsize = 56; 
	
	//패딩
	protected byte[] padBuffer(int count) {
		int n = (int) (count % BLOCK_SIZE); // 메시지길이를 128로 나눈 나머지를 패딩채움
		int padding = (n < 112) ? (112 - n) : (240 - n); // 16바이트(128비트)는 원래메시지길이를 저장하기 위해 놔둠, 112가 안될시 다음블럭에서 뺌 
		byte[] result = new byte[padding + 16]; //마지막 블럭의 길이 선언 
		result[0] = (byte) 0x80; //패딩 첫자리는 1로 선언 1000 0000
		
     	return result; //패딩 된 값을 돌려줌
	}
	 
	//SHA512의 압축함수
	private final synchronized long[] sha(long hh[], byte[] in) //객체단위 쓰레드 동기화
	{
	     long A = hh[0];
	     long B = hh[1];
	     long C = hh[2];
	     long D = hh[3];
	     long E = hh[4];
	     long F = hh[5];
	     long G = hh[6];
	     long H = hh[7];
	     long T, T2;
	     int r,bytesize=0;
	     
	     // 1부터 16 까지 메시지를 워드에 복사  
	     for(r=0;r<16;r++){
	    	 for(int j=0;j<8;j++){ // 바이트를 롱에 넣어줌
	    		 w[r] = (long)in[bytesize] << bsize; //롱타입으로 변환 (<< 비트연산자로 한바이트씩 넣어줌)
	    		 bsize-=8;
	    		 bytesize++;
	    	 }
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
	    	 //Rotate(A) : RotR28  ^  RotR38  ^  RotR39
	    
	    	 T2 = (((A >> 28) | (A << 36)) ^ ((A >> 38) | (A << 26)) ^ ((A >> 39) | (A << 25))) //Mixer1
	         + ((A & B) ^ (A & C) ^ (B & C)); //Majority
	       
	         //Conditional = (x AND y) XOR((NOTx) AND (z))
	    	 //Rotate(E) : RotR14  ^  RotR18  ^  RotR41
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
	     
	     return new long[] { hh[0] + A, hh[1] + B, hh[2] + C, hh[3] + D, hh[4] + E, hh[5] + F,
	                        hh[6] + G, hh[7] + H };
	}
	 
	private byte[][] str2byte(int roop,int cnt,String str){ //str을 long으로 바꿈
		byte[][] msgblock = new byte[roop][cnt];
		
		for(int i=0;i<roop;i++) 
			 for(int j=0;j<BLOCK_SIZE;j++)
				 msgblock[i][j] = (byte)str.charAt((i*BLOCK_SIZE)+j); //스트링을 롱데이터형으로 바꿈
		
		 return msgblock;
		
	}
	private int roopcnt(int cnt){ //루프수 결정
		int roop;
		roop = ((int)cnt/BLOCK_SIZE); //블럭 해쉬 시킬 횟수
		if((cnt%BLOCK_SIZE)>113) //메시지 블럭 남는 숫자가 113보다 크다면 한회 추가 (메시지길이가 들어갈 자리 포함)
			 roop++;
		return roop;
	}
	private void printmsgblock(int roop,int cnt,byte[][] msgblock){ //전체 메시지블럭 출력
		for(int i=0;i<roop;i++)
			 for(int j=0;j<cnt;j++)
				 System.out.print(msgblock[i][j]+" ");
	}
	
	private void hashprint(long[] Hash){
		for(int i=0;i<8;i++)
			 System.out.format("%02X%n",Hash[i]); //16진수 출력
	}
	
	private void byteblockprint(byte[] msgbyte){ //128바이트 블럭 출력
		for(int i=0;i<BLOCK_SIZE;i++)
			 System.out.print(msgbyte[i]+" ");
	}
	private byte[] lastmsgblock(byte[] padresult, int cnt,String str,int roop){ //마지막 블럭 설정 : 마지막 메시지 + 패딩 + 메시지길이
		byte[] msgbyte = new byte[BLOCK_SIZE];
		int lastcnt = (cnt % BLOCK_SIZE);
		
		for(int i=0;i<lastcnt;i++) 
			msgbyte[i] = (byte)str.charAt((roop*BLOCK_SIZE)+i); //마지막 블럭을 바이트화해서 넣음
		
		 
		for(int i=0;i<BLOCK_SIZE-lastcnt;i++) //블럭사이즈-마지막블럭글자수 
			msgbyte[lastcnt+i] = padresult[i];//마지막 메시지 뒤에 패딩을 붙임
		
		long lmsglength = (long)str.length();
		
		for(int i=120;i<128;i++){ //long에 들어있는 메시지 길이를 byte에 넣어줌
			msgbyte[i] = (byte)(lmsglength >> bsize);
			bsize -=8;
		}
		
		return msgbyte;
	}
	
	private String filein(String filename)throws IOException{
		BufferedReader reader = null;
		String filestring = null;
		reader = new BufferedReader(new FileReader(filename)); //텍스트파일 읽어오는 부분
		while(true){
			String data = reader.readLine();
			if (data == null)
				break;
			filestring+=data;
		} //처음 null 스트링 값을 빼는법 알아볼것.
		
		reader.close();
        return filestring;
	}
	
	//메인함수
	public static void main(String[] args){
		try{ 
			int cnt=0,roop;
			byte[] msgbyte = new byte[BLOCK_SIZE];
		 
			SHA512 Sha = new SHA512(); 
			//메인 함수 선언
		 
			String str = new String();
			Scanner filescan = new Scanner(System.in);
			String fn;
			System.out.println("텍스트가 들어있는 파일명을 입력하세요 "); //파일 입력
			fn = filescan.nextLine();
			str = Sha.filein(fn);
			
			for(int i=0;i<str.length();i++)
				cnt++;
			
			roop = Sha.roopcnt(cnt);
		 
			byte[][] msgblock = new byte[roop][BLOCK_SIZE];
		 
			msgblock = Sha.str2byte(roop,cnt,str);  //스트링을 롱데이터형으로 바꿈
		 
			System.out.println(cnt+"개의 메시지");
			System.out.println(str);
			System.out.println(roop+1 +"개의 메시지블록");
		 
			Sha.printmsgblock(roop, cnt, msgblock); //메시지 블록 출력		
		
			Sha.resetContext(); //초기 상수값 설정
		 
			long[] InitHash = new long[8];
		 
			InitHash = Sha.h; // 초기값을 넣어줌
		 
			System.out.println();
			System.out.println("초기 상수값");
		 
			//함수 넣을것 반복함수
			Sha.hashprint(InitHash); //초기상수 출력
		 
			long[] HashProcess = new long[8];
			HashProcess = InitHash; //처리할 값에다가 초기값을 넣어줌 
	
		 
			for(int i=0;i<roop;i++){ 
				for(int j=0;j<BLOCK_SIZE;j++)
					msgbyte[j] = (byte)msgblock[i][j]; //루프번째 메시지 블럭 처리값을 메시지 바이트에 넣어줌
				System.out.println();
				System.out.println(i+1 + "번째 블럭"); //처리값 출력
				Sha.byteblockprint(msgbyte); //블럭 출력
				HashProcess = Sha.sha(HashProcess, msgbyte); //메시지 블럭을 처리
				System.out.println();
				Sha.hashprint(HashProcess);
			}
		 
			System.out.println("마지막 해쉬시킬 블럭");
			//패딩
		 
			byte[] padresult = new byte[112]; //패딩값 선언
			padresult = Sha.padBuffer(str.length());
		 
			msgbyte = Sha.lastmsgblock(padresult, cnt, str, roop); // 마지막 메시지 블럭 설정	 
			Sha.byteblockprint(msgbyte);
		 
			long[] CompleteHash = new long[8]; 
			CompleteHash = Sha.sha(HashProcess, msgbyte);
		 
			System.out.println();
			System.out.println("해쉬처리 끝난값");
		 
			Sha.hashprint(CompleteHash);
			
			//해쉬 파일 출력 - ??
		}
		
		//예외처리
		catch (FileNotFoundException fnfe){
			System.out.println("파일이 존재하지 않습니다.");
		}
		catch (IOException ioe){
			System.out.println("파일을 읽을 수 없습니다.");
		}
		finally{
			try {}
			catch (Exception e){}
		}
	}
}

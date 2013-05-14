import java.io.*;
import java.util.*;

public class SHA512 {
	private static final long[] k = { //��� Ű ����
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
	
	protected void resetContext() //����� �ʱⰪ
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
	 	
	private long h[] = new long[8]; // �����
	
	private static final int BLOCK_SIZE = 128; // 128����Ʈ (1024��Ʈ)
		 
	private static final long[] w = new long[80]; //80�� ���� ����
	private static int bsize = 56; 
	
	//�е�
	protected byte[] padBuffer(int count) {
		int n = (int) (count % BLOCK_SIZE); // �޽������̸� 128�� ���� �������� �е�ä��
		int padding = (n < 112) ? (112 - n) : (240 - n); // 16����Ʈ(128��Ʈ)�� �����޽������̸� �����ϱ� ���� ����, 112�� �ȵɽ� ���������� �� 
		byte[] result = new byte[padding + 16]; //������ ���� ���� ���� 
		result[0] = (byte) 0x80; //�е� ù�ڸ��� 1�� ���� 1000 0000
		
     	return result; //�е� �� ���� ������
	}
	 
	//SHA512�� �����Լ�
	private final synchronized long[] sha(long hh[], byte[] in) //��ü���� ������ ����ȭ
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
	     
	     // 1���� 16 ���� �޽����� ���忡 ����  
	     for(r=0;r<16;r++){
	    	 for(int j=0;j<8;j++){ // ����Ʈ�� �տ� �־���
	    		 w[r] = (long)in[bytesize] << bsize; //��Ÿ������ ��ȯ (<< ��Ʈ�����ڷ� �ѹ���Ʈ�� �־���)
	    		 bsize-=8;
	    		 bytesize++;
	    	 }
	     }
	     
	     //16���� 80���� ���� Ȯ��
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
	 
	private byte[][] str2byte(int roop,int cnt,String str){ //str�� long���� �ٲ�
		byte[][] msgblock = new byte[roop][cnt];
		
		for(int i=0;i<roop;i++) 
			 for(int j=0;j<BLOCK_SIZE;j++)
				 msgblock[i][j] = (byte)str.charAt((i*BLOCK_SIZE)+j); //��Ʈ���� �յ����������� �ٲ�
		
		 return msgblock;
		
	}
	private int roopcnt(int cnt){ //������ ����
		int roop;
		roop = ((int)cnt/BLOCK_SIZE); //�� �ؽ� ��ų Ƚ��
		if((cnt%BLOCK_SIZE)>113) //�޽��� �� ���� ���ڰ� 113���� ũ�ٸ� ��ȸ �߰� (�޽������̰� �� �ڸ� ����)
			 roop++;
		return roop;
	}
	private void printmsgblock(int roop,int cnt,byte[][] msgblock){ //��ü �޽����� ���
		for(int i=0;i<roop;i++)
			 for(int j=0;j<cnt;j++)
				 System.out.print(msgblock[i][j]+" ");
	}
	
	private void hashprint(long[] Hash){
		for(int i=0;i<8;i++)
			 System.out.format("%02X%n",Hash[i]); //16���� ���
	}
	
	private void byteblockprint(byte[] msgbyte){ //128����Ʈ �� ���
		for(int i=0;i<BLOCK_SIZE;i++)
			 System.out.print(msgbyte[i]+" ");
	}
	private byte[] lastmsgblock(byte[] padresult, int cnt,String str,int roop){ //������ �� ���� : ������ �޽��� + �е� + �޽�������
		byte[] msgbyte = new byte[BLOCK_SIZE];
		int lastcnt = (cnt % BLOCK_SIZE);
		
		for(int i=0;i<lastcnt;i++) 
			msgbyte[i] = (byte)str.charAt((roop*BLOCK_SIZE)+i); //������ ���� ����Ʈȭ�ؼ� ����
		
		 
		for(int i=0;i<BLOCK_SIZE-lastcnt;i++) //��������-�����������ڼ� 
			msgbyte[lastcnt+i] = padresult[i];//������ �޽��� �ڿ� �е��� ����
		
		long lmsglength = (long)str.length();
		
		for(int i=120;i<128;i++){ //long�� ����ִ� �޽��� ���̸� byte�� �־���
			msgbyte[i] = (byte)(lmsglength >> bsize);
			bsize -=8;
		}
		
		return msgbyte;
	}
	
	private String filein(String filename)throws IOException{
		BufferedReader reader = null;
		String filestring = null;
		reader = new BufferedReader(new FileReader(filename)); //�ؽ�Ʈ���� �о���� �κ�
		while(true){
			String data = reader.readLine();
			if (data == null)
				break;
			filestring+=data;
		} //ó�� null ��Ʈ�� ���� ���¹� �˾ƺ���.
		
		reader.close();
        return filestring;
	}
	
	//�����Լ�
	public static void main(String[] args){
		try{ 
			int cnt=0,roop;
			byte[] msgbyte = new byte[BLOCK_SIZE];
		 
			SHA512 Sha = new SHA512(); 
			//���� �Լ� ����
		 
			String str = new String();
			Scanner filescan = new Scanner(System.in);
			String fn;
			System.out.println("�ؽ�Ʈ�� ����ִ� ���ϸ��� �Է��ϼ��� "); //���� �Է�
			fn = filescan.nextLine();
			str = Sha.filein(fn);
			
			for(int i=0;i<str.length();i++)
				cnt++;
			
			roop = Sha.roopcnt(cnt);
		 
			byte[][] msgblock = new byte[roop][BLOCK_SIZE];
		 
			msgblock = Sha.str2byte(roop,cnt,str);  //��Ʈ���� �յ����������� �ٲ�
		 
			System.out.println(cnt+"���� �޽���");
			System.out.println(str);
			System.out.println(roop+1 +"���� �޽������");
		 
			Sha.printmsgblock(roop, cnt, msgblock); //�޽��� ��� ���		
		
			Sha.resetContext(); //�ʱ� ����� ����
		 
			long[] InitHash = new long[8];
		 
			InitHash = Sha.h; // �ʱⰪ�� �־���
		 
			System.out.println();
			System.out.println("�ʱ� �����");
		 
			//�Լ� ������ �ݺ��Լ�
			Sha.hashprint(InitHash); //�ʱ��� ���
		 
			long[] HashProcess = new long[8];
			HashProcess = InitHash; //ó���� �����ٰ� �ʱⰪ�� �־��� 
	
		 
			for(int i=0;i<roop;i++){ 
				for(int j=0;j<BLOCK_SIZE;j++)
					msgbyte[j] = (byte)msgblock[i][j]; //������° �޽��� �� ó������ �޽��� ����Ʈ�� �־���
				System.out.println();
				System.out.println(i+1 + "��° ��"); //ó���� ���
				Sha.byteblockprint(msgbyte); //�� ���
				HashProcess = Sha.sha(HashProcess, msgbyte); //�޽��� ���� ó��
				System.out.println();
				Sha.hashprint(HashProcess);
			}
		 
			System.out.println("������ �ؽ���ų ��");
			//�е�
		 
			byte[] padresult = new byte[112]; //�е��� ����
			padresult = Sha.padBuffer(str.length());
		 
			msgbyte = Sha.lastmsgblock(padresult, cnt, str, roop); // ������ �޽��� �� ����	 
			Sha.byteblockprint(msgbyte);
		 
			long[] CompleteHash = new long[8]; 
			CompleteHash = Sha.sha(HashProcess, msgbyte);
		 
			System.out.println();
			System.out.println("�ؽ�ó�� ������");
		 
			Sha.hashprint(CompleteHash);
			
			//�ؽ� ���� ��� - ??
		}
		
		//����ó��
		catch (FileNotFoundException fnfe){
			System.out.println("������ �������� �ʽ��ϴ�.");
		}
		catch (IOException ioe){
			System.out.println("������ ���� �� �����ϴ�.");
		}
		finally{
			try {}
			catch (Exception e){}
		}
	}
}

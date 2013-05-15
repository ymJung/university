import java.io.*;

public class Notepad  {
	public void NotePad(String s) throws IOException {
		String filename = s;
		int block = 0;
		BufferedInputStream bis = new BufferedInputStream(new FileInputStream(new File(filename)));
		byte[] buff = new byte[128]; //128���� ���� ���
        while((block = bis.read(buff, 0, buff.length)) > 0)  //�Ѻ�Ͼ� ������ ���
        	System.out.print(new String(buff, 0, block));
        
	}
	public static void main(String[] args) throws IOException{
		Notepad np = new Notepad();
		String s = "test.txt";
		if ( args.length > 0) {
			s = args[0];
		}
		np.NotePad(s);
	}
}
/*Notepad Ŭ���� ����
�������� ���ڷ� ���ϸ��� �Է¹޾� File ��ü ����
FileInputStream, BufferedInputStream�� �̿��Ͽ�
�ѱ��� ���Ե� ������ ������ �״�� ����Ѵ�.

public static void main(String args[]) {
  Notepad np = new Notepad(args[0]);
  }
*/

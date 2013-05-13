import java.io.*;

public class Notepad  {
	public void NotePad(String s) throws IOException {
		String filename = s;
		int block = 0;
		BufferedInputStream bis = new BufferedInputStream(new FileInputStream(new File(filename)));
		byte[] buff = new byte[128]; //128글자 까지 출력
        while((block = bis.read(buff, 0, buff.length)) > 0)  //한블록씩 꺼내서 출력
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
/*Notepad 클래스 선언
생성자의 인자로 파일명을 입력받아 File 객체 생성
FileInputStream, BufferedInputStream을 이용하여
한글이 포함된 파일의 내용을 그대로 출력한다.

public static void main(String args[]) {
  Notepad np = new Notepad(args[0]);
  }
*/

import java.io.*;

public class CopyFile {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		BufferedReader in = null;
		PrintWriter out = null;
		out = new PrintWriter(new FileWriter("output.txt"));
		out.println("�ȳ��ϼ���");
		out.println("����Թ̴� ���� ����");
		out.println("������ ���ּ�����");
		out.println("������ ���Ѵٸ� ������ �ƴԹ̴� ����");
		out.flush();
		in = new BufferedReader(new FileReader("output.txt"));
		String line;
		while((line = in.readLine()) != null){
			System.out.println(line);
		}
		if(in!=null)
			in.close();
		if(out!=null)
			out.close();
		
	}

}

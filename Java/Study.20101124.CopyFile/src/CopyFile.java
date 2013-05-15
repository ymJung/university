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
		out.println("æ»≥Á«œººø‰");
		out.println("ªÁ∂˚«‘πÃ¥Ÿ ∞Ì∞ª¥‘ §ª§ª");
		out.println("∞·¡¶∏¶ «ÿ¡÷ººø∞ø∞");
		out.println("∞·¡¶∏¶ æ»«—¥Ÿ∏È ∞Ì∞ª¥‘¿Ã æ∆¥‘πÃ¥Ÿ ≤®†∫");
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

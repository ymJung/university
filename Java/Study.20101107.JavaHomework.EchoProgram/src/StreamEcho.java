import java.io.*;

public class StreamEcho {
	
	public static char c;
	
	public static void main(String[] args){
		InputStream echo = System.in;
		System.out.println("echo���α׷��Դϴ�. (����->S)");
		try{
			while(c != 'S'){
				c = (char)echo.read();
				System.out.print(c);
				}
		}catch(IOException e)
		{
			System.out.println("����ó��");
		}
			
		
	}

}

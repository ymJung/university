import java.io.IOException;
public class Test {
	public static void main(String[] args){
		System.out.println(readString());
	}
	
	public static String readString(){
		byte[] buf = new byte[100];
		System.out.println("문자열을 입력하시오");
		try{
			System.in.read(buf);
		}catch(IOException e){
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
		return new String(buf);
	}

}

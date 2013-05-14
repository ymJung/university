
public class trycatch {
	public static void main(String args[]){
		int x =1,y=0;
		try{
			int result = x/y; //에러발생
		}
		catch (ArithmeticException e){
			System.out.println("0으로 나눌수 없음");
		}
		System.out.println("프로그램은 그대로 진행");
		
		}
}

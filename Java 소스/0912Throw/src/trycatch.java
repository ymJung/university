
public class trycatch {
	public static void main(String args[]){
		int x =1,y=0;
		try{
			int result = x/y; //�����߻�
		}
		catch (ArithmeticException e){
			System.out.println("0���� ������ ����");
		}
		System.out.println("���α׷��� �״�� ����");
		
		}
}

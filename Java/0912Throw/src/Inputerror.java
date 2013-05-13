import java.util.*;
public class Inputerror {
	static Scanner scan = new Scanner(System.in);
	
	public static void main(String[] args){
		int i = 0;
		System.out.println("정수를 입력하세요: ");
		try{
			i = scan.nextInt();
			System.out.println("입력받은 정수값 : " +i );
		}catch(InputMismatchException e){
			System.out.println("잘못입력했어");
		}
	}

}

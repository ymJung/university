import java.util.*;
public class Inputerror {
	static Scanner scan = new Scanner(System.in);
	
	public static void main(String[] args){
		int i = 0;
		System.out.println("������ �Է��ϼ���: ");
		try{
			i = scan.nextInt();
			System.out.println("�Է¹��� ������ : " +i );
		}catch(InputMismatchException e){
			System.out.println("�߸��Է��߾�");
		}
	}

}

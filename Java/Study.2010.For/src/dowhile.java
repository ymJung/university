import java.util.*;

public class dowhile {

	/**
	 * @param args
	 */
	public static void main(String[] args){
		// TODO Auto-generated method stub
		int answer = 44; //����
		int guess;
		int tries =0;
		Scanner scan = new Scanner(System.in);
		
		do{
			System.out.print("������ ������ : ");
			guess = scan.nextInt();
			tries++;
			
			if(guess > answer)
				System.out.println("�װź��� ����");
			if(guess < answer)
				System.out.println("�װź��� ����");
		}while(guess!=answer);
		
		System.out.printf("��������! %d������ �����?\n",tries);
		
	}

}

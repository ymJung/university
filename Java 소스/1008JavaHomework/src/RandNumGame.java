import java.util.*;

public class RandNumGame {
	public static void main(String[] args){
		Random rand = new Random();
		int answer = rand.nextInt(10); //����
		int guess;
		int tries=0;
		
		Scanner scan = new Scanner(System.in);
		
		do{
			System.out.print("���� ���� : ");
			guess = scan.nextInt();
			tries++;			
			if(guess > answer)
				System.out.println("����");
			else if(guess < answer)
				System.out.println("����");
			
		}while(guess!=answer);
		
		System.out.println(tries+" ������ ����");
	}
}


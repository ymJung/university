import java.util.*;

public class RandNumGame {
	public static void main(String[] args){
		Random rand = new Random();
		int answer = rand.nextInt(10); //정답
		int guess;
		int tries=0;
		
		Scanner scan = new Scanner(System.in);
		
		do{
			System.out.print("답을 추측 : ");
			guess = scan.nextInt();
			tries++;			
			if(guess > answer)
				System.out.println("낮아");
			else if(guess < answer)
				System.out.println("높아");
			
		}while(guess!=answer);
		
		System.out.println(tries+" 번만에 정답");
	}
}


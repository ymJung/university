import java.util.*;

public class dowhile {

	/**
	 * @param args
	 */
	public static void main(String[] args){
		// TODO Auto-generated method stub
		int answer = 44; //정답
		int guess;
		int tries =0;
		Scanner scan = new Scanner(System.in);
		
		do{
			System.out.print("정답을 추측해 : ");
			guess = scan.nextInt();
			tries++;
			
			if(guess > answer)
				System.out.println("그거보다 낮아");
			if(guess < answer)
				System.out.println("그거보다 높아");
		}while(guess!=answer);
		
		System.out.printf("ㅊㅋㅊㅋ! %d번만에 맞췄네?\n",tries);
		
	}

}

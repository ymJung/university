import java.util.Scanner; // 입력을 위한 Scanner 클래스 포함

public class Overpay {
	public static void main(String args[]){
		final int RATE = 5000; //고정
		int pay;
		int hours;
		Scanner input = new Scanner(System.in);
		System.out.print("시간을 입력하시오: ");
		hours = input.nextInt();
		if(hours > 8)
			pay = RATE * 8 + (int) (1.5* RATE * (hours - 8)); //8시간 초과근무시
		else
			pay = RATE * hours;
		System.out.printf("임금은%d입니다",pay);
		
		
	}
}

import java.util.Scanner;
public class casegrade {
	public static void main(String args[]){
		int month,year,days;
		year = 2010;
		days = 0;
		
		System.out.print("몇월이 몇일인가?? \n월수를 입력하라 : ");
		Scanner scan = new Scanner(System.in);
		month = scan.nextInt();
		
		switch(month){
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				days = 31;
				break;
			case 2: //윤달계산
				if(((year % 4 ==0) &&! (year %100 == 0))||(year %400 ==0))
					days = 29;
				else
					days = 28;
				break;
				
				default:
					System.out.println("너 잘못입력했어");
					break;
		}
		System.out.println("입력한 달의 일수는 " +days);
		
		
	}

}

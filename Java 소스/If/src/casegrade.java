import java.util.Scanner;
public class casegrade {
	public static void main(String args[]){
		int month,year,days;
		year = 2010;
		days = 0;
		
		System.out.print("����� �����ΰ�?? \n������ �Է��϶� : ");
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
			case 2: //���ް��
				if(((year % 4 ==0) &&! (year %100 == 0))||(year %400 ==0))
					days = 29;
				else
					days = 28;
				break;
				
				default:
					System.out.println("�� �߸��Է��߾�");
					break;
		}
		System.out.println("�Է��� ���� �ϼ��� " +days);
		
		
	}

}

import java.util.Scanner;

public class ArrayTest4 {
	public static void main(String[] args){
		final int STUDENTS = 5;
		int total = 0;
		
		Scanner scan = new Scanner(System.in);
		int[] scores = new int[STUDENTS];
		
		for(int i = 0;i<STUDENTS;i++){
			System.out.print("�����Է��ϼ�");
			scores[i]= scan.nextInt();
		}
		for (int i=0;i<STUDENTS;i++)
			total +=scores[i];
		System.out.println("��ռ�����" +total/STUDENTS+ "�Դϴ�");
		
	}

}

import java.util.Scanner;

public class ArrayTest4 {
	public static void main(String[] args){
		final int STUDENTS = 5;
		int total = 0;
		
		Scanner scan = new Scanner(System.in);
		int[] scores = new int[STUDENTS];
		
		for(int i = 0;i<STUDENTS;i++){
			System.out.print("성적입력하쇼");
			scores[i]= scan.nextInt();
		}
		for (int i=0;i<STUDENTS;i++)
			total +=scores[i];
		System.out.println("평균성적은" +total/STUDENTS+ "입니다");
		
	}

}

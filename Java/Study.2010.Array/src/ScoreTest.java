import java.util.Scanner;

public class ScoreTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int total=0,size;
		
		Scanner scan = new Scanner(System.in);
		System.out.print("�迭�� ũ�⸦ �Է��Ͻÿ� :");
		size = scan.nextInt();
		int[] scores = new int[size];
		for(int i =0;i<scores.length;i++){
			System.out.print("������ �Է��Ͻÿ�");
			scores[i] = scan.nextInt();
		}
		
		for(int i =0;i<scores.length;i++)
			total += scores[i];
		System.out.println("��ռ����� "+total/scores.length+ "�Դϴ�");
	}

}

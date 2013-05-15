import java.util.Scanner; // 스캐너 클래스 사용

public class Radius {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		double radius,area;
		Scanner input = new Scanner(System.in);
		System.out.print("반지름 입력하쇼 : "); 
		radius = input. nextDouble();
		area = 3.141592 * radius * radius;
		System.out.printf("입력한 원의 면적은 %f.2다!",area);
		
		

	}

}

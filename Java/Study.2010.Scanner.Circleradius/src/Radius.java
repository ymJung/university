import java.util.Scanner; // ��ĳ�� Ŭ���� ���

public class Radius {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		double radius,area;
		Scanner input = new Scanner(System.in);
		System.out.print("������ �Է��ϼ� : "); 
		radius = input. nextDouble();
		area = 3.141592 * radius * radius;
		System.out.printf("�Է��� ���� ������ %f.2��!",area);
		
		

	}

}


public class FloatPoint {
	public static void main(String args[]){
		double r1 = 123.5;
		double r2 = 1.2E-300; // 1.2 ���ϱ� 10�� -300�� 
		double r3 = 1.2E+300; // 1.2 ���ϱ� 10�� 300��
		System.out.println(0.0/0.0);
		System.out.println(r1/0.0);
		System.out.println(r2/r3);
		System.out.println(r3/r2);
	}

}

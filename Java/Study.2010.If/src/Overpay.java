import java.util.Scanner; // �Է��� ���� Scanner Ŭ���� ����

public class Overpay {
	public static void main(String args[]){
		final int RATE = 5000; //����
		int pay;
		int hours;
		Scanner input = new Scanner(System.in);
		System.out.print("�ð��� �Է��Ͻÿ�: ");
		hours = input.nextInt();
		if(hours > 8)
			pay = RATE * 8 + (int) (1.5* RATE * (hours - 8)); //8�ð� �ʰ��ٹ���
		else
			pay = RATE * hours;
		System.out.printf("�ӱ���%d�Դϴ�",pay);
		
		
	}
}
